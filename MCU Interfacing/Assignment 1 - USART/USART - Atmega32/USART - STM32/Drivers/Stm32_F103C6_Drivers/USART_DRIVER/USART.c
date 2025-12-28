/*
 * USART.c
 *
 *
 *  Created on: Dec 24, 2025
 *      Author:  Belal Hani Sabha
 */


#include "USART.h"


/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
USART_Config_t* G_USART_Config  = NULL ;


/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */
/**================================================================
 * @Fn				-MCAL_USARTT_Init
 * @brief 			- Initializes USARTT (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- USART_Config: All USARTT Configuration EXTI_PinConfig_t
 * @retval 			-none
 * Note				-Support for Now Asynch mode & Clock 8 MHZ
 */
void MCAL_USART_Init (USART_t *USARTx, USART_Config_t* USART_Config){

	uint32_t P_Clk , BRR ;

	G_USART_Config = USART_Config ;

	//1-	Enable  Clock for input USART
	if(USARTx == USART1){
			RCC_USART1_CLK_EN(); 		//USART1 set


	}else if(USARTx == USART2){
			RCC_USART2_CLK_EN();			// USART2 set



	}else if(USARTx == USART3){

			RCC_USART3_CLK_EN();			// USART3 set
	}



	//2-Enable the USART by writing the UE bit in USART_CR1 register to 1.
	 //Bit 13 UE: USART enable
	USARTx->CR1 |= (1 << 13) ;

	//3-Enable USART Tx and Rx engines according to the USART_Mode configuration item
		// Bit 2 RE: Receiver enable , Bit 3 TE: Transmitter enable
	USARTx->CR1 |= USART_Config->USART_Mode ;

	//4- Select DataSize
	  // Bit 12 M: Word length
	USARTx->CR1 |= USART_Config->DataSize;

	//5-Enable or Disable Parity Bit and Select even or odd if Its Enabled
	   // Bit 10 PCE: Parity control enable , Bit 9 PS: Parity selection
	USARTx->CR1 |= USART_Config->Parity;

	//6- Select Number of Stop Bits
	  //Bits 13:12 STOP: STOP bits
	USARTx->CR2 |= USART_Config->StopBitNo;

	//7- Enable or Disable FlowControl Control
	  //Bit 9 CTSE: CTS enable , Bit 8 RTSE: RTS enable
	USARTx->CR3 |= USART_Config->FlowCtrl;

	//8- Configuration of BRR(Baudrate register)
	//PCLK1 for USART 2, 3
	//PCLK2 for USART1
	if(USARTx == USART1){
		P_Clk = MCAL_RCC_Get_PCLK2Freqency();
	}else{
		P_Clk = MCAL_RCC_Get_PCLK1Freqency();
	}

	BRR = (uint32_t) USART_BRR_Register( P_Clk, USART_Config->BaudRate) ;
	USARTx->BRR = BRR ;

	//ENABLE | DISABLE Interrupt
	//USART_CR1
	if (USART_Config->IRQ_Enable  != USART_IRQ_Disable )
	{
		USARTx->CR1 |= (USART_Config->IRQ_Enable) ;
		//Enable NVIC For USARTx IRQ
		if ( USARTx == USART1 )
			NVIC_IRQ37_USART1_Enable ;

		else if ( USARTx == USART2 )
			NVIC_IRQ38_USART2_Enable ;

		else if ( USARTx == USART3 )
			NVIC_IRQ39_USART3_Enable ;
	}
}





/**================================================================
 * @Fn				-MCAL_USART_DEInit
 * @brief 			- DEInitializes USART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Reset the Model By RCC
 */
void MCAL_USART_DeInit 		(USART_t *USARTx){

	//reset USARTx Peripheral and Disable IRQ

	if ( USARTx == USART1 )
	{
		RCC_USART1_CLK_Reset();
		NVIC_IRQ37_USART1_Disable ;

	}

	else if ( USARTx == USART2 )
	{
		RCC_USART2_CLK_Reset();
		NVIC_IRQ38_USART2_Disable ;


	}

	else if ( USARTx == USART3 )
	{
		RCC_USART3_CLK_Reset();
		NVIC_IRQ39_USART3_Disable ;

	}



}

