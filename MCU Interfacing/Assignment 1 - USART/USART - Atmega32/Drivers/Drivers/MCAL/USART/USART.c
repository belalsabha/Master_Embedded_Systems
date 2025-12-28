/*
 * USART.c
 *
 * Created: 18/12/2025 10:32:10 
 *  Author: Belal
 */ 

#include "USART.h"

void MCAL_USART_Init (void){
	
	
	
	
	
	
	// Baud rate
	USART->UBRRL = 51;

	// UCSRC: URSEL=1, Async, No parity, 1 stop, 8-bit
	USART->UCSRC = (1<<7) | (1<<1) | (1<<2);
	// Enable RX, TX
	USART->UCSRB = (1<<4) | (1<<3);

  
  
}
void MCAL_USART_Send_Char (uint8_t data){
	while(!(USART->UCSRA & (1 << 5)));   //Bit 5 – UDRE: USART Data Register Empty
	USART->UDR = data ;
}
uint8_t MCAL_USART_Recieve_Char (void)
{
	while(!(USART->UCSRA & (1 << 7)));  //• Bit 7 – RXC: USART Receive Complete
	return USART->UDR ;
}




void  MCAL_USART_Send_Number(uint32_t number)
{
	uint8_t *ptr = &number;
	MCAL_USART_Send_Char(ptr[0]);
	MCAL_USART_Send_Char(ptr[1]);
	MCAL_USART_Send_Char(ptr[2]);
	MCAL_USART_Send_Char(ptr[3]);
	// with shifting
	//	MCAL_USART_Send_Char((uint8_t)number);
	//	MCAL_USART_Send_Char((uint8_t)(number>>8));
	//	MCAL_USART_Send_Char((uint8_t)(number>>16));
	//	MCAL_USART_Send_Char((uint8_t)(number>>24));
}

uint32_t  MCAL_USART_Receive_Number()
{
	uint32_t number;
	uint8_t *ptr=&number;
	
	ptr[0]= MCAL_USART_Recieve_Char ();
	ptr[1]= MCAL_USART_Recieve_Char ();
	ptr[2]= MCAL_USART_Recieve_Char ();
	ptr[3]= MCAL_USART_Recieve_Char ();
	
	
	// with shifting
	//	uint8_t byte1 =  MCAL_USART_Recieve_Char();
	//	uint8_t byte2 =  MCAL_USART_Recieve_Char();
	//	uint8_t byte3 =  MCAL_USART_Recieve_Char();
	//	uint8_t byte4 =  MCAL_USART_Recieve_Char();
	//	number = byte1|(uint32_t)byte2<<8|(uint32_t)byte2<<16|(uint32_t)byte3<<24;
	return number;
	
	
}

void MCAL_USART_Send_String(char *str)
{
	while (*str)
	{
		MCAL_USART_Send_Char(*str++);
	}
}

void MCAL_USART_Recieve_String(uint8_t *str){
   uint8_t i = 0 ;
	while(1)
	{
		*str = MCAL_USART_Recieve_Char();
		if( *str == '0')
			break;
		else{
			Write_Character_onLCD(*str);
			if( i == 15) {
				Control_LCD_Lines_And_Cursor(2,0);
			}else if (i == 31)
			{
			  Clear_LCD_Screen();
			}
			str++;
			i++;
		}

	}
}