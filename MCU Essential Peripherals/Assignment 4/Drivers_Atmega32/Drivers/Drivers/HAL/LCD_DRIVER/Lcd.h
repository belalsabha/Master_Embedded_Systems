/*
 * Lcd.h
 *
 * Created: 14 / 12 /2025
 * Author : Belal Hani Sabha
 */ 





#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include "Atmega32.h"
#include "IO.h"



#define _delay_ms(x) { \
	unsigned int i,j; \
	for(i=0;i<x;i++) for(j=0;j<255;j++); \
}



// LCD commands 
#define LCD_FUNCTION_4BIT_2LINES        0x28
#define LCD_ENTRY_MODE                  0x06
#define LCD_BEGIN_AT_FIRST_ROW          0x80
#define LCD_BEGIN_AT_SECOND_ROW         0xC0
#define LCD_DISP_ON_CURSOR_BLINK        0x0F
#define LCD_CLEAR_SCREEN                0x01

#define LCD_DATA_PORTS					IOA
#define LCD_CONTROL_PORTS				IOB

#define Register_Select					IO_PIN1
#define Read_Write						IO_PIN2
#define Enable							IO_PIN3

void LCD_Init(void);
void Send_Pulse_toLCD(void);
void Clear_LCD_Screen(void);
void Write_Command_onLCD(uint8_t Command);
void Write_Character_onLCD(uint8_t Character);
void Write_String_onLCD(uint8_t *String);
void Control_LCD_Lines_And_Cursor(uint8_t LINE, uint8_t CURSOR);

#endif /* LCD_H_ */
