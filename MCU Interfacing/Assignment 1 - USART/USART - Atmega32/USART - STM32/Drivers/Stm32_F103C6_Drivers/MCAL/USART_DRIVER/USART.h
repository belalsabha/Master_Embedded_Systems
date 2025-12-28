/*
 * USART.h
 *
 *  Created on: Dec 24, 2025
 *      Author:  Belal Hani Sabha
 */

#ifndef USART_DRIVER_USART_H_
#define USART_DRIVER_USART_H_

//----------------------------------
//Includes
//----------------------------------
#include "GPIO.h"
#include "stm32f103x6.h"
#include "GPIO.h"
#include "RCC.h"



//----------------------------------
//User type definitions (structures)
//----------------------------------

//Configuration structure For User inputs
typedef struct {

	uint8_t       USART_Mode 		   ;	// Specifies the TX/RX Mode.
											// This parameter must be set based on @ref USART_Mode_define

	uint32_t      BaudRate	 	 	   ;	// This member configures the USART communication baud rate
											// This parameter must be set based on @ref USART_BaudRate_define


	uint8_t	      DataSize     		   ;	// Specifies the number of data bits transmitted or received in a frame.
											// This parameter must be set based on @ref USART_DataSize_define


	uint8_t		  Parity		 		   ;	//Specifies the parity mode.
											//@ref USART_Parity_define

	uint8_t 	  StopBitNo  		   ;	//Specifies the number of stop bits transmitted
											//@ref USART_StopBitNo_define

	uint8_t       FlowCtrl   		   ;	//Specifies whether the hardware flow control mode is enabled or disabled
											//@ref USART_FlowCtrl _define

	uint8_t       IRQ_Enable	 	   ; 	//enable or disable USART IRQ TX/RX
											//@ref USART_IRQ_Enable_define , you can select two or three parameters EX.USART_IRQ_Enable_TXE |USART_IRQ_Enable_TC


	void 		  (*Ptr_ISR_Func)(void);	//Set the C Function() which will be called once the IRQ  Happen


}USART_Config_t;

// * =======================================================================================
/*===================================Reference Macros=======++++++=========================*/
// * =======================================================================================

// @ref USART_Mode_define
#define  USART_Mode_RX_Enable    	(1<<2)        		    //Bit 2 RE: Receiver enable
#define  USART_Mode_TX_Enable    	(1<<3)        			//Bit 3 TE: Transmitter enable
#define  USART_Mode_TX_RX_Enable    (1<<3) | (1<<2)        //Bit 3 & 2 : Transmitter enable  & Receiver enable


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
		//Bit 12 M: Word length
#define USART_DataSize_8bit             (0)
#define USART_DataSize_9bit  			(1 << 12)



// @ref USART_Parity_define
  //Bit 10 PCE: Parity control enable
#define USART_Parity_Disable			(0)
#define USART_Parity_Enable				(1 << 10)
  //Bit 9 PS: Parity selection
#define USART_Odd_Parity				(1 << 9)
#define USART_Even_Parity				(0)



// @ref USART_StopBitNo_define
		//Bits 13:12 STOP: STOP bits
#define USART_StopBitNo_1				(0)  		//00
#define USART_StopBitNo_half				(1<<12)		//01
#define USART_StopBitNo_2				(1<<13)		//01
#define USART_StopBitNo_1andHalf				((1<<13) | (1<<12))		//11





// @ref USART_FlowCtrl _define
#define USART_CTS_RTS_Disable				(0)
		//Bit 8 RTSE: RTS enable
#define USART_RTS_Enable					(1<<8)
        //Bit 9 CTSE: CTS enable
#define USART_CTS_Enable					(1<<9)
#define USART_CTS_RTS_Enable				((1<<8)  | (1<<9))







//@ref USART_IRQ_Enable_define
#define USART_IRQ_Disable                      			(0)
#define USART_IRQ_Enable_TXE                       		(1<<7)  //Transmit data register empty
#define USART_IRQ_Enable_TC                     		(1<<6) 	//Transmission complete
#define USART_IRQ_Enable_RXNEIE                       	(1<<5)  //Received data ready to be read & Overrun error detected
#define USART_IRQ_Enable_PE                       	    (1<<8)  //Parity error








/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */

// Enable | Disable PollingMechanism
#define PollingMechanism_EN         1
#define PollingMechanism_Dis        0






//Macros
//Bits 15:4 DIV_Mantissa[11:0]: mantissa of USARTDIV
	//These 12 bits define the mantissa of the USART Divider (USARTDIV)
	//Bits 3:0 DIV_Fraction[3:0]: fraction of USARTDIV
	//These 4 bits define the fraction of the USART Divider (USARTDIV)

// Calculate BaudRate >> USARTDIV = DIV_Mantissa + (DIV_Fraction / 16)
// Example if P_Clk_ = 36M and Baudrate = 115200      >>>>>

//Steps :
//		   1- USARTDIV 					= 36*10^6 / (16*115200) = 19.53125 = 19
//		   2- USARTDIV_MUL100 			= 100*36*10^6 / (16*115200) =  1953.125 = 1953
//		   3- DIV_Mantissa_MUL100  		= 19*100 =  Integer Part (USARTDIV  )  * 100= 1900
//		   4- DIV_Mantissa        		= 19.53125 = 19
//		   5- DIV_Fraction		  		= 1953.125 - 1900   = 53.125 * 16 /100 = (uint32_t) 8.5 = 8
//		   6- USART_BRR_Register : write 19 from bit no 4 to 15  , and 8 from bit no 0 to 3
#define USARTDIV( P_Clk_ , Baudrate ) 				(P_Clk_ / (16 * Baudrate ))

#define USARTDIV_MUL100( P_Clk_ , Baudrate )		(	(100 * P_Clk_ )	/ (16 * Baudrate ))

#define DIV_Mantissa_MUL100( P_Clk_ , Baudrate )	(USARTDIV( P_Clk_ , Baudrate )  * 100 )

#define DIV_Mantissa( P_Clk_ , Baudrate )  			( USARTDIV( P_Clk_ , Baudrate ))

#define DIV_Fraction( P_Clk_ , Baudrate )  			(( - DIV_Mantissa_MUL100( P_Clk_ , Baudrate ) + USARTDIV_MUL100	( P_Clk_ , Baudrate ) )	*16 /100 )

#define USART_BRR_Register( P_Clk_ , Baudrate )		(( DIV_Mantissa ( P_Clk_ , Baudrate ) <<4 )|( (DIV_Fraction( P_Clk_ , Baudrate )) & 0xF ))









/*
 * =======================================================================================
 * 							APIs Supported by "MCAL GPIO DRIVER"
 * =======================================================================================
 */
void MCAL_USART_Init 		(USART_t *USARTx, USART_Config_t* USART_Config);
void MCAL_USART_DeInit 		(USART_t *USARTx);


void MCAL_USART_GPIO_Set_Pins(USART_t *USARTx);


void MCAL_USART_SendData		(USART_t *USARTx, uint16_t *pTxData ,uint8_t PollingEn );
void MCAL_USART_ReceiveData	(USART_t *USARTx, uint16_t *pTxData ,uint8_t PollingEn );

void MCAL_USART_WAIT_TC 		(USART_t *USARTx ) ;

//MCAL_USART_LIN_Init ()  					//LIN
//MCAL_USART_Init 	  ()  				    //Synchronous
//MCAL_USART_DMA_Init () 					/ MultiBuffer Communication


#endif /* USART_DRIVER_USART_H_ */
