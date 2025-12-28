/*
 * App.c
 *
 *
 *  Created on: Dec 25, 2025
 *      Author:  Belal Hani Sabha
 */


//----------------------------------
//Includes
//----------------------------------
#include "App.h"

//----------------------------------
//Global Variables
//----------------------------------
	uint16_t Data;



//----------------------------------
//Local Function
//----------------------------------
	void UART_IRQ_Callback (void)
	{

		MCAL_USART_ReceiveData(USART1, &Data, PollingMechanism_Dis);
		MCAL_USART_SendData(USART1, &Data, 	PollingMechanism_EN);

	}


//----------------------------------
//APIs IMPLEMENTATION
//----------------------------------

	/**================================================================
	 * @Fn              - APP_Init
	 * @brief           - Initializes application peripherals and USART configuration
	 * @param [in]      - none
	 * @retval          - none
	 * Note             - Enables AFIO and GPIOA clocks.
	 *                  - Configures USART1 with:
	 *                    * Baud rate 115200
	 *                    * 8-bit data size
	 *                    * No parity
	 *                    * 1 stop bit
	 *                    * TX/RX enabled
	 *                    * RX interrupt enabled
	 *                  - Sets USART GPIO pins.
	 *                  - Callback function is APP_Start.
	 *                  - Clock assumed 8 MHz.
	 */
void APP_Init(void){
    RCC_AFIO_CLK_EN();
    RCC_GPIOA_CLK_EN();


    USART_Config_t uartConfig;
    uartConfig.BaudRate      = USART_BaudRate_115200;
    uartConfig.DataSize      = USART_DataSize_8bit;
    uartConfig.FlowCtrl      = USART_CTS_RTS_Disable;
    uartConfig.IRQ_Enable    = USART_IRQ_Enable_RXNEIE  ;
    uartConfig.Parity        = USART_Parity_Disable;
    uartConfig.Ptr_ISR_Func  = APP_Start;
    uartConfig.StopBitNo     = USART_StopBitNo_1;
    uartConfig.USART_Mode    = USART_Mode_TX_RX_Enable;

    MCAL_USART_GPIO_Set_Pins(USART1);

    MCAL_USART_Init(USART1, &uartConfig);
}


/**================================================================
 * @Fn              - APP_Start
 * @brief           - USART interrupt callback function
 * @param [in]      - none
 * @retval          - none
 * Note             - Called automatically when USART RX interrupt occurs.
 *                  - Handles received data through UART_IRQ_Callback().
 *                  - Polling mechanism example is provided but commented.
 */
void APP_Start(void){


	UART_IRQ_Callback ();

			// by using Polling Mechanism
	    	// MCAL_USART_ReceiveData(USART1, &Data, PollingMechanism_EN);
	    	// MCAL_USART_SendData(USART1, &Data, PollingMechanism_EN);
	    	// MCAL_USART_WAIT_TC(USART1);
}