/**================================================================
 * @Fn				-MCAL_USART_GPIO_Set_Pins
 * @brief 			- intialize GPIO Pins
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Should enable the corresponding ALT  & GPIO  in RCC clock Also called after MCAL_USART_Init()
 */
void MCAL_USART_GPIO_Set_Pins(USART_t *USARTx)
{
    GPIO_Configure_Pin_t PIN_CFG;
    uint8_t FlowControl = G_USART_Config->FlowCtrl;


    // Configure USART Pins based on Recommended  configurations for device peripherals in TRM
    // USARTx_TX(1)
    //Full duplex 	>>Alternate                  >>  function push-pull
    // Half duplex  >>synchronous                >> mode Alternate function push-pull

    //USARTx_RX
    //Full duplex  >>Input floating              >> Input pull-up
    //Half duplex  >>synchronous mode Not used.  >>Can be used as a general IO

    //USARTx_CK    >>Synchronous mode            >> Alternate function push-pull
    //USARTx_RTS   >> Hardware flow control      >> Alternate function push-pull
    //USARTx_CTS   >> Hardware flow control      >> Input floating/ Input pull-up

    // ================= USART1 =================
    if (USARTx == USART1)
    {
        //TX PA9
        PIN_CFG.GPOI_Pin_Number = GPIO_PIN9;
        PIN_CFG.GPIO_Mode = Alternate_function_output_Push_pull;
        PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz;
        MCAL_GPIO_Init(GPIOA, &PIN_CFG);

        // RX PA10
        PIN_CFG.GPOI_Pin_Number = GPIO_PIN10;
        PIN_CFG.GPIO_Mode =  GPIO_Floating_Input ;
        MCAL_GPIO_Init(GPIOA, &PIN_CFG);

        // CTS PA11
        if (FlowControl & USART_CTS_Enable)
        {
            PIN_CFG.GPOI_Pin_Number = GPIO_PIN11;
            PIN_CFG.GPIO_Mode = GPIO_Floating_Input ;
            MCAL_GPIO_Init(GPIOA, &PIN_CFG);
        }

        //RTS PA12
        if (FlowControl & USART_RTS_Enable)
        {
            PIN_CFG.GPOI_Pin_Number = GPIO_PIN12;
            PIN_CFG.GPIO_Mode = Alternate_function_output_Push_pull;
            PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz;
            MCAL_GPIO_Init(GPIOA, &PIN_CFG);
        }
    }

    // ================= USART2 =================
    else if (USARTx == USART2)
    {
        // TX PA2
        PIN_CFG.GPOI_Pin_Number = GPIO_PIN2;
        PIN_CFG.GPIO_Mode = Alternate_function_output_Push_pull;
        PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz;
        MCAL_GPIO_Init(GPIOA, &PIN_CFG);

        // RX PA3
        PIN_CFG.GPOI_Pin_Number = GPIO_PIN3;
        PIN_CFG.GPIO_Mode = GPIO_Floating_Input ;
        MCAL_GPIO_Init(GPIOA, &PIN_CFG);

        // CTS PA0
        if (FlowControl & USART_CTS_Enable)
        {
            PIN_CFG.GPOI_Pin_Number = GPIO_PIN0;
            PIN_CFG.GPIO_Mode = GPIO_Floating_Input ;
            MCAL_GPIO_Init(GPIOA, &PIN_CFG);
        }

        // RTS PA1
        if (FlowControl & USART_RTS_Enable)
        {
            PIN_CFG.GPOI_Pin_Number = GPIO_PIN1;
            PIN_CFG.GPIO_Mode = Alternate_function_output_Push_pull;
            PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz;
            MCAL_GPIO_Init(GPIOA, &PIN_CFG);
        }
    }

    // ================= USART3 =================
    else if (USARTx == USART3)
    {
        // TX PB10
        PIN_CFG.GPOI_Pin_Number = GPIO_PIN10;
        PIN_CFG.GPIO_Mode = Alternate_function_output_Push_pull;
        PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz;
        MCAL_GPIO_Init(GPIOB, &PIN_CFG);

        // RX PB11
        PIN_CFG.GPOI_Pin_Number = GPIO_PIN11;
        PIN_CFG.GPIO_Mode = GPIO_Floating_Input ;
        MCAL_GPIO_Init(GPIOB, &PIN_CFG);

        // CTS PB13
        if (FlowControl & USART_CTS_Enable)
        {
            PIN_CFG.GPOI_Pin_Number = GPIO_PIN13;
            PIN_CFG.GPIO_Mode = GPIO_Floating_Input ;
            MCAL_GPIO_Init(GPIOB, &PIN_CFG);
        }

        // RTS PA14
        if (FlowControl & USART_RTS_Enable)
        {
            PIN_CFG.GPOI_Pin_Number = GPIO_PIN14;
            PIN_CFG.GPIO_Mode = Alternate_function_output_Push_pull;
            PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz;
            MCAL_GPIO_Init(GPIOA, &PIN_CFG);
        }
    }
}






