/*
 * KeyPad.c
 *
 *  Created on: Jan 22, 2026
 *  Developer : Eng - Ahmad Ali Assad
 *  Tester : Eng - Belal Hani Sabha
 *  KeyPad Type : 4*4
 */
#include "KeyPad.h"

const uint8_t Cols_KeyPad[4] = { C0, C1, C2, C3 };
const uint8_t Rows_KeyPad[4] = { R0, R1, R2, R3 };
const uint8_t KeypadKeys[4][4] ={ { '7', '8', '9', '/' } , { '4', '5', '6', '*' } , { '1', '2', '3', '-' } , { 'C', '0', '#', '+' } } ;

void HAL_Keypad_Init()
{
    IO_Configure_Pin_t pin;

    pin.IO_Mode = input_with_pull_up;
    pin.IO_Pin_Number = R0;
    MCAL_IO_Init(KeyPad_Port , &pin);
	
	pin.IO_Pin_Number = R1;
	MCAL_IO_Init(KeyPad_Port , &pin);
	 
	pin.IO_Pin_Number = R2;
	MCAL_IO_Init(KeyPad_Port , &pin);
	
	pin.IO_Pin_Number = R3;
	MCAL_IO_Init(KeyPad_Port , &pin);


    pin.IO_Mode = output_Hight;
    pin.IO_Pin_Number = C0;
    MCAL_IO_Init(KeyPad_Port, &pin);
    MCAL_IO_WritePin(KeyPad_Port , C0 , SET_PIN);
	
	pin.IO_Pin_Number = C1;
	MCAL_IO_Init(KeyPad_Port , &pin);
	MCAL_IO_WritePin(KeyPad_Port , C1 , SET_PIN);
	
	pin.IO_Pin_Number = C2;
	MCAL_IO_Init(KeyPad_Port , &pin);
	MCAL_IO_WritePin(KeyPad_Port , C2 , SET_PIN);
	
	pin.IO_Pin_Number = C3;
	MCAL_IO_Init(KeyPad_Port , &pin);
	MCAL_IO_WritePin(KeyPad_Port , C3 , SET_PIN);
}
		
uint8_t HAL_GetData_FromKeyPad()
{
    uint8_t row, col;

    for (col = 0 ; col < 4 ; col++)
    {
		// all cloumns high
        MCAL_IO_WritePin(KeyPad_Port, C0, SET_PIN);
		MCAL_IO_WritePin(KeyPad_Port, C1, SET_PIN);
		MCAL_IO_WritePin(KeyPad_Port, C2, SET_PIN);
		MCAL_IO_WritePin(KeyPad_Port, C3, SET_PIN);

        // specify column to low 
        MCAL_IO_WritePin(KeyPad_Port, Cols_KeyPad[col], RESET_PIN);

        // scanning
        for (row = 0; row < 4; row++)
        {
// 			// duplicated if condition to ensure key is pressed 
//             if (MCAL_IO_ReadPin(KeyPad_Port, Rows_KeyPad[row]) == RESET_PIN)
//             {
//                 // simple delay for debouncing in real simulation not software simulation
//                 for (volatile uint32_t d = 0; d < 5000; d++);

                if (MCAL_IO_ReadPin(KeyPad_Port, Rows_KeyPad[row]) == RESET_PIN)
                {
                    // return the pressed key when user left the keypad  
                    while (MCAL_IO_ReadPin(KeyPad_Port, Rows_KeyPad[row]) == RESET_PIN);
                    return KeypadKeys[row][col];
                }
            }
        }
    }
	
	




