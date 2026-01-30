/*
 * Lcd.c
 *
 *  Created on: Jan 22, 2025
 *  Developer & Tester : Eng - Belal Hani Sabha
 *  LCD Type : LM016 16*2
 */

//----------------------------------
//Includes
//----------------------------------
#include "LCD.h"

//----------------------------------
//Global Variables
//----------------------------------
GPIO_Configure_Pin_t PinConfig;


//----------------------------------
//Prototypes
//----------------------------------
//Simple Delay
void delay_ms(uint32_t time){
	uint32_t i,j;
	for(i=0;i<time;i++)
		for(j=0;j<255;j++);
}


//----------------------------------
//APIs IMPLEMENTATION
//----------------------------------

// Send Pulse to LCD to write Data
void HAL_Send_Pulse_toLCD(LCD_Configure_t* lcd){
	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->EN_Pin, SET_PIN);
	delay_ms(1);
	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->EN_Pin, RESET_PIN);
	delay_ms(1);
}

// Send 4 bit to lcd
void HAL_LCD_Send4Bits(LCD_Configure_t* lcd, uint8_t nibble){
	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->DataPins[0], (nibble >> 0) & 1);
	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->DataPins[1], (nibble >> 1) & 1);
	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->DataPins[2], (nibble >> 2) & 1);
	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->DataPins[3], (nibble >> 3) & 1);
	HAL_Send_Pulse_toLCD(lcd);
}

//init GPIOx Pins that connected to LCD Pins
void HAL_LCD_GPIOx_Init(LCD_Configure_t* lcd){

	PinConfig.GPIO_Mode = output_push_pull;
	PinConfig.GPIO_Output_Frequency = Frequency_10MHz;

	//Control Pins
	PinConfig.GPOI_Pin_Number = lcd->RS_Pin;
	MCAL_GPIO_Init(lcd->LCD_Port, &PinConfig);

	PinConfig.GPOI_Pin_Number = lcd->RW_Pin;
	MCAL_GPIO_Init(lcd->LCD_Port, &PinConfig);

	PinConfig.GPOI_Pin_Number = lcd->EN_Pin;
	MCAL_GPIO_Init(lcd->LCD_Port, &PinConfig);

	// Data Pins
	if(lcd->Mode == LCD_MODE_8BIT){

		PinConfig.GPOI_Pin_Number = lcd->DataPins[0]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
		PinConfig.GPOI_Pin_Number = lcd->DataPins[1]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
		PinConfig.GPOI_Pin_Number = lcd->DataPins[2]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
		PinConfig.GPOI_Pin_Number = lcd->DataPins[3]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
		PinConfig.GPOI_Pin_Number = lcd->DataPins[4]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
		PinConfig.GPOI_Pin_Number = lcd->DataPins[5]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
		PinConfig.GPOI_Pin_Number = lcd->DataPins[6]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
		PinConfig.GPOI_Pin_Number = lcd->DataPins[7]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);

	} else {

		PinConfig.GPOI_Pin_Number = lcd->DataPins[0]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
		PinConfig.GPOI_Pin_Number = lcd->DataPins[1]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
		PinConfig.GPOI_Pin_Number = lcd->DataPins[2]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
		PinConfig.GPOI_Pin_Number = lcd->DataPins[3]; MCAL_GPIO_Init(lcd->LCD_Port,&PinConfig);
	}

	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->RS_Pin, RESET_PIN);
	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->RW_Pin, RESET_PIN);
	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->EN_Pin, RESET_PIN);
}

// Init LCD
void HAL_LCD_Init(LCD_Configure_t* lcd){
	delay_ms(20);
	HAL_LCD_GPIOx_Init(lcd);

	if(lcd->Mode == LCD_MODE_8BIT){
		HAL_Write_Command_onLCD(lcd, LCD_FUNCTION_8BIT_2LINES);
	} else {
		HAL_LCD_Send4Bits(lcd, 0x03); delay_ms(5);
		HAL_LCD_Send4Bits(lcd, 0x03); delay_ms(1);
		HAL_LCD_Send4Bits(lcd, 0x03); delay_ms(1);
		HAL_LCD_Send4Bits(lcd, 0x02);
		HAL_Write_Command_onLCD(lcd, LCD_FUNCTION_4BIT_2LINES);
	}

	HAL_Write_Command_onLCD(lcd, LCD_ENTRY_MODE);
	HAL_Write_Command_onLCD(lcd, LCD_DISP_ON_CURSOR_BLINK);
	HAL_Clear_LCD_Screen(lcd);
}

