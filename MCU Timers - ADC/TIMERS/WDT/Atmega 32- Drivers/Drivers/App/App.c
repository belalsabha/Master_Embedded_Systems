/*
 * App.c
 *
 * Created: 28/12/2025
 * Author : Belal Hani Sabha
 */

#include "App.h"


/* Simple delay */
void Delay_ms(uint16_t ms)
{
    volatile uint16_t i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1000; j++);
}
	WDT_Config_t WDTConfig ;
/* ================= App Initialization ================= */
void App_Init(void)
{
	IO_Configure_Pin_t PinNumber_Configuration ;
	PinNumber_Configuration.IO_Pin_Number =  IO_PIN0 ;
	PinNumber_Configuration.IO_Mode = 	output_Hight ;
	MCAL_IO_Init( IOC,  &PinNumber_Configuration);
	MCAL_IO_WritePin(IOC , IO_PIN0 , SET_PIN);
	Delay_ms(100);

	
	

	WDTConfig.Watchdog_Status=WDT_Enable;
	WDTConfig.Prescaler = WDT_PRESCALER_1s;
	
	
	
}

/* ================= App Main Loop ================= */
void App_Run(void)
{
			WDT_Init(WDT ,&WDTConfig);
			Delay_ms(500);
			MCAL_IO_WritePin(IOC , IO_PIN0 , RESET_PIN);
			Delay_ms(2000);
			WDT_DeInit(WDT);
			MCAL_IO_WritePin(IOC , IO_PIN0 , SET_PIN);
			Delay_ms(2000);

	
}
