/*
 * USART.c
 *
 * Created: 18/12/2025 10:32:10 
 *  Author: Belal
 */ 

#include "USART.h"


volatile uint8_t flag_send = 1;
volatile uint8_t *TX_str;


USART_Config_t    *G_USART_Config ;

void MCAL_USART_Init(USART_t *USARTx , USART_Config_t *USART_Config){

	G_USART_Config = USART_Config;

	//================== Mode Select & BaudRate ==================
	USARTx->UCSRC = (1<<7) | USART_Config->Mode_Select;

	if (USART_Config->Mode_Select == USART_Mode_Asynchronous)
	{
		USARTx->UCSRA = USART_Config->Speed;

		if (USART_Config->Speed == USART_Speed_Normal)
		{
			USARTx->UBRRL = USART_UBRR_Register(F_OSC ,USART_Config->BaudRate ,16);
		}
		else
		{
			USARTx->UBRRL = USART_UBRR_Register(F_OSC ,USART_Config->BaudRate ,8);
		}
	}
	else
	{
		USARTx->UBRRL = USART_UBRR_Register(F_OSC ,USART_Config->BaudRate ,2);
	}

	//================== Frame Format ==================
	USARTx->UCSRC = (1<<7)
	| USART_Config->Mode_Select
	| USART_Config->Parity
	| USART_Config->StopBitNo;

	// Data Size
	if(USART_Config->DataSize == USART_DataSize_5bit)
	{
		// default
	}
	else if(USART_Config->DataSize == USART_DataSize_6bit)
	{
		USARTx->UCSRC |= USART_DataSize_6bit;
	}
	else if(USART_Config->DataSize == USART_DataSize_7bit)
	{
		USARTx->UCSRC |= USART_DataSize_7bit;
	}
	else if(USART_Config->DataSize == USART_DataSize_8bit)
	{
		USARTx->UCSRC |= USART_DataSize_8bit;
	}
	else if(USART_Config->DataSize == USART_DataSize_9bit)
	{
		USARTx->UCSRC |= USART_DataSize_8bit;
		USARTx->UCSRB |= USART_DataSize_9bit;
	}

	//================== TX / RX Enable ==================
	if (USART_Config->USART_Mode == USART_Mode_RX_Enable)
	{
		USARTx->UCSRB |= USART_Mode_RX_Enable;
	}
	else if(USART_Config->USART_Mode == USART_Mode_TX_Enable)
	{
		USARTx->UCSRB |= USART_Mode_TX_Enable;
	}
	else
	{
		USARTx->UCSRB |= USART_Mode_TX_RX_Enable;
	}

	//================== IRQ Enable ==================
	if (USART_Config->IRQ_Enable == USART_IRQ_Disable)
	{
		// nothing
	}
	else if(USART_Config->IRQ_Enable == USART_IRQ_Enable_RXC)
	{
		USARTx->UCSRB |= USART_IRQ_Enable_RXC;
	}
	else if(USART_Config->IRQ_Enable == USART_IRQ_Enable_TXC)
	{
		USARTx->UCSRB |= USART_IRQ_Enable_TXC;
	}
	else if (USART_Config->IRQ_Enable == USART_IRQ_Enable_TXC_RXC)
	{
		USARTx->UCSRB |= USART_IRQ_Enable_TXC_RXC;
	}
	else
	{
		USARTx->UCSRB |= USART_IRQ_Enable_UDRE;
	}
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

void MCAL_USART_Recieve_String(uint8_t *str)
{
	uint8_t i = 0;
	uint8_t ch;

	while (1)
	{
		ch = MCAL_USART_Recieve_Char();

		if (ch == '\r')
		{
			*str = '\0';    
			break;
		}

		*str = ch;
		Write_Character_onLCD(ch);

		if (i == 15)
		{
			Control_LCD_Lines_And_Cursor(2, 0);
		}
		else if (i == 31)
		{
			Clear_LCD_Screen();
			i = 0;
		}

		str++;
		i++;
	}
}



uint8_t MCAL_UART_Receive_Periodic(uint8_t *pdata)
{
	if (USART->UCSRA & (1 << 7))   // RXC
	{
		*pdata = USART->UDR;
		return 1;
	}
	return 0;
}


void MCAL_UART_SendNoBlock(uint8_t data)
{
	if (USART->UCSRA & (1 << 5))   // UDRE
	{
		USART->UDR = data;
	}
}



uint8_t MCAL_UART_ReceiveNoBlock(void)
{
	return USART->UDR;
}


void MCAL_UART_SendString_Asynch(uint8_t *str)
{
	if (flag_send == 1)
	{
		TX_str = str;
		flag_send = 0;

		USART->UCSRB |= (1 << 6);   // TXCIE
		USART->UDR = TX_str[0];
	}
}

/*
ISR(USART_TXC_vect)
{
	static uint8_t i = 1;

	if (TX_str[i] != '\0')
	{
		USART->UDR = TX_str[i];
		i++;
	}
	else
	{
		i = 1;
		flag_send = 1;
		USART->UCSRB &= ~(1 << 6);   // Disable TXCIE
	}
}
*/