/*
 * App.c
 *
 * Created: 28 / 12 /2025
 * Author : Belal Hani Sabha
 */

#include "App.h"

void Delay_ms(uint16_t ms)
{
	volatile uint16_t i, j;
	for(i = 0; i < ms; i++)
	{
		for(j = 0; j < 1000; j++)
		{
		}
	}
}

		uint8_t data , x=0;
		uint8_t data_string [10]  ;

void App_Init(){
	

		LCD_Init();
		USART_Config_t USART_Config;
		
		USART_Config.USART_Mode=USART_Mode_TX_RX_Enable;
		USART_Config.Mode_Select= USART_Mode_Asynchronous;
		USART_Config.BaudRate=USART_BaudRate_9600;
		USART_Config.DataSize =USART_DataSize_8bit;
		USART_Config.Parity=USART_Parity_Disable;
		USART_Config.StopBitNo=USART_StopBitNo_1;
		USART_Config.Speed = USART_Speed_Normal;
		USART_Config.IRQ_Enable =USART_IRQ_Disable;
		USART_Config.Ptr_ISR_Func = NULL;
		MCAL_USART_Init(USART, &USART_Config);
		
		Write_String_onLCD("USART TX Mode:");
		 Delay_ms(500);
		 
		MCAL_USART_Send_String("Welcome...");
		
		Clear_LCD_Screen();
		
		Write_String_onLCD("USART RX Mode:");
		
		 Delay_ms(500);
		 
		Clear_LCD_Screen();
	
	
		//  	Write_String_onLCD("USART TX....");
		//  	Control_LCD_Lines_And_Cursor(2,0);
		//  	MCAL_USART_Send_Char ('B');
		// 		MCAL_USART_Send_Char ('E');
		// 		MCAL_USART_Send_Char ('L');
		// 		MCAL_USART_Send_Char ('A');
		// 		MCAL_USART_Send_Char ('L');
	
	
}
void App_Run(){
	
	//  		data = MCAL_USART_Recieve_Char ();
	//  		Write_Character_onLCD(data);
			MCAL_USART_Recieve_String(data_string);
			Write_String_onLCD(data_string);
		

	
}