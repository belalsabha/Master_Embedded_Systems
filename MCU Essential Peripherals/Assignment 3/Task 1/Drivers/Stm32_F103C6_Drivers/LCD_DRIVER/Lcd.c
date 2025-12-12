/*
 * Lcd.c
 *
 *  Created on: Dec 10, 2025
 *  Author: Belal Hani Sabha
 */
#include "Lcd.h"

void _delay_ms(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}

void LCD_GPIOx_Init(void)
{
	// Init Control Ports E ,RW , RS

		PinConfig.GPOI_Pin_Number = Register_Select;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = Read_Write;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = Enable;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);


	// Init Data Ports (D0-D7)

		PinConfig.GPOI_Pin_Number = GPIO_PIN0;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN1;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN2;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN3;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN4;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN5;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN6;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN7;
		PinConfig.GPIO_Mode = output_push_pull;
		PinConfig.GPIO_Output_Frequency = Frequency_10MHz;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);


	MCAL_GPIO_WritePin(LCD_Control_PORTS, Enable, 			RESET_PIN);
	MCAL_GPIO_WritePin(LCD_Control_PORTS, Register_Select,  RESET_PIN);
	MCAL_GPIO_WritePin(LCD_Control_PORTS, Read_Write, 		RESET_PIN);

}

void LCD_Init(void){
	_delay_ms(20);
	LCD_GPIOx_Init();
	_delay_ms(10);
	Clear_LCD_Screen();
	Write_Command_onLCD(LCD_FUNCTION_8BIT_2LINES);
	Write_Command_onLCD(LCD_ENTRY_MODE);
	Write_Command_onLCD(LCD_BEGIN_AT_FIRST_ROW);
	Write_Command_onLCD(LCD_DISP_ON_CURSOR_BLINK);
}

void IS_LCD_Busy(void){

		PinConfig.GPOI_Pin_Number = GPIO_PIN0;
		PinConfig.GPIO_Mode = GPIO_Floating_Input;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN1;
		PinConfig.GPIO_Mode = GPIO_Floating_Input;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN2;
		PinConfig.GPIO_Mode = GPIO_Floating_Input;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN3;
		PinConfig.GPIO_Mode = GPIO_Floating_Input;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN4;
		PinConfig.GPIO_Mode = GPIO_Floating_Input;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN5;
		PinConfig.GPIO_Mode = GPIO_Floating_Input;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN6;
		PinConfig.GPIO_Mode = GPIO_Floating_Input;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);

		PinConfig.GPOI_Pin_Number = GPIO_PIN7;
		PinConfig.GPIO_Mode = GPIO_Floating_Input;
		MCAL_GPIO_Init(LCD_Control_PORTS, &PinConfig);


	MCAL_GPIO_WritePin(LCD_Control_PORTS, Read_Write, SET_PIN);
	MCAL_GPIO_WritePin(LCD_Control_PORTS, Register_Select, RESET_PIN);
	Send_Pulse_toLCD();
	MCAL_GPIO_WritePin(LCD_Control_PORTS, Read_Write, RESET_PIN);
}

void Send_Pulse_toLCD(void){
	MCAL_GPIO_WritePin(LCD_Control_PORTS, Enable, SET_PIN);
	_delay_ms(50);
	MCAL_GPIO_WritePin(LCD_Control_PORTS, Enable, RESET_PIN);
	_delay_ms(50);
}

void Clear_LCD_Screen(void){
	Write_Command_onLCD(LCD_CLEAR_SCREEN);
}

void Write_Command_onLCD(uint8_t Command){
	//IS_LCD_Busy();
	MCAL_GPIO_WritePort(LCD_Control_PORTS, Command);
	MCAL_GPIO_WritePin(LCD_Control_PORTS, Read_Write, RESET_PIN);
	MCAL_GPIO_WritePin(LCD_Control_PORTS, Register_Select, RESET_PIN);
	_delay_ms(1);
	Send_Pulse_toLCD();
}

void Write_Character_onLCD(uint8_t Character){
	//IS_LCD_Busy();
	MCAL_GPIO_WritePort(LCD_Control_PORTS, Character);
	MCAL_GPIO_WritePin(LCD_Control_PORTS, Read_Write, RESET_PIN);
	MCAL_GPIO_WritePin(LCD_Control_PORTS, Register_Select, SET_PIN);


	_delay_ms(10);
	Send_Pulse_toLCD();
}

void Write_String_onLCD(uint8_t *String){
	uint32_t counter = 0 ;
	while (*String > 0 ){
		counter++;
		Write_Character_onLCD(*String++);

		if(counter == 16){
			Control_LCD_Lines_And_Cursor(2,0);
		}
		else if (counter == 32 ){
			Clear_LCD_Screen();
			Control_LCD_Lines_And_Cursor(1,0);
			counter=0;
		}
	}
}

void Control_LCD_Lines_And_Cursor(uint8_t LINE , uint8_t CURSOR){
	if (LINE == 1){
		if (CURSOR < 16 && CURSOR >= 0){
			Write_Command_onLCD(LCD_BEGIN_AT_FIRST_ROW+CURSOR);
		}
	}
	if (LINE == 2){
		if (CURSOR < 16 && CURSOR >= 0){
			Write_Command_onLCD(LCD_BEGIN_AT_SECOND_ROW+CURSOR);
		}
	}
}

void Display_Number_onLCD(uint32_t NUMBER){
	uint8_t str[11];
	sprintf(str,"%lu",NUMBER);
	Write_String_onLCD(str);
}

void Display_RealNumber_onnLCD(float NUMBER){
	char buffer[16];
	int INTEGER_PART = (int)NUMBER;
	int FRACTION_PART = (NUMBER - INTEGER_PART) * 1000;
	if(FRACTION_PART < 0)
		FRACTION_PART = -FRACTION_PART;
	sprintf(buffer, "%d.%03d", INTEGER_PART, FRACTION_PART );
	Write_String_onLCD(buffer);
}
