
/*
 * main.c
 *
 * Created: 13/06/47 01:36:40 
 *  Author: Belal
 */ 



#include "LCD.h"
#include "keyPad.h"

int main(void)
{
	uint8_t key , status = 0 , operator = 0;
	float num1 = 0, num2 = 0, result = 0;

	LCD_Init();
	Keypad_Init();

	Write_String_onLCD("Welcome to Belal Calculator");
	_delay_ms(2000);
	Clear_LCD_Screen();

	while(1)
	{
		key = GetData_FromKeyPad();

		if(key == 'N') continue; // do nothing

		else if(key == '?')   // clear lcd 
		{
			Clear_LCD_Screen();
			num1 = num2 = result = 0;
			operator = 0;
			status = 0;
		}

		else if(key >= '0' && key <= '9')  
		{
			Write_Character_onLCD(key);
			if(status == 0) num1 = num1*10 + (key - '0');
			else num2 = num2*10 + (key - '0');
		}

		else if(key == '+' || key == '-' || key == '*' || key == '/')  
		{
			Write_Character_onLCD(key);
			operator = key;
			status = 1; 
		}

		else if(key == '=')
		{
			Control_LCD_Lines_And_Cursor(2,0);
			Write_String_onLCD("Result = ");
			switch(operator)
			{
				case '+': result = num1 + num2; break;
				case '-': result = num1 - num2; break;
				case '*': result = num1 * num2; break;
				case '/':
				if(num2 != 0) result = num1 / num2;
				else {
					 Clear_LCD_Screen();
					 _delay_ms(20);
					 Write_String_onLCD("ERROR :");
					 Control_LCD_Lines_And_Cursor(2,0);
					 Write_String_onLCD("Divide By 0");
					  continue;
					   }
				break;
			}
			 Display_RealNumber_onnLCD(result);


		}
	}
}


