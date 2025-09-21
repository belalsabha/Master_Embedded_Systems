#include "uart.h"
	// define a string to send address to  *Ptr_tx_String
 unsigned char string_[100]= "Eng-Belal_Hani_Abu_Sabha" ;

	void  main(void)
	{
		//calling function
		Uart_Send_String(string_);
	}	



