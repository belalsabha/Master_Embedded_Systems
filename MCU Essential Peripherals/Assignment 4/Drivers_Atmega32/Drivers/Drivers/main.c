/*
 * main.c
 *
 * Created: 14 / 12 /2025
 * Author : Belal Hani Sabha
 */ 

#include "Atmega32.h"
#include "IO.h"
#include "LCD.h"
#include "Seven_Segment.h"

typedef unsigned char uint8_t ;

void _delay_ms_(int x){
	unsigned int i,j;
	for(i=0;i<x;i++){
		for(j=0;j<255;j++);
	}
}

void IO_init(){
	IO_Configure_Pin_t PinNumber_Configuration;

	// Control pins
	PinNumber_Configuration.IO_Pin_Number = Register_Select;
	PinNumber_Configuration.IO_Mode = output_Low;
	MCAL_IO_Init(&IOB, &PinNumber_Configuration);

	PinNumber_Configuration.IO_Pin_Number = Read_Write;
	MCAL_IO_Init(&IOB, &PinNumber_Configuration);

	PinNumber_Configuration.IO_Pin_Number = Enable;
	MCAL_IO_Init(&IOB, &PinNumber_Configuration);

	// Data pins
	PinNumber_Configuration.IO_Pin_Number = IO_PIN4;
	MCAL_IO_Init(&IOA, &PinNumber_Configuration);

	PinNumber_Configuration.IO_Pin_Number = IO_PIN5;
	MCAL_IO_Init(&IOA, &PinNumber_Configuration);

	PinNumber_Configuration.IO_Pin_Number = IO_PIN6;
	MCAL_IO_Init(&IOA, &PinNumber_Configuration);

	PinNumber_Configuration.IO_Pin_Number = IO_PIN7;
	MCAL_IO_Init(&IOA, &PinNumber_Configuration);

	// init Control pins as low
	MCAL_GPIO_WritePin(&IOB, Enable, RESET_PIN);
	MCAL_GPIO_WritePin(&IOB, Register_Select, RESET_PIN);
	MCAL_GPIO_WritePin(&IOB, Read_Write, RESET_PIN);
}

int main(void){
	uint8_t counter ;
	IO_init();
	LCD_Init();
	//Init_7Segment();

	while(1){
        Write_String_onLCD("Hello.....!");

 

        _delay_ms(100);
   
       Clear_LCD_Screen();
	}
	return 0;
}