// Send Command to LCD
void HAL_Write_Command_onLCD(LCD_Configure_t* lcd, uint8_t Command){

	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->RS_Pin, RESET_PIN);
	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->RW_Pin, RESET_PIN);

	if(lcd->Mode == LCD_MODE_8BIT){

		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[0],(Command>>0)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[1],(Command>>1)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[2],(Command>>2)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[3],(Command>>3)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[4],(Command>>4)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[5],(Command>>5)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[6],(Command>>6)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[7],(Command>>7)&1);

		HAL_Send_Pulse_toLCD(lcd);
	} else {
		HAL_LCD_Send4Bits(lcd, Command >> 4);
		HAL_LCD_Send4Bits(lcd, Command & 0x0F);
	}
}

// Send Character to LCD
void HAL_Write_Character_onLCD(LCD_Configure_t* lcd, uint8_t Character){

	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->RS_Pin, SET_PIN);
	MCAL_GPIO_WritePin(lcd->LCD_Port, lcd->RW_Pin, RESET_PIN);

	if(lcd->Mode == LCD_MODE_8BIT){

		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[0],(Character>>0)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[1],(Character>>1)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[2],(Character>>2)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[3],(Character>>3)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[4],(Character>>4)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[5],(Character>>5)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[6],(Character>>6)&1);
		MCAL_GPIO_WritePin(lcd->LCD_Port,lcd->DataPins[7],(Character>>7)&1);

		HAL_Send_Pulse_toLCD(lcd);
	} else {
		HAL_LCD_Send4Bits(lcd, Character >> 4);
		HAL_LCD_Send4Bits(lcd, Character & 0x0F);
	}
}

// Send String to LCD
void HAL_Write_String_onLCD(LCD_Configure_t* lcd, uint8_t* String){
	uint32_t counter = 0;
	while(*String){
		counter++;
		HAL_Write_Character_onLCD(lcd,*String++);
		if(counter==16)  HAL_Control_LCD_Lines_And_Cursor(lcd,2,0);
		else if(counter==32){
			HAL_Clear_LCD_Screen(lcd);
			HAL_Control_LCD_Lines_And_Cursor(lcd,1,0);
			counter=0;
		}
	}
}

// Control LCD Cursor
void HAL_Control_LCD_Lines_And_Cursor(LCD_Configure_t* lcd, uint8_t LINE, uint8_t CURSOR){
	if(LINE==1 && CURSOR<16)
		HAL_Write_Command_onLCD(lcd,LCD_BEGIN_AT_FIRST_ROW+CURSOR);
	else if(LINE==2 && CURSOR<16)
		HAL_Write_Command_onLCD(lcd,LCD_BEGIN_AT_SECOND_ROW+CURSOR);
}

// Clear LCD Screen
void HAL_Clear_LCD_Screen(LCD_Configure_t* lcd){
	HAL_Write_Command_onLCD(lcd,LCD_CLEAR_SCREEN);
}

// Send uint32 Number to LCD
void HAL_Display_Number_onLCD(LCD_Configure_t* lcd,uint32_t NUMBER){
	uint8_t str[11];
	sprintf((char*)str,"%lu",NUMBER);
	HAL_Write_String_onLCD(lcd,str);
}

// Send Float Number to LCD
void HAL_Display_RealNumber_onLCD(LCD_Configure_t* lcd,float NUMBER){
	uint8_t buffer[16];
	uint32_t INTEGER_PART = (uint32_t)NUMBER;
	uint32_t FRACTION_PART = (NUMBER - INTEGER_PART) * 1000;
	if(FRACTION_PART < 0) FRACTION_PART = -FRACTION_PART;

	sprintf((char*)buffer,"%lu.%01ld",INTEGER_PART,FRACTION_PART);
	HAL_Write_String_onLCD(lcd,buffer);}
