/*
 * Lcd.h
 *
 *  Created on: Dec 10, 2025
 *  Author: Belal Hani Sabha
 */

#ifndef LCD_H_
#define LCD_H_

#include "GPIO.h"
#include <stdlib.h>
#include <stdint.h>
#include "Stm32f103x6.h"


//commands for LCD
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)

#define   LCD_Control_PORTS        GPIOA
#define   DATA_shift                   4   // = 0 in 8-bit mode and 4 in 4-bit mode

#define   Register_Select	 GPIO_PIN8
#define   Read_Write     	 GPIO_PIN9
#define   Enable          	 GPIO_PIN10

//-------------------------------------------------------
GPIO_Configure_Pin_t PinConfig ;

//-------------------------------------------------------
void LCD_Init(void);
void LCD_GPIOx_Init(void);
void IS_LCD_Busy(void);
void Send_Pulse_toLCD(void);
void Clear_LCD_Screen(void);
void Write_Command_onLCD(uint8_t Command);
void Write_Character_onLCD(uint8_t Character);
void Write_String_onLCD(uint8_t *String);
void Control_LCD_Lines_And_Cursor(uint8_t LINE , uint8_t CURSOR);
void Display_Number_onLCD(uint32_t NUMBER);
void Display_RealNumber_onnLCD(float NUMBER);

#endif /* LCD_H_ */
