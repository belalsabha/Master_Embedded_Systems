/*
 * main.c
 *
 * Created: 19 / 12 /2025
 * Author : Belal Hani Sabha
 */ 

#include "Atmega32.h"
#include "IO.h"
#include "LCD.h"
#include "Seven_Segment.h"
#include "EXTI.h"
#include "USART.h"



/* For  Atmega32 Simulation */ 
int main(void) {
	
	uint8_t data ;
	uint8_t data_string [10]  ;
	LCD_Init();
	MCAL_USART_Init ();
	

//  	Write_String_onLCD("USART TX....");
//  	Control_LCD_Lines_And_Cursor(2,0);   
//  	MCAL_USART_Send_Char ('B');
// 		MCAL_USART_Send_Char ('E');
// 		MCAL_USART_Send_Char ('L');
// 		MCAL_USART_Send_Char ('A');
// 		MCAL_USART_Send_Char ('L');
	while (1) {
			
//  		data = MCAL_USART_Recieve_Char ();
//  		Write_Character_onLCD(data);
// 
	 			MCAL_USART_Recieve_String(data_string);
				Control_LCD_Lines_And_Cursor(2,0);
 				Write_String_onLCD(data_string);
			
				

	}
}


