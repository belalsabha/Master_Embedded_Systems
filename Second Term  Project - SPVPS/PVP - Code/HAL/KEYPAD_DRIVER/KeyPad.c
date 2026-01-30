/*
 * KeyPad.c
 *
 *  Created on: Jan 22, 2026
 *  Developer & Tester : Eng - Belal Hani Sabha
 *  KeyPad Type : 4*3
 */


//----------------------------------
//Includes
//----------------------------------
#include "KeyPad.h"

//----------------------------------
//Global Variables
//----------------------------------
// Cols_KeyPads & Rows_KeyPads arrays
uint16_t Cols_KeyPad[3] = {C0, C1, C2};
uint16_t Rows_KeyPad[4] = {R0, R1, R2, R3};
uint8_t KeypadKeys[4][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};

//----------------------------------
//APIs IMPLEMENTATION
//----------------------------------

// Init keypad pins
void HAL_Keypad_Init()
{
	GPIO_Configure_Pin_t pin;

	// Initialize Rows as Input Pull-Down
	pin.GPIO_Mode = GPIO_Input_pull_down;

	pin.GPOI_Pin_Number = R0;
	MCAL_GPIO_Init(KeyPad_Port, &pin);

	pin.GPOI_Pin_Number = R1;
	MCAL_GPIO_Init(KeyPad_Port, &pin);

	pin.GPOI_Pin_Number = R2;
	MCAL_GPIO_Init(KeyPad_Port, &pin);

	pin.GPOI_Pin_Number = R3;
	MCAL_GPIO_Init(KeyPad_Port, &pin);


	// Init Columns as Output Push Pull with 10MHz Frequency
	pin.GPIO_Mode = output_push_pull;
	pin.GPIO_Output_Frequency = Frequency_10MHz;

	pin.GPOI_Pin_Number = C0;
	MCAL_GPIO_Init(KeyPad_Port, &pin);

	pin.GPOI_Pin_Number = C1;
	MCAL_GPIO_Init(KeyPad_Port, &pin);

	pin.GPOI_Pin_Number = C2;
	MCAL_GPIO_Init(KeyPad_Port, &pin);

	// Reset Pin C0, C1, C2
	MCAL_GPIO_WritePin(KeyPad_Port, C0, RESET_PIN);
	MCAL_GPIO_WritePin(KeyPad_Port, C1, RESET_PIN);
	MCAL_GPIO_WritePin(KeyPad_Port, C2, RESET_PIN);
}

//  Get Key Pressed on KeyPad
uint8_t HAL_GetData_FromKeyPad(void)
{
	for(uint8_t col = 0; col < 3; col++)
	{
		// 1- Activate current column
		MCAL_GPIO_WritePin(KeyPad_Port, Cols_KeyPad[col], SET_PIN);

		// 2- Scan rows
		for(uint8_t row = 0; row < 4; row++)
		{
			if(MCAL_GPIO_ReadPin(KeyPad_Port, Rows_KeyPad[row]) == SET_PIN)
			{
				// 3- Sinple Delay for Debouncing
				for(uint32_t d = 0; d < 1000; d++);

				if(MCAL_GPIO_ReadPin(KeyPad_Port, Rows_KeyPad[row]) == SET_PIN)
				{
					// 4- Reset column
					MCAL_GPIO_WritePin(KeyPad_Port, Cols_KeyPad[col], RESET_PIN);

					// 5- Wait for release
					while(MCAL_GPIO_ReadPin(KeyPad_Port, Rows_KeyPad[row]) == SET_PIN);

					return KeypadKeys[row][col];
				}
			}
		}

		// 6- Reset column before next scan
		MCAL_GPIO_WritePin(KeyPad_Port, Cols_KeyPad[col], RESET_PIN);
	}

	return 'N';   // No key pressed
}

