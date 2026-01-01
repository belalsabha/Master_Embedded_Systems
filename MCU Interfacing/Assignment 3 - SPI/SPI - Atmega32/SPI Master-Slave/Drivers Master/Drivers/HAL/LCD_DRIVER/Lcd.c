/*
 *  Lcd.c
 *
 * Created: 14 / 12 /2025
 * Author : Belal Hani Sabha
 */ 

#include "LCD.h"






void LCD_IO_init(){
	IO_Configure_Pin_t PinNumber_Configuration;

	//init  Control pins as output
	PinNumber_Configuration.IO_Pin_Number = Register_Select;
	PinNumber_Configuration.IO_Mode = output_Low;
	MCAL_IO_Init(IOB, &PinNumber_Configuration);

	PinNumber_Configuration.IO_Pin_Number = Read_Write;
	PinNumber_Configuration.IO_Mode = output_Low;
	MCAL_IO_Init(IOB, &PinNumber_Configuration);

	PinNumber_Configuration.IO_Pin_Number = Enable;
	PinNumber_Configuration.IO_Mode = output_Low;
	MCAL_IO_Init(IOB, &PinNumber_Configuration);



	//init  Data pins as low output
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



	// write 0 om control pins
	MCAL_IO_WritePin(IOB, Enable, RESET_PIN);
	MCAL_IO_WritePin(IOB, Register_Select, RESET_PIN);
	MCAL_IO_WritePin(IOB, Read_Write, RESET_PIN);
	
}
void LCD_Init(void){
	_delay_ms(20);
	LCD_IO_init();
	Clear_LCD_Screen();
	Write_Command_onLCD(0x02);
	Write_Command_onLCD(LCD_FUNCTION_4BIT_2LINES);
	Write_Command_onLCD(LCD_ENTRY_MODE);
	Write_Command_onLCD(LCD_BEGIN_AT_FIRST_ROW);
	Write_Command_onLCD(LCD_DISP_ON_CURSOR_BLINK);
}

void Send_Pulse_toLCD(void){
	MCAL_IO_WritePin(LCD_CONTROL_PORTS, Enable, RESET_PIN);
	_delay_ms(2);
	MCAL_IO_WritePin(LCD_CONTROL_PORTS, Enable, SET_PIN);
	_delay_ms(2);
}

void Clear_LCD_Screen(void){
	Write_Command_onLCD(LCD_CLEAR_SCREEN);
}

void Write_Command_onLCD(uint8_t Command){
	LCD_DATA_PORTS->PORT = (LCD_DATA_PORTS->PORT & 0x0F) | (Command & 0xF0);
	MCAL_IO_WritePin(LCD_CONTROL_PORTS, Register_Select, RESET_PIN);
	MCAL_IO_WritePin(LCD_CONTROL_PORTS, Read_Write, RESET_PIN);
	Send_Pulse_toLCD();

	LCD_DATA_PORTS->PORT = (LCD_DATA_PORTS->PORT & 0x0F) | ((Command << 4) & 0xF0);
	MCAL_IO_WritePin(LCD_CONTROL_PORTS, Register_Select, RESET_PIN);
	MCAL_IO_WritePin(LCD_CONTROL_PORTS, Read_Write, RESET_PIN);
	Send_Pulse_toLCD();
}

void Write_Character_onLCD(uint8_t Character){
	LCD_DATA_PORTS->PORT = (LCD_DATA_PORTS->PORT & 0x0F) | (Character & 0xF0);
	MCAL_IO_WritePin(LCD_CONTROL_PORTS, Register_Select, SET_PIN);
	MCAL_IO_WritePin(LCD_CONTROL_PORTS, Read_Write, RESET_PIN);
	Send_Pulse_toLCD();

	LCD_DATA_PORTS->PORT = (LCD_DATA_PORTS->PORT & 0x0F) | ((Character << 4) & 0xF0);
	MCAL_IO_WritePin(LCD_CONTROL_PORTS, Register_Select, SET_PIN);
	MCAL_IO_WritePin(LCD_CONTROL_PORTS, Read_Write, RESET_PIN);
	Send_Pulse_toLCD();
}

void Write_String_onLCD(uint8_t *String){
	uint32_t counter = 0;
	while(*String > 0){
		counter++;
		Write_Character_onLCD(*String++);
		if(counter == 16) Control_LCD_Lines_And_Cursor(2,0);
		if(counter == 32){
			Clear_LCD_Screen();
			Control_LCD_Lines_And_Cursor(1,0);
			counter = 0;
		}
	}
}

void Control_LCD_Lines_And_Cursor(uint8_t LINE, uint8_t CURSOR){
	if(LINE == 1 && CURSOR < 16)
	Write_Command_onLCD(LCD_BEGIN_AT_FIRST_ROW + CURSOR);
	if(LINE == 2 && CURSOR < 16)
	Write_Command_onLCD(LCD_BEGIN_AT_SECOND_ROW + CURSOR);
}