/*********************************************************************
 * @fn      		  - MCAL_USART_SendData
 *
 * @brief             -Send Buffer on USART
 *
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param[in]         -pTxDatar Buffer
 * @param[in]         -PollingEn   Enable pooling or dsable it
 *
 * @return            -

 * @Note              - Should initialize USART First
 * 						//			When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
						//			the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
						//			because it is replaced by the parity.
						//			When receiving with the parity enabled, the value read in the MSB bit is the received parity
						//			bit

 */

void MCAL_USART_SendData(USART_t *USARTx, uint16_t *pTxData,uint8_t PollingEn ){

	uint16_t *pdata;



	/*Single byte communication
	The TXE bit is always cleared by a write to the data register.
	The TXE bit is set by hardware and it indicates:
	• The data has been moved from TDR to the shift register and the data transmission has started.
	• The TDR register is empty.
	• The next data can be written in the USART_DR register without overwriting the
	previous data.
	This flag generates an interrupt if the TXEIE bit is set. */


	// Waiting Until Data transmission starts then  TXE bit is set in SR Register
	if (PollingEn == PollingMechanism_EN)
		while(! (USARTx->SR & 1<<7 ) );

	//Check if USART Data Size is 9 BIT or 8 BIT

	// For 9 bit data
	if (G_USART_Config->DataSize ==USART_DataSize_9bit )
	{


		//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
		//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect because it is replaced by the parity.
		//	When receiving with the parity enabled, the value read in the MSB bit is the received parity bit

		// transfer the data to DR Register
		USARTx->DR = (*pTxData & (uint16_t)0x01FF);

	}else
	{   // for 8 bit data
		// transfer the data to DR Register
		USARTx->DR = (*pTxData  & (uint8_t)0xFF);
	}

}
void MCAL_USART_ReceiveData(USART_t *USARTx, uint16_t *pTxData ,uint8_t PollingEn ){

	// Waiting Until data received data  ,  RXNE is set
	if (PollingEn == PollingMechanism_EN)
	{
		while( ! (USARTx->SR & 1<<5 ));
	}


	//Check if USART Data Size is 9 BIT or 8 BIT

	// For 9 bit data
	if (G_USART_Config->DataSize ==USART_DataSize_9bit )
	{
		if (G_USART_Config->Parity == USART_Parity_Disable)
		{
			// if parity is disabled , we can consider that 9 bits for data
			*((uint16_t*) pTxData) = USARTx->DR ;

		}else
		{
			// if parity is enabled , so 8 bit for data and 1 bit for parity
			*((uint16_t*) pTxData) = ( USARTx->DR  & (uint8_t)0xFF );

		}

	}else
	{
		//For 8 bit data
		if (G_USART_Config->Parity == USART_Parity_Disable)
		{
			// if parity is disabled , we can consider that 8 bits for data
			*((uint16_t*) pTxData) = ( USARTx->DR  & (uint8_t)0xFF ) ;

		}else
		{
			// if parity is enabled , so 7 bit for data and 1 bit for parity
			*((uint16_t*) pTxData) = ( USARTx->DR  & (uint8_t)0X7F );

		}
	}



}

void MCAL_USART_WAIT_TC(USART_t *USARTx ) {

	// After writing the last data into the USART_DR register, wait until TC=1. This indicates
		//that the transmission of the last frame is complete
	while( ! (USARTx->SR & 1<<6 ));
}





					//ISRs
void USART1_IRQHandler (void)
{

	G_USART_Config->Ptr_ISR_Func () ;

}

void USART2_IRQHandler (void)
{
	G_USART_Config->Ptr_ISR_Func () ;

}
void USART3_IRQHandler (void)
{
	G_USART_Config->Ptr_ISR_Func () ;


}

