
/*
 * Seven_Segment.c
 * Created on: Dec 14, 2025
 * Author: Belal Hani Sabha
 */

#include "Seven_Segment.h"
#include "Atmega32.h"

typedef unsigned char uint8_t;

void Init_7Segment(){
	IO_Configure_Pin_t PinNumber_Configuration;
	
	//init   Segment pins (PORTC 4-7)
	PinNumber_Configuration.IO_Pin_Number = IO_PIN4;
	PinNumber_Configuration.IO_Mode = output_Low;
	MCAL_IO_Init(IOA, &PinNumber_Configuration);

	PinNumber_Configuration.IO_Pin_Number = IO_PIN5;
	PinNumber_Configuration.IO_Mode = output_Low;
	MCAL_IO_Init(IOA, &PinNumber_Configuration);

	PinNumber_Configuration.IO_Pin_Number = IO_PIN6;
	PinNumber_Configuration.IO_Mode = output_Low;
	MCAL_IO_Init(IOA, &PinNumber_Configuration);

	PinNumber_Configuration.IO_Pin_Number = IO_PIN7;
	PinNumber_Configuration.IO_Mode = output_Low;
	MCAL_IO_Init(IOA, &PinNumber_Configuration);

	// Enable pins (PORTC 2-3)
	PinNumber_Configuration.IO_Pin_Number = EN1;
	PinNumber_Configuration.IO_Mode = output_Low;
	MCAL_IO_Init(IOC, &PinNumber_Configuration);
	PinNumber_Configuration.IO_Pin_Number = EN2;
	PinNumber_Configuration.IO_Mode = output_Low;
	 MCAL_IO_Init(IOC, &PinNumber_Configuration);


	// Set all LOW initially
	// just clear any on IOC pins 
	MCAL_IO_WritePin(IOC, A, RESET_PIN);
	MCAL_IO_WritePin(IOC, B, RESET_PIN);
	MCAL_IO_WritePin(IOC, C, RESET_PIN);
	MCAL_IO_WritePin(IOC, D, RESET_PIN);
	MCAL_IO_WritePin(IOC, EN1  , RESET_PIN);
	MCAL_IO_WritePin(IOC, EN2  ,	RESET_PIN);
	
	// Enable specific 7-segment
	MCAL_IO_WritePin(IOC, EN1, SET_PIN);
	MCAL_IO_WritePin(IOC, EN2, SET_PIN);
}

void DisplayNumber_on_7Segment(uint8_t num){
	uint8_t DISPLAY [11] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

	uint8_t value = DISPLAY[num];

	MCAL_IO_WritePin(IOC, A, (value>>0)&1);
	MCAL_IO_WritePin(IOC, B, (value>>1)&1);
	MCAL_IO_WritePin(IOC, C, (value>>2)&1);
	MCAL_IO_WritePin(IOC, D, (value>>3)&1);
}


