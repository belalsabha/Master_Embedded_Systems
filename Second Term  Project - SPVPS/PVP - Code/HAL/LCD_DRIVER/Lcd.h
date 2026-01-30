/*
 * Lcd.h
 *
 *  Created on: Jan 22, 2026
 *  Developer & Tester : Eng - Belal Hani Sabha
 *  LCD Type : LM016     16*2
 */

#ifndef LCD_H_
#define LCD_H_

//----------------------------------
//Includes
//----------------------------------
#include "PLATFORM_TYPES.h"
#include "Stm32f103x6.h"
#include "GPIO.h"


//----------------------------------
//Macros
//----------------------------------
//commands for LCD
#define LCD_FUNCTION_8BIT_2LINES     (0x38)
#define LCD_FUNCTION_4BIT_2LINES     (0x28)
#define LCD_MOVE_DISP_RIGHT          (0x1C)
#define LCD_MOVE_DISP_LEFT           (0x18)
#define LCD_MOVE_CURSOR_RIGHT        (0x14)
#define LCD_MOVE_CURSOR_LEFT         (0x10)
#define LCD_DISP_OFF                 (0x08)
#define LCD_DISP_ON_CURSOR           (0x0E)
#define LCD_DISP_ON_CURSOR_BLINK     (0x0F)
#define LCD_DISP_ON_BLINK            (0x0D)
#define LCD_DISP_ON                  (0x0C)
#define LCD_ENTRY_DEC                (0x04)
#define LCD_ENTRY_DEC_SHIFT          (0x05)
#define LCD_ENTRY_INC                (0x06)
#define LCD_ENTRY_INC_SHIFT          (0x07)
#define LCD_BEGIN_AT_FIRST_ROW       (0x80)
#define LCD_BEGIN_AT_SECOND_ROW      (0xC0)
#define LCD_CLEAR_SCREEN             (0x01)
#define LCD_ENTRY_MODE               (0x06)
// Modes
#define LCD_MODE_8BIT   1
#define LCD_MODE_4BIT   0




//----------------------------------
//User type definitions (structures for LCD)
//----------------------------------
typedef struct {
	GPIOx_t* LCD_Port;   	   // Select LCD Port
    uint16_t RS_Pin;           // Select Register Select Pin
    uint16_t RW_Pin;           // Select Read/Write Pin
    uint16_t EN_Pin;           // Select Enable Pin
    uint8_t  Mode;             // Select Mode ( 0 in 8-bit mode ,  4 in 4-bit mode )
    uint16_t DataPins[8];      // Select Data Pin Depending on LCD Mode
}LCD_Configure_t;


/*
 * =======================================================================================
 * 							APIs Supported by "HAL LCD DRIVER"
 * =======================================================================================
 */
void HAL_LCD_Init(LCD_Configure_t* lcd);
void HAL_LCD_GPIOx_Init(LCD_Configure_t* lcd);
void HAL_Send_Pulse_toLCD(LCD_Configure_t* lcd);
void HAL_LCD_Send4Bits(LCD_Configure_t* lcd, uint8_t nibble);
void HAL_Write_Command_onLCD(LCD_Configure_t* lcd, uint8_t Command);
void HAL_Write_Character_onLCD(LCD_Configure_t* lcd, uint8_t Character);
void HAL_Write_String_onLCD(LCD_Configure_t* lcd, uint8_t* String);
void HAL_Control_LCD_Lines_And_Cursor(LCD_Configure_t* lcd, uint8_t LINE, uint8_t CURSOR);
void HAL_Clear_LCD_Screen(LCD_Configure_t* lcd);
void HAL_Display_Number_onLCD(LCD_Configure_t* lcd, uint32_t NUMBER);
void HAL_Display_RealNumber_onLCD(LCD_Configure_t* lcd, float NUMBER);


#endif /* LCD_H_ */
