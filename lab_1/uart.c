#include "uart.h"
//uart reg
#define UART0DR *((volatile unsigned int* const)((unsigned int*)0x101f1000))

void Uart_send_string(unsigned char* p_tx_srting){
while (*p_tx_srting != '\0'){
	// loop until end of string
UART0DR=(unsigned int)(*p_tx_srting); //transmit char
p_tx_srting++; // point to next char 
}
}