/*
 * IO.c
 * Created on: Dec 14, 2025
 * Author: Belal Hani Sabha
 */

#include "IO.h"

void MCAL_IO_Init(IOx_t *IOx, IO_Configure_Pin_t* PinNumber_Configuration){
	if(PinNumber_Configuration->IO_Mode == input_without_pull_up){
		IOx->DDR  &= ~ (PinNumber_Configuration->IO_Pin_Number);
		IOx->PORT &= ~ (PinNumber_Configuration->IO_Pin_Number);
	}
	else if(PinNumber_Configuration->IO_Mode == input_with_pull_up){
		IOx->DDR  &= ~ (PinNumber_Configuration->IO_Pin_Number);
		IOx->PORT |=  (PinNumber_Configuration->IO_Pin_Number);
	}
	else {
		IOx->DDR  |=  (PinNumber_Configuration->IO_Pin_Number);
		if(PinNumber_Configuration->IO_Mode == output_Hight){
			IOx->PORT |=  (PinNumber_Configuration->IO_Pin_Number);
			} else {
			IOx->PORT &= ~ (PinNumber_Configuration->IO_Pin_Number);
		}
	}
}

void MCAL_IO_DeInit(IOx_t *IOx){
	IOx->DDR  = 0x00;
	IOx->PORT = 0x00;
	SFIOR = 0x00;
}

uint8_t MCAL_IO_ReadPin(IOx_t *IOx, uint8_t PinNumber){
	return ((IOx->PIN & PinNumber) != 0) ? SET_PIN : RESET_PIN;
}

uint8_t MCAL_IO_ReadPort(IOx_t *IOx){
	return IOx->PIN;
}

void MCAL_GPIO_WritePin(IOx_t *IOx, uint8_t PinNumber, uint8_t Value){
	if(Value == SET_PIN){
		IOx->PORT |= PinNumber;
		} else {
		IOx->PORT &= ~PinNumber;
	}
}
