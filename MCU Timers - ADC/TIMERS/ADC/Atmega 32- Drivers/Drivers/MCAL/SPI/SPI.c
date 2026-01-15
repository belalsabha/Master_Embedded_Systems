/*
 * SPI.c
 *
 * Created: 29 / 12 /2025
 * Author : Belal Hani Sabha
 */

#include "SPI.h"

void (*SPI_Callback)(void);

void MCAL_SPI_Init(SPI_t *SPIx, SPI_Config_t *SPI_Config){

		

		MCAL_SPI_DeInit(SPIx);
		
		
		// • Bit 6 – SPE: SPI Enable
		//When the SPE bit is written to one, the SPI is enabled. This bit must be set to enable any SPI operations.
		SPIx->SPCR |= (1 << 6) ;
		
		//• Bit 4 – MSTR: Master/Slave Select
	    //This bit selects Master SPI mode when written to one, and Slave SPI mode when written logic zero. 
	    //If SS is configured as an input and is driven low while MSTR is set, MSTR will be cleared, and SPIF in SPSR will become set. 
		//The user will then have to set MSTR to re-enable SPI Master mode.
	if(SPI_Config->SPI_Mode == SPI_Master){
		SPIx->SPCR |= SPI_Master ;
	}
		
		
		//• Bit 5 – DORD: Data Order
		//When the DORD bit is written to one, the LSB of the data word is transmitted first.
		//When the DORD bit is written to zero, the MSB of the data word is transmitted first
		
	if(SPI_Config->Data_Order ==  LSB ){
		SPIx->SPCR |= LSB ;
	}
	
	
	
		//• Bit 3 – CPOL: Clock Polarity
		//	CPOL	Leading Edge	Trailing Edge
		//	0		Rising			Falling
		//	1		Falling			Rising
	SPIx->SPCR &= ~(1 << 3);
	SPIx->SPCR |= SPI_Config->Clock_Polarity;
		

		//• Bit 2 – CPHA: Clock Phase
		//CPHA    Leading Edge     Trailing Edge
		//  0     Sample		   Setup
		//  1     Setup			   Sample
	SPIx->SPCR &= ~(1 << 2);
	SPIx->SPCR |= SPI_Config->Clock_Phase;

		//• Bit 0 – SPI2X: Double SPI Speed Bit
		//When this bit is written logic one the SPI speed (SCK Frequency) will be doubled when the SPI
		//is in Master mode (see Table 58). This means that the minimum SCK period will be two CPU
		//clock periods. When the SPI is configured as Slave, the SPI is only guaranteed to work at fosc/4 or lower.
		
		
		
				
				//SPI2X SPR1  SPR0  SCK Frequency
				//0		 0	   0	 fosc/4
				//0		 0	   1	 fosc/16
				//0		 1	   0	 fosc/64
				//0		 1	   1	 fosc/128
				//1		 0	   0	 fosc/2
				//1		 0	   1	 fosc/8
				//1		 1	   0	 fosc/32
				//1		 1	   1	 fosc/64
				
			if (SPI_Config->Speed == SPI_Speed_Double)
			{
				SPIx->SPSR |= (1 << 0);   // SPI2X = 1
				SPIx->SPCR |= SPI_Config->Clock_Rate;
			}
			else
			{
				SPIx->SPSR &= ~(1 << 0);  // SPI2X = 0
				SPIx->SPCR |= SPI_Config->Clock_Rate;
			}
		

		//• Bit 7 – SPIE: SPI Interrupt Enable
		//This bit causes the SPI interrupt to be executed if SPIF bit in the SPSR Register is set and the if
		//the global interrupt enable bit in SREG is set.
		if (SPI_Config->IRQ_Enable)
		{
			SPIx->SPCR |= SPI_IRQ_Enable ;
			SREG |= (1 << 7);   // GIE 
			SPI_Callback = SPI_Config->Ptr_ISR_Func;
		}
			
}

void MCAL_SPI_DeInit(SPI_t *SPIx){
	
	SPIx->SPCR = 0x00 ;
	SPIx->SPSR &= ~(1<<0) ;	
}



uint8_t MCAL_SPI_SendReceive(SPI_t *SPIx, uint8_t data) {
	// Put data into buffer
	SPIx->SPDR = data;
	// Wait for transmission complete (SPIF bit in SPSR)
	while (!(SPIx->SPSR & (1 << 7)));
	// Return received data
	return SPIx->SPDR;
}


void MCAL_SPI_IO_Set_Pins(SPI_t *SPIx ){
	IO_Configure_Pin_t PinNumber_Configuration ;
	
	if(SPIx->SPCR & (1<<4) )
	{
		PinNumber_Configuration.IO_Pin_Number =  SS ;
		PinNumber_Configuration.IO_Mode = output_Hight ; 
		MCAL_IO_WritePin(SPI_PORT, SS, SET_PIN);  // Master idle HIGH

		
		MCAL_IO_Init( SPI_PORT,  &PinNumber_Configuration);
		
		PinNumber_Configuration.IO_Pin_Number =  MOSI ;
		PinNumber_Configuration.IO_Mode = 	output_Hight ;
		
		MCAL_IO_Init( SPI_PORT,  &PinNumber_Configuration);
		
		PinNumber_Configuration.IO_Pin_Number =  MISO ;
		PinNumber_Configuration.IO_Mode =  input_without_pull_up ;
			
		MCAL_IO_Init( SPI_PORT,  &PinNumber_Configuration);
			
		PinNumber_Configuration.IO_Pin_Number =  SCLK ;
		PinNumber_Configuration.IO_Mode = output_Hight;
		
		MCAL_IO_Init( SPI_PORT,  &PinNumber_Configuration);
	}else{
		PinNumber_Configuration.IO_Pin_Number =  SS ;
		PinNumber_Configuration.IO_Mode =input_without_pull_up ;
				
		MCAL_IO_Init( SPI_PORT,  &PinNumber_Configuration);

		PinNumber_Configuration.IO_Pin_Number =  MOSI ;
		PinNumber_Configuration.IO_Mode = 	input_without_pull_up ;
				
		MCAL_IO_Init( SPI_PORT,  &PinNumber_Configuration);
		
		PinNumber_Configuration.IO_Pin_Number =  MISO ;
		PinNumber_Configuration.IO_Mode = output_Hight ;
				
		MCAL_IO_Init( SPI_PORT,  &PinNumber_Configuration);
				
		PinNumber_Configuration.IO_Pin_Number =  SCLK ;
		PinNumber_Configuration.IO_Mode = input_without_pull_up;
				
		MCAL_IO_Init( SPI_PORT,  &PinNumber_Configuration);
	}	
}


ISR(SPI_STC_vect){
	
	SPI_Callback();
	
}