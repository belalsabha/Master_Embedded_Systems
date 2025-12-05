/*
 * keyPad.c
 *
 * Created: 13/06/47 01:36:40 
 *  Author: Belal
 */ 


#include "keypad.h"

uint32_t Rows_KeyPad[] = {R0, R1, R2, R3}; //rows of the keypad
uint32_t Cols_KeyPad[] = {C0, C1, C2, C3};//columns

void Keypad_Init(){
	KEYPAD_DATA_DIRECTION &= ~((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));
	KEYPAD_DATA_DIRECTION |= ((1 << C0) | (1 << C1) | (1 << C2) | (1 << C3));
	KEYPAD_DATA_PORT = 0xFF;
}

uint8_t GetData_FromKeyPad(){
	int x,y;
	for (x = 0; x < 4; x++){
		KEYPAD_DATA_PORT |= ((1<<Cols_KeyPad[0]) | (1<<Cols_KeyPad[1]) | (1<<Cols_KeyPad[2]) | (1<<Cols_KeyPad[3]));
		KEYPAD_DATA_PORT &= ~(1<<Cols_KeyPad[x]);
		for(y = 0; y < 4; y++){
			if (!(KeyPad_PIN & (1 << Rows_KeyPad[y])))
			{
				while(!(KeyPad_PIN & (1 << Rows_KeyPad[y])));
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