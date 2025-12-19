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

volatile uint8_t irq0_flag = 0;

void IRQ0_Callback() {
	irq0_flag = 1;
}

// Simple delay
void delay_ms(int x) {
	unsigned int i, j;
	for (i = 0; i < x; i++)
	for (j = 0; j < 255; j++);
}

/* For  Atmega32 Simulation */ 
// int main(void) {
// 	
// 	
// 	LCD_Init();
// 	Init_7Segment();
// 	
// 	SREG |= 1<< 7; // Enable global interrupts
// 
// 	EXTI_Configure_Pin_t EXTIx;
// 	EXTIx.EXTI_PIN = EXTI0PD2;
// 	EXTIx.EDGE_CASE = RISING_EDGE;
// 	EXTIx.IRQ_E_D = ENABLE_IRQ_EXTI;
// 	EXTIx.P_IRQ_FUNC_CALLBACK = IRQ0_Callback;
// 
// 	MCAL_EXTI_IO_Init(&EXTIx);
// 
// 	
// 
// 	while (1) {
// 		
// 		if (irq0_flag) {
// 			
// 			irq0_flag = 0;
// 			Write_String_onLCD("IRQ0 Enabled");
// 			delay_ms(5000);
// 			Clear_LCD_Screen();
// 			
// 		}
// 	}
// }

// For Amit kit Simulation
int main(void){
	uint8_t counter = 9 ;
	LCD_Init();
	Init_7Segment();

	while(1){
		Write_String_onLCD("Hello.....!");
        for ( ; counter < 10 ; counter--)
        {
			DisplayNumber_on_7Segment(counter);
			_delay_ms(1000);
        }
		
    	_delay_ms(100);
		
		Clear_LCD_Screen();
		counter = 9 ;
	}
	return 0;
}