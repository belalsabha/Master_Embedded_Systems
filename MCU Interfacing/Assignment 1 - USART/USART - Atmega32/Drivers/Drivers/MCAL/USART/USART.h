/*
 * USART.h
 *
 * Created: 19/12/2025 10:32:23 
 *  Author: Belal
 */ 


#ifndef USART_H_
#define USART_H_

//----------------------------------
//Includes
//----------------------------------
#include "Atmega32.h"
#include "IO.h"


































/*
 * =======================================================================================
 * 							APIs Supported by "MCAL USART DRIVER"
 * =======================================================================================
 */

// 					APIs For USART

void MCAL_USART_Init (void);

void MCAL_USART_Send_Char (uint8_t data);
uint8_t MCAL_USART_Recieve_Char (void);

void MCAL_USART_Send_String(char* str);
void MCAL_USART_Recieve_String(uint8_t* str);

void MCAL_USART_Send_Number(uint32_t num);
uint32_t MCAL_USART_Receive_Number(void);






#endif /* USART_H_ */