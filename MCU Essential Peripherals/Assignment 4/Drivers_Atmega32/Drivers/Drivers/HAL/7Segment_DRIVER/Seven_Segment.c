
/*
 * Seven_Segment.c
 * Created on: Dec 14, 2025
 * Author: Belal Hani Sabha
 */

#include "Seven_Segment.h"
#include "Atmega32.h"

typedef unsigned char uint8_t;

 uint8_t SEG_7_NUM[10]= {
	0b0011, // 0
	0b0001, // 1
	0b1011, // 2
	0b1010, // 3
	0b0110, // 4
	0b1100, // 5
	0b1101, // 6
	0b0010, // 7
	0b1111, // 8
	0b1110  // 9
};


void Init_7Segment(void){
	IO_Configure_Pin_t PinCnfg;
	PinCnfg.IO_Mode = output_Low;

	// Segment pins (PORTC 4-7)
	for(uint8_t pin = SEG_A; pin <= SEG_D; pin <<= 1){
		PinCnfg.IO_Pin_Number = pin;
		MCAL_IO_Init(&IOC, &PinCnfg);
	}

	// Enable pins (PORTC 2-3)
	PinCnfg.IO_Pin_Number = EN1;
	 MCAL_IO_Init(&IOC, &PinCnfg);
	PinCnfg.IO_Pin_Number = EN2;
	 MCAL_IO_Init(&IOC, &PinCnfg);

	// Decimal point (PORTB PIN0)
	PinCnfg.IO_Pin_Number = DP; 
	MCAL_IO_Init(&IOB, &PinCnfg);

	// Set all LOW initially
	MCAL_GPIO_WritePin(&IOC, SEG_A, RESET_PIN);
	MCAL_GPIO_WritePin(&IOC, SEG_B, RESET_PIN);
	MCAL_GPIO_WritePin(&IOC, SEG_C, RESET_PIN);
	MCAL_GPIO_WritePin(&IOC, SEG_D, RESET_PIN);
	MCAL_GPIO_WritePin(&IOB, DP   ,	RESET_PIN);
	MCAL_GPIO_WritePin(&IOC, EN1  , RESET_PIN);
	MCAL_GPIO_WritePin(&IOC, EN2  ,	RESET_PIN);
}

void DisplayNumber_on_7Segment(uint8_t num){
	uint8_t value = SEG_7_NUM[num % 10];

	MCAL_GPIO_WritePin(&IOC, SEG_A, (value>>0)&1);
	MCAL_GPIO_WritePin(&IOC, SEG_B, (value>>1)&1);
	MCAL_GPIO_WritePin(&IOC, SEG_C, (value>>2)&1);
	MCAL_GPIO_WritePin(&IOC, SEG_D, (value>>3)&1);
}

// Enable specific 7-segment
void Enable_7Segment(uint8_t seg){
	MCAL_GPIO_WritePin(&IOC, EN1, (seg==1)?SET_PIN:RESET_PIN);
	MCAL_GPIO_WritePin(&IOC, EN2, (seg==2)?SET_PIN:RESET_PIN);
}
