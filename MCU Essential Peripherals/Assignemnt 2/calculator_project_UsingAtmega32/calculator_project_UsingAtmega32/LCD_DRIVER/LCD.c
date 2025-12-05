/*
 * LCD.c
 *
 * Created: 13/06/47 01:36:19 
 *  Author: Belal
 */ 


#include "LCD.h"


void LCD_Init(void){
	_delay_ms(20);
	LCD_CONTROL_DIRECTION |= ((1<<Register_Select) | (1<<Read_Write) | (1<<Enable) ) ;
	LCD_CONTROL_PORTS     &= ~((1<<Register_Select) | (1<<Read_Write) | (1<<Enable)) ;
	LCD_DATA_DIRECTION    = 0xFF ;
	_delay_ms(20);
	Clear_LCD_Screen();
	
    #ifdef EIGHT_BIT_MODE
	Write_Command_onLCD(LCD_FUNCTION_8BIT_2LINES);
	#endif
	
	#ifdef FOUR_BIT_MODE
	Write_Command_onLCD(0x02); 
	Write_Command_onLCD(LCD_FUNCTION_4BIT_2LINES);
	#endif
	
	Write_Command_onLCD(LCD_ENTRY_MODE);
	Write_Command_onLCD(LCD_BEGIN_AT_FIRST_ROW);
	Write_Command_onLCD(LCD_DISP_ON_CURSOR_BLINK);
	}
	
	
void IS_LCD_Busy(void){
	LCD_DATA_DIRECTION     &=~(0xFF<<DATA_shift);
	LCD_CONTROL_PORTS      |= (1<<Read_Write) ;
	LCD_CONTROL_PORTS      &= ~ (1<<Register_Select) ;
	Send_Pulse_toLCD();
    LCD_CONTROL_PORTS      &= ~(1<<Read_Write) ;
    LCD_DATA_DIRECTION |= (0xFF<<DATA_shift);
    
}



void Send_Pulse_toLCD(void){
LCD_CONTROL_PORTS &= ~ (1<<Enable);
_delay_us(200);
LCD_CONTROL_PORTS |= (1<<Enable);
_delay_us(200);
}


void Clear_LCD_Screen(void){
	Write_Command_onLCD(LCD_CLEAR_SCREEN);
}


void Write_Command_onLCD(uint8_t Command){
	IS_LCD_Busy();
	#ifdef EIGHT_BIT_MODE
		LCD_DATA_PORTS = Command ;
		LCD_CONTROL_PORTS &=~((1<<Register_Select) | (1<<Read_Write));
		_delay_ms(1);
		Send_Pulse_toLCD();
    #endif

	
	#ifdef FOUR_BIT_MODE
LCD_DATA_PORTS = (LCD_DATA_PORTS & 0x0F) | (Command & 0xF0);


		LCD_CONTROL_PORTS     &= ~((1<<Register_Select) | (1<<Read_Write)) ;
		Send_Pulse_toLCD();
LCD_DATA_PORTS = (LCD_DATA_PORTS & 0x0F) | ((Command << 4) );
		LCD_CONTROL_PORTS     &= ~((1<<Register_Select) | (1<<Read_Write)) ;
		Send_Pulse_toLCD();
	 #endif

}


void Write_Character_onLCD(uint8_t Character){
	IS_LCD_Busy();
		#ifdef EIGHT_BIT_MODE
         LCD_CONTROL_PORTS |= (1<<Register_Select);
         LCD_CONTROL_PORTS &= ~(1<<Read_Write);
         LCD_DATA_PORTS = Character;
         _delay_us(100);
         Send_Pulse_toLCD();
		#endif
		
		#ifdef FOUR_BIT_MODE
		LCD_DATA_PORTS = (LCD_DATA_PORTS & 0x0F) | (Character & 0xF0);
	    LCD_CONTROL_PORTS |= (1<<Register_Select);
	    LCD_CONTROL_PORTS &= ~(1<<Read_Write);
		Send_Pulse_toLCD();
		LCD_DATA_PORTS = (LCD_DATA_PORTS & 0x0F) | ((Character << 4) );

		LCD_CONTROL_PORTS |= (1<<Register_Select);
		LCD_CONTROL_PORTS &= ~(1<<Read_Write);
		Send_Pulse_toLCD();	
        #endif
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
		if (LINE == 1)
		{
			if (CURSOR < 16 && CURSOR >= 0)
			{
				Write_Command_onLCD(LCD_BEGIN_AT_FIRST_ROW+CURSOR);
			}
		}
		if (LINE == 2)
		{
			if (CURSOR < 16 && CURSOR >= 0)
			{
				Write_Command_onLCD(LCD_BEGIN_AT_SECOND_ROW+CURSOR);
			}
		}
}

void Display_Number_onLCD(uint32_t NUMBER){
		uint8_t str[6];
		sprintf(str,"%d",NUMBER); 
        Write_String_onLCD(str);
}

void Display_RealNumber_onnLCD(float NUMBER)
{
	char buffer[16];
	int INTEGER_PART = (int)NUMBER;
	int FRACTION_PART = (NUMBER - INTEGER_PART) * 1000;

	if(FRACTION_PART < 0)
	FRACTION_PART = -FRACTION_PART;

	sprintf(buffer, "%d.%03d", INTEGER_PART, FRACTION_PART );
	Write_String_onLCD(buffer);
}
