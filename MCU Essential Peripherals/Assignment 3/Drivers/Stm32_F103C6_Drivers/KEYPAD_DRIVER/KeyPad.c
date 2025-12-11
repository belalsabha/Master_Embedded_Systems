/*
 * keyPad.c
 *
 * Created: 13/06/47 01:36:40
 *  Author: Belal
 */


#include <KeyPad.h>

uint32_t Rows_KeyPad[] = {R0, R1, R2, R3}; //rows of the keypad
uint32_t Cols_KeyPad[] = {C0, C1, C2, C3};//columns

void Keypad_Init(){
	Pin_Config->GPOI_Pin_Number= R0 ;
	Pin_Config->GPIO_Mode = GPIO_Floating_Input;


	Pin_Config->GPOI_Pin_Number= R1 ;
	Pin_Config->GPIO_Mode = GPIO_Floating_Input;


	Pin_Config->GPOI_Pin_Number= R2 ;
	Pin_Config->GPIO_Mode = GPIO_Floating_Input;


	Pin_Config->GPOI_Pin_Number= R3 ;
	Pin_Config->GPIO_Mode = GPIO_Floating_Input;


	Pin_Config->GPOI_Pin_Number= C0 ;
	Pin_Config->GPIO_Mode = output_push_pull;
	Pin_Config->GPIP_Output_Frequency = Frequency_10MHz ;

	Pin_Config->GPOI_Pin_Number= C1 ;
	Pin_Config->GPIO_Mode = output_push_pull;
	Pin_Config->GPIP_Output_Frequency = Frequency_10MHz ;

	Pin_Config->GPOI_Pin_Number= C2 ;
	Pin_Config->GPIO_Mode = output_push_pull;
	Pin_Config->GPIP_Output_Frequency = Frequency_10MHz ;

	Pin_Config->GPOI_Pin_Number= C3 ;
	Pin_Config->GPIO_Mode = output_push_pull;
	Pin_Config->GPIP_Output_Frequency = Frequency_10MHz ;

    MCAL_GPIO_Init(KEYPAD_PORT, &Pin_Config);
	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);
}






uint8_t GetData_FromKeyPad(){
	uint32_t x,y;
	for (x = 0; x < 4; x++){
		MCAL_GPIO_WritePin(KEYPAD_PORT, Cols_KeyPad[0], SET_PIN);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Cols_KeyPad[1], SET_PIN);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Cols_KeyPad[2], SET_PIN);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Cols_KeyPad[3], SET_PIN);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Cols_KeyPad[x], RESET_PIN);

		for(y = 0; y < 4; y++){
			if (MCAL_GPIO_ReadPin(KEYPAD_PORT, Rows_KeyPad[y]) == 0)
			{
				while(MCAL_GPIO_ReadPin(KEYPAD_PORT, Rows_KeyPad[y]) == 0);
				switch(x){
					case (0):
						if (y == 0) return '7';
						else if (y == 1) return '4';
						else if (y == 2) return '1';
						else if (y == 3) return '?';
						break;
					case (1):
						if (y == 0) return '8';
						else if (y == 1) return '5';
						else if (y == 2) return '2';
						else if (y == 3) return '0';
						break;
					case (2):
						if (y == 0) return '9';
						else if (y == 1) return '6';
						else if (y == 2) return '3';
						else if (y == 3) return '=';
						break;
					case (3):
						if (y == 0) return '/';
						else if (y == 1) return '*';
						else if (y == 2) return '-';
						else if (y == 3) return '+';
						break;
				}
			}
		}
	}
	return 'N';
}
