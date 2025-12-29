/*
 * App.c
 *
 * Created: 28 / 12 /2025
 * Author : Belal Hani Sabha
 */

#include "App.h"


	    /* Replace with your application code */
	    unsigned char counter = 0;
	    unsigned char index_display;



/* Simple  delay */
void Delay_ms(uint16_t ms)
{
	volatile uint16_t i, j;
	for (i = 0; i < ms; i++)
	{
		for (j = 0; j < 1000; j++)
		{
		}
	}
}


void SPI_Received_ISR(void){
	uint8_t received = SPI->SPDR; 
}


void execute(unsigned char cmd, unsigned char data , SPI_t *SPIx)
{
	MCAL_IO_WritePin(IOB,SS, RESET_PIN);
	SPIx->SPDR = cmd;
	while (!(SPIx->SPSR & (1 << 7)));
	SPIx->SPDR = data;
	while (!(SPIx->SPSR & (1 << 7)));
	MCAL_IO_WritePin(IOB,SS, SET_PIN);
	}


/* ================= App Initialization ================= */
void App_Init(void)
{
	LCD_Init();

	SPI_Config_t SPI_Config;

	SPI_Config.SPI_Mode = SPI_Master;
	SPI_Config.Data_Order = MSB;
	SPI_Config.Clock_Polarity = Rising_Falling;
	SPI_Config.Clock_Phase    = Sample_Setup;
	SPI_Config.Clock_Rate = Normal_Fosc_64;
	SPI_Config.Speed = USART_Speed_Normal;
	SPI_Config.IRQ_Enable = USART_IRQ_Disable;
	SPI_Config.Ptr_ISR_Func = NULL;

	 MCAL_SPI_Init(SPI , &SPI_Config);
	 MCAL_SPI_IO_Set_Pins(SPI);
	
	

	    execute(0x09, 0xFF,SPI);
	    execute(0x0A, 0xFF,SPI);
	    execute(0x0B, 0xF7,SPI);
	    execute(0x0C, 0x01,SPI);
	
}



/* ================= App Main Loop ================= */
void App_Run(void)
{
		for (index_display = 1; index_display < 9; index_display++)
		execute(index_display, counter++,SPI);
		Delay_ms(1000);
}
