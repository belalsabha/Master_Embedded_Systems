#include "uart.h"
 unsigned char string_buffer[100]= "Belal_Hani_Abu_Sabha" ;
  unsigned char const string_buffer2[100]= "Belal_Hani_Abu_Sabha" ;


void main(void){
Uart_send_string(string_buffer);
}