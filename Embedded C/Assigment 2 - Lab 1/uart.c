#include "uart.h"
	// define uart register address
#define UART0DR *((volatile unsigned int* const)((unsigned int*)0x101f1000))

	void Uart_Send_String(unsigned char* Ptr_tx_String){

		// loop until end of string
		while(*Ptr_tx_String != '\0'){

			UART0DR=(unsigned int)(*Ptr_tx_String); //transmit char (1 byte) to UART0DR 	
			Ptr_tx_String++; // for next character
		}
	}






