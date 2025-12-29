/*
 * App_Slave.c
 *
 * Created: 29/12/2025
 * Author: Belal Hani Sabha
 */

#include "App.h"
uint8_t counter = 1;

/* Simple delay */
void Delay_ms(uint16_t ms)
{
    volatile uint16_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1000; j++);
}

/* ================= App Initialization ================= */
void App_Init(void)
{
   SPI_Config_t SPI_Config;
   SPI_Config.SPI_Mode = SPI_Master;
   SPI_Config.Data_Order = MSB;
   SPI_Config.Clock_Polarity = Rising_Falling;
   SPI_Config.Clock_Phase = Sample_Setup;
   SPI_Config.Clock_Rate = Normal_Fosc_16;
   SPI_Config.Speed = SPI_Speed_Normal;
   SPI_Config.IRQ_Enable = SPI_IRQ_Disable;
   SPI_Config.Ptr_ISR_Func = 0;

   MCAL_SPI_Init(SPI_PORT, &SPI_Config);
   MCAL_SPI_IO_Set_Pins(SPI_PORT);

   for(uint8_t i=0;i<8;i++){
	   IO_Configure_Pin_t pinConf = {1<<i, output_Low};
	   MCAL_IO_Init(IOA, &pinConf);
	  
}
   }
/* Read data from Master */
void App_Run(void)
{
    MCAL_IO_WritePort(IOA, counter);

    MCAL_SPI_SendReceive(SPI_PORT, counter);

    counter++;
	
    if(counter > 9) counter = 1;
	
   Delay_ms(1000);
}
   