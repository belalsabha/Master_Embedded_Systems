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

//----------------------------------
//User type definitions (structures)
//----------------------------------

//Configuration structure For User inputs
typedef struct {

	uint8_t       USART_Mode 		   ;		// Specifies the TX/RX Mode.
												// This parameter must be set based on @ref USART_Mode_define
								
	uint8_t		Mode_Select            ;		//selects between Asynchronous and Synchronous mode of operation
												//This parameter must be set based on @ref USART_Mode_Select_define

	uint32_t      BaudRate	 	 	   ;		// This member configures the USART communication baud rate
												// This parameter must be set based on @ref USART_BaudRate_define


	uint8_t	      DataSize     		   ;		// Specifies the number of data bits transmitted or received in a frame.
												// This parameter must be set based on @ref USART_DataSize_define


	uint8_t		  Parity		 	   ;		//Specifies the parity mode.
												//@ref USART_Parity_define

	uint8_t 	  StopBitNo  		   ;		//Specifies the number of stop bits transmitted
												//@ref USART_StopBitNo_define

	uint8_t       Speed   		       ;		//Specifies whether the Speed is Normal or Double
												//@ref USART_Speed _define
	
	uint8_t       IRQ_Enable	 	   ; 		//enable or disable USART IRQ TX/RX
												//@ref USART_IRQ_Enable_define , you can select two or three parameters EX.USART_IRQ_Enable_TXE |USART_IRQ_Enable_TC


	void 		  (*Ptr_ISR_Func)(void);	//Set the C Function() which will be called once the IRQ  Happen


}USART_Config_t;



// * =======================================================================================
/*===================================Reference Macros=======++++++=========================*/
// * =======================================================================================

// @ref USART_Mode_define
#define  USART_Mode_RX_Enable    	(1<<4)        		    //• Bit 4 – RXEN: Receiver Enable
#define  USART_Mode_TX_Enable    	(1<<3)        			//• Bit 3 – TXEN: Transmitter Enable
#define  USART_Mode_TX_RX_Enable    (1<<3) | (1<<4)         //• Bit 3 & 4 : Transmitter enable  & Receiver enable


//@ref USART_Mode_Select_define
 //• Bit 6 – UMSEL: USART Mode Select
#define  USART_Mode_Asynchronous     	(0)        				//• Bit 6  =  0 
#define  USART_Mode_Synchronous     	(1<<6)        			//• Bit 6  =  1


// @ref USART_BaudRate_define
#define USART_BaudRate_2400                   2400
#define USART_BaudRate_9600                   9600
#define USART_BaudRate_19200                  19200
#define USART_BaudRate_57600                  57600
#define USART_BaudRate_115200                 115200
#define USART_BaudRate_230400                 230400
#define USART_BaudRate_460800                 460800
#define USART_BaudRate_921600                 921600
#define USART_BaudRate_2250000                2250000
#define USART_BaudRate_4500000                4500000


// @ref USART_DataSize_define
		//• Bit 2:1 – UCSZ1:0: Character Size
#define USART_DataSize_5bit             (0)
#define USART_DataSize_6bit  			(1<<1)
#define USART_DataSize_7bit             (1<<2)
#define USART_DataSize_8bit  			(1<<1) | (1<<2)
#define USART_DataSize_9bit             (1 << 2)  // in USCRB with USART_DataSize_8bit 




// @ref USART_Parity_define
  //• Bit 5:4 – UPM1:0: Parity Mode
#define USART_Parity_Disable			(0)
#define USART_Odd_Parity				(3 << 4)
#define USART_Even_Parity				(2 << 4)



// @ref USART_StopBitNo_define
		//• Bit 3 – USBS: Stop Bit Select
#define USART_StopBitNo_1				(0)  		//00
#define USART_StopBitNo_2				(1<<3)		//01




//@ref USART_Speed _define
	//• Bit 1 – U2X: Double the USART Transmission Speed
#define USART_Speed_Normal              (0)
#define USART_Speed_Double              (1<<1)	



//@ref USART_IRQ_Enable_define
#define USART_IRQ_Disable                      			(0)
#define USART_IRQ_Enable_RXC                       		(1<<7)  //• Bit 7 – RXC: USART Receive Complete
#define USART_IRQ_Enable_TXC                     		(1<<6) 	//• Bit 6 – TXC: USART Transmit Complete
#define USART_IRQ_Enable_TXC_RXC						(1<<7) | (1<<6)
#define USART_IRQ_Enable_UDRE                       	(1<<5)  //• Bit 5 – UDRE: USART Data Register Empty








/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */

#define F_OSC 8000000    //from TRM	


//BAUD Baud rate (in bits per second, bps)
//fOSC    System Oscillator clock frequency
//UBRR Contents of the UBRRH and UBRRL Registers, (0 - 4095)

//UBRR = fosc/speed_mode*Baudrate    - 1
// in Async if normal mode  speed_mode = 16 , double speed_mode = 8 
//in Sync speed_mode = 2  
#define USART_UBRR_Register( fosc , Baudrate , Speed_Mode)		((( fosc / (Speed_Mode * Baudrate)  ) ) -1 )


/*
 * =======================================================================================
 * 							APIs Supported by "MCAL USART DRIVER"
 * =======================================================================================
 */

// 					APIs For USART

void   MCAL_USART_Init(USART_t *USARTx , USART_Config_t *USART_Config);

void MCAL_USART_Send_Char (uint8_t data);
uint8_t MCAL_USART_Recieve_Char (void);

void MCAL_USART_Send_String(char* str);
void MCAL_USART_Recieve_String(uint8_t* str);

void MCAL_USART_Send_Number(uint32_t num);
uint32_t MCAL_USART_Receive_Number(void);


uint8_t MCAL_UART_Receive_Periodic(uint8_t *pdata);

void MCAL_UART_SendNoBlock(uint8_t data);
uint8_t  MCAL_UART_ReceiveNoBlock(void);

void   MCAL_UART_SendString_Asynch(uint8_t * str);



#endif /* USART_H_ */