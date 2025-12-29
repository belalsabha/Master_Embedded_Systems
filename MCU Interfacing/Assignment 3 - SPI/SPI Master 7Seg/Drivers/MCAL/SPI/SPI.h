/*
 * SPI.h
 *
 * Created: 29 / 12 /2025
 * Author : Belal Hani Sabha
 */



#ifndef SPI_H_
#define SPI_H_


//----------------------------------
//Includes
//----------------------------------
#include "Atmega32.h"
#include "IO.h"

//-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//----------------------------------
//User type definitions (structures)
//----------------------------------
//Configuration structure For User inputs
typedef struct {

	uint8_t       SPI_Mode 		           ;	    // Specifies the SPI is it MISO || MOSI.
													// This parameter must be set based on @ref SPI_Mode_define
	
	uint8_t		 Data_Order                ;		//selects which data transmit first MSB || LSB
													//This parameter must be set based on @ref Data_Order_Select_define

	uint32_t     Clock_Polarity 	 	   ;		// Select which edge for reading and which for writing 
													// This parameter must be set based on @ref Clock_Polarity_define


	uint8_t	     Clock_Phase     		   ;		// determine if data is sampled on the leading (first) or trailing (last) edge of SCK.
													// This parameter must be set based on @ref  Clock_Phase _define

	uint8_t		 Clock_Rate		 	       ;		//select frequency .
													//@ref Clock_Rate_define
													
	uint8_t       Speed   		           ;		//Specifies whether the Speed is Normal or Double
													//@ref USART_Speed _define												
	
	uint8_t      IRQ_Enable	 	           ; 		//enable or disable SPI IRQ 
													//@ref SPI_IRQ_Enable_define 


	void 		 (*Ptr_ISR_Func)(void)     ;	    //Set the C Function() which will be called once the IRQ  Happen


}SPI_Config_t;




//-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//----------------------------------
//Macros Configuration References
//----------------------------------

//@ref SPI_Mode_define
#define  SPI_Master    				(1<<4)        		    //•  Bit 4 – MSTR: Master/Slave Select   >> 1 >> Master
#define  SPI_Slave     			    (0)        			//•  Bit 4 – MSTR: Master/Slave Select   >> 0 >> Slave


//@ref Data_Order_Select_define
#define  LSB    					(1<<5)        		    //•  • Bit 5 – DORD: Data Order   >> 1 >> LSB First
#define  MSB    					(0)        			//•  • Bit 5 – DORD: Data Order   >> 0 >> MSB First 

//@ref Clock_Polarity_define
//	CPOL	Leading Edge	Trailing Edge
//	0		Rising			Falling
//	1		Falling			Rising
#define  Rising_Falling    	        (0)        		    //•  •  • Bit 3 – CPOL: Clock Polarity
#define  Falling_Rising    	        (1<<3)        			//•  •  • Bit 3 – CPOL: Clock Polarity


//@ref  Clock_Phase _define
//CPHA    Leading Edge     Trailing Edge
//  0     Sample		   Setup
//  1     Setup			   Sample
#define  Sample_Setup    	        (0)        		    //•  •  •  • Bit 2 – CPHA: Clock Phase
#define  Setup_Sample   	        (1<<2)        			//•  •  •  • Bit 2 – CPHA: Clock Phase




//@ref USART_Speed _define
#define SPI_Speed_Normal              (0)			  ////• Bit 0 – SPI2X: Double SPI Speed Bit
#define SPI_Speed_Double              (1<<0)			  ////• Bit 0 – SPI2X: Double SPI Speed Bit



//@ref Clock_Rate_define

//• Bits 1, 0 – SPR1, SPR0: SPI Clock Rate Select 1 and 0
//• Bit 0 – SPI2X: Double SPI Speed Bit

//SPI2X SPR1  SPR0  SCK Frequency
//0		 0	   0	 fosc/4
//0		 0	   1	 fosc/16
//0		 1	   0	 fosc/64
//0		 1	   1	 fosc/128
//1		 0	   0	 fosc/2
//1		 0	   1	 fosc/8
//1		 1	   0	 fosc/32
//1		 1	   1	 fosc/64

//for normal speed 
#define Normal_Fosc_4			(0)
#define Normal_Fosc_16			(1<<0)
#define Normal_Fosc_64			(1<<1)
#define Normal_Fosc_128		    (1<<0) | (1<<1)

//for double speed
#define Double_Fosc_2			(0)
#define Double_Fosc_8			(1<<0)
#define Double_Fosc_32			(1<<1)
#define Double_Fosc_64		    (1<<0) | (1<<1)



//@ref SPI_IRQ_Enable_define
#define SPI_IRQ_Disable         (0)
#define SPI_IRQ_Enable          (1<<7)  //• • Bit 7 – SPIE: SPI Interrupt Enable





#define SPI_PORT			IOB
#define SS	 				IO_PIN4
#define MOSI 				IO_PIN5
#define MISO 				IO_PIN6
#define SCLK 				IO_PIN7





/*
 * =======================================================================================
 * 							APIs Supported by "MCAL SPI DRIVER"
 * =======================================================================================
 */

void MCAL_SPI_Init(SPI_t *SPIx , SPI_Config_t *SPI_Config);
void MCAL_SPI_DeInit();
void MCAL_SPI_IO_Set_Pins(SPI_t *SPIx );
uint8_t MCAL_SPI_SendReceive(SPI_t *SPIx, uint8_t data);




#endif /* SPI_H_ */