/*
 * SPI.c
 *
 *  Created on: Dec 30, 2025
 *      Author:  Belal Hani Sabha
 */


#include "SPI.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
SPI_Config_t  *G_SPI_Config[2]  = { NULL,NULL } ;
SPI_Config_t  G_SPI1_Config  	 ;

SPI_Config_t  G_SPI2_Config		 ;



/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */
#define 	SPI1_Index		0
#define 	SPI2_Index		1

/*
 * =======================================================================================
 * 							APIs Implementation
 * =======================================================================================
 */
/**================================================================
 * @Fn				- MCAL_SPI_Init
 * @brief 			- Initializes the SPI module according to the specified parameters.
 * @param [in] 		- SPIx: where x can be (1..2 depending on device used)
 * @param [in] 		- SPI_Config: All SPI Configuration
 * @retval 			-none
 * Note				-none
 */
void MCAL_SPI_Init(SPI_t *SPIx , SPI_Config_t  *SPI_Config){

	// Satfty For Control Registers ..
	// Write on these Variables then Assign Value to CR Register
	uint16_t Temp_CR1 = 0 ;

	uint16_t Temp_CR2 = 0 ;

	if(SPIx == SPI1){
		G_SPI1_Config = *SPI_Config;
	G_SPI_Config[SPI1_Index]= &G_SPI1_Config;
	RCC_SPI1_CLK_EN();

	}

	if(SPIx == SPI2){
		G_SPI2_Config = *SPI_Config;

		G_SPI_Config[SPI2_Index]= &G_SPI2_Config ;
		RCC_SPI2_CLK_EN();
	}


	/*Bit 6 SPE: SPI enable
		0: Peripheral disabled
		1: Peripheral enabled*/
	Temp_CR1 |= (1 << 6);

	/*Bit 2MSTR: Master selection
		0: Slave configuration
		1: Master configuration*/
	 Temp_CR1 |= SPI_Config->Device_Mode ;

    // Communication_Mode
	 Temp_CR1 |= SPI_Config->Communication_Mode ;

	 /*Bit 11 DFF: Data frame format
	 	 0: 8-bit data frame format is selected for transmission/reception
	 	 1: 16-bit data frame format is selected for transmission/reception   */
	 Temp_CR1 |= SPI_Config->Frame_Format ;

	 /*Bit1 CPOL: Clock polarity
	 0: CK to 0 when idle
	 1: CK to 1 when idle   */
	 Temp_CR1 |= SPI_Config->ClockPolarity ;

	 /*Bit 0 CPHA: Clock phase
	 0: The first clock transition is the first data capture edge
	 1: The second clock transition is the first data capture edge
	 */
	 Temp_CR1 |= SPI_Config->ClockPhase ;


	 /***************************************************************************************************/

	 //NSS
	 if(SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_enable){

		 Temp_CR2 |= SPI_Config->NSS ;

	 }else if(SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_disable)
	 {
		 Temp_CR2 &= SPI_Config->NSS ;

	 }else {

		 Temp_CR1 |= SPI_Config->NSS ;
	 }

	 /***************************************************************************************************/
	 /*Bits 5:3  BR[2:0]: Baud rate control */
	 Temp_CR1 |= SPI_Config->SPIClockSpeed ;

	 /***************************************************************************************************/

	 //Bit 7 TXEIE: Tx buffer empty interrupt enable >> 1 = Set
	 //Bit 6 RXNEIE: RX buffer not empty interrupt enable >> 1 = Set
	 //Bit 5 ERRIE: Error interrupt enable   >> 1 = Set
	 if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_Disabled ){

		 Temp_CR2 |= SPI_Config->IRQ_Enable ;


		 // Select What SPI Should Open NVIC For it
			if(SPIx == SPI1){

				NVIC_IRQ37_SPI1_Enable;

			}

			if(SPIx == SPI2){

				NVIC_IRQ38_SPI2_Enable;
			}


	 }

		// Write on SPIx Registers
		SPIx->CR1 = Temp_CR1 ;
		SPIx->CR2 = Temp_CR2 ;
}



/**================================================================
 * @Fn				- MCAL_SPI_DeInit
 * @brief 			- Deinitializes the SPI module.
 * @param [in] 		- SPIx: where x can be (1..2 depending on device used)
 * @retval 			-none
 * Note				-Reset the Model By RCC
 */
void MCAL_SPI_DeInit(SPI_t *SPIx ){

	if(SPIx == SPI1){

		RCC_SPI1_CLK_Reset();
		NVIC_IRQ37_SPI1_Disable;
	}

	if(SPIx == SPI2){

		RCC_SPI2_CLK_Reset();
		NVIC_IRQ38_SPI2_Disable;
	}
}


/**================================================================
 * @Fn				-  MCAL_SPI_GPIO_Set_Pins
 * @brief 			-  Configures GPIO pins for the SPI module
 * @param [in] 		-  SPIx: where x can be (1..2 depending on device used)
 * @retval 			-none
 * Note				-none
 */

void MCAL_SPI_GPIO_Set_Pins(SPI_t *SPIx ){

	GPIO_Configure_Pin_t PIN_CFG;

	if(SPIx == SPI1){
		/* SPI1_NSS  PA4
		 * SPI1_SCK	 PA5
		 * SPI1_MISO PA6
		 * SPI1_MOSI PA7
		 * */


		if(G_SPI_Config[SPI1_Index]->Device_Mode == SPI_Master_Mode){ // Master
			//SPIx_NSS  PA4
				//Hardware master  /slave >>  Input floating/ Input pull-up / Input pull-down
				//Hardware master >> / NSS output enabled Alternate function push-pull
				//Software Not used. Can be used as a GPIO

			switch(G_SPI_Config[SPI1_Index]->NSS){
			//NSS output
			case SPI_NSS_Hard_Master_SS_output_enable : PIN_CFG.GPIO_Mode =  Alternate_function_output_Push_pull    ;
														PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz ;
														PIN_CFG.GPOI_Pin_Number = GPIO_PIN4 ;
														MCAL_GPIO_Init(GPIOA, &PIN_CFG);
				break;
				//NSS input
			case SPI_NSS_Hard_Master_SS_output_disable: PIN_CFG.GPIO_Mode =   GPIO_Floating_Input  ;
														PIN_CFG.GPOI_Pin_Number = GPIO_PIN4 ;
														MCAL_GPIO_Init(GPIOA, &PIN_CFG);
				break;


			}

			//SPI1_SCK	 PA5
			//Master  >>  Alternate function push-pull
			PIN_CFG.GPIO_Mode =  Alternate_function_output_Push_pull    ;
			PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz ;
			PIN_CFG.GPOI_Pin_Number = GPIO_PIN5 ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG);

			//SPI1_MISO PA6
			//Full duplex / master >>  Input floating / Input pull-up
			PIN_CFG.GPIO_Mode =   GPIO_Floating_Input  ;
			PIN_CFG.GPOI_Pin_Number = GPIO_PIN6 ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG);

			// SPI1_MOSI PA7
			//Full duplex  / master  >>  Alternate function push-pull
			PIN_CFG.GPIO_Mode =  Alternate_function_output_Push_pull    ;
			PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz ;
			PIN_CFG.GPOI_Pin_Number = GPIO_PIN7 ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG);


			}else{ // Slave
			//SPIx_NSS  PA4
			//Hardware master  /slave >>  Input floating/ Input pull-up / Input pull-down

			if(G_SPI_Config[SPI1_Index]->NSS == SPI_NSS_Hard_Slave){

					PIN_CFG.GPIO_Mode =   GPIO_Floating_Input  ;
					PIN_CFG.GPOI_Pin_Number = GPIO_PIN4 ;
					MCAL_GPIO_Init(GPIOA, &PIN_CFG);
			}
			//SPI1_SCK	 PA5
			//Slave  >> Input floating
			PIN_CFG.GPIO_Mode =   GPIO_Floating_Input  ;
			PIN_CFG.GPOI_Pin_Number = GPIO_PIN5 ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG);

			//SPI1_MISO PA6
			//Full duplex /  slave  >> (point to point) Alternate function push-pull
			PIN_CFG.GPIO_Mode =   Alternate_function_output_Push_pull   ;
			PIN_CFG.GPOI_Pin_Number = GPIO_PIN6 ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG);

			// SPI1_MOSI PA7
			//Full duplex /  slave  >> Input floating / Input pull-up
			PIN_CFG.GPIO_Mode =   GPIO_Floating_Input  ;
			PIN_CFG.GPOI_Pin_Number = GPIO_PIN7;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG);

		}}
        if(SPIx == SPI2){
		/* SPI2_NSS  PB12
		 * SPI2_SCK	 PB13
		 * SPI2_MISO PB14
		 * SPI2_MOSI PB15
		 * */

        	if(G_SPI_Config[SPI2_Index]->Device_Mode == SPI_Master_Mode){ // Master
        		//SPIx_NSS  PB12
        		//Hardware master  /slave >>  Input floating/ Input pull-up / Input pull-down
        		//Hardware master >> / NSS output enabled Alternate function push-pull
        		//Software Not used. Can be used as a GPIO

        		switch(G_SPI_Config[SPI2_Index]->NSS){
        		//NSS output
        		case SPI_NSS_Hard_Master_SS_output_enable : PIN_CFG.GPIO_Mode =  Alternate_function_output_Push_pull    ;
        		PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz ;
        		PIN_CFG.GPOI_Pin_Number = GPIO_PIN12 ;
        		MCAL_GPIO_Init(GPIOB, &PIN_CFG);
        		break;
        		//NSS input
        		case SPI_NSS_Hard_Master_SS_output_disable: PIN_CFG.GPIO_Mode =   GPIO_Floating_Input  ;
        		PIN_CFG.GPOI_Pin_Number = GPIO_PIN12 ;
        		MCAL_GPIO_Init(GPIOB, &PIN_CFG);
        		break;


        		}

        		//SPI1_SCK	 PB13
        		//Master  >>  Alternate function push-pull
        		PIN_CFG.GPIO_Mode =  Alternate_function_output_Push_pull    ;
        		PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz ;
        		PIN_CFG.GPOI_Pin_Number = GPIO_PIN13 ;
        		MCAL_GPIO_Init(GPIOB, &PIN_CFG);

        		//SPI1_MISO PB14
        		//Full duplex / master >>  Input floating / Input pull-up
        		PIN_CFG.GPIO_Mode =   GPIO_Floating_Input  ;
        		PIN_CFG.GPOI_Pin_Number = GPIO_PIN14 ;
        		MCAL_GPIO_Init(GPIOB, &PIN_CFG);

        		// SPI1_MOSI PB15
        		//Full duplex  / master  >>  Alternate function push-pull
        		PIN_CFG.GPIO_Mode =  Alternate_function_output_Push_pull    ;
        		PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz ;
        		PIN_CFG.GPOI_Pin_Number = GPIO_PIN15 ;
        		MCAL_GPIO_Init(GPIOB, &PIN_CFG);


        	}else{ // Slave
        	//SPIx_NSS  PB12
        	//Hardware master  /slave >>  Input floating/ Input pull-up / Input pull-down

        	if(G_SPI_Config[SPI1_Index]->NSS == SPI_NSS_Hard_Slave){

        		PIN_CFG.GPIO_Mode =   GPIO_Floating_Input  ;
        		PIN_CFG.GPOI_Pin_Number = GPIO_PIN12 ;
        		MCAL_GPIO_Init(GPIOB, &PIN_CFG);
        	}
        	//SPI1_SCK	 PB13
        	//Slave  >> Input floating
        	PIN_CFG.GPIO_Mode =   GPIO_Floating_Input  ;
        	PIN_CFG.GPOI_Pin_Number = GPIO_PIN13 ;
        	MCAL_GPIO_Init(GPIOB, &PIN_CFG);

        	//SPI1_MISO PB14
        	//Full duplex /  slave  >> (point to point) Alternate function push-pull
        	PIN_CFG.GPIO_Mode =   Alternate_function_output_Push_pull   ;
        	PIN_CFG.GPOI_Pin_Number = GPIO_PIN14 ;
        	MCAL_GPIO_Init(GPIOB, &PIN_CFG);

        	// SPI1_MOSI PB15
        	//Full duplex /  slave  >> Input floating / Input pull-up
        	PIN_CFG.GPIO_Mode =   GPIO_Floating_Input  ;
        	PIN_CFG.GPOI_Pin_Number = GPIO_PIN15;
        	MCAL_GPIO_Init(GPIOB, &PIN_CFG);


}
        }
				}

/*********************************************************************
 * @fn      		  - MCAL_SPI_SendData
 *
 * @brief             -Sends data using SPI communication in Full Duplex Master/Slave
						and Half Duplex Master modes.
 *
 * @param [in] 		  - SPIx: where x can be (1..2 depending on device used)
 * @param[in]         -pTxBuff
 * @param[in]         -PollingEn   Enable pooling or dsable it
 *
 * @return            - none

 * @Note              - none

 */

void MCAL_SPI_SendData(SPI_t *SPIx , uint16_t *pTxBuff ,uint8_t PollingEn){

	/*Bit 1 TXE: Transmit buffer empty
		0: Tx buffer not empty
		1: Tx buffer empty*/
	if (PollingEn == PollingMechanism_EN)
		while(! (SPIx->SR & (1<<1)) );

	SPIx->DR =  *pTxBuff;

}




/*********************************************************************
 * @fn      		  - MCAL_SPI_ReceiveData
 *
 * @brief             -Receives data using SPI communication in Full Duplex Master/Slave
						and Half Duplex Slave modes.
 * @param [in] 		  - SPIx: where x can be (1..2 depending on device used)
 * @param[in]         -pTxBuff
 * @param[in]         -PollingEn   Enable pooling or dsable it
 *
 * @return            - none

 * @Note              - none

 */

void MCAL_SPI_ReceiveData(SPI_t *SPIx , uint16_t *pTxBuff ,uint8_t PollingEn){


	/*Bit 0 RXNE: Receive buffer not empty
		0: Rx buffer empty
		1: Rx buffer not empty*/
	if (PollingEn == PollingMechanism_EN)
		while( ! (SPIx->SR & (1<<0) ));

	*pTxBuff = SPIx->DR ;

}







/*********************************************************************
 * @fn      		  - MCAL_SPI_TX_RX
 *
 * @brief             -Transmits and receives data using SPI communication in Full Duplex
						Master/Slave mode only.
 * @param [in] 		  - SPIx: where x can be (1..2 depending on device used)
 * @param[in]         -pTxBuff
 * @param[in]         -PollingEn   Enable pooling or dsable it
 *
 * @return            - none

 * @Note              - none

 */

void MCAL_SPI_TX_RX(SPI_t *SPIx , uint16_t *pTxBuff ,uint8_t PollingEn){

	if (PollingEn == PollingMechanism_EN)
		while(! (SPIx->SR & (1<<1)) );
    SPIx->DR =  *pTxBuff;


	if (PollingEn == PollingMechanism_EN)
		while( ! (SPIx->SR & (1<<0) ));
	*pTxBuff = SPIx->DR ;

}

//ISRs
void SPI1_IRQHandler (void)
{
	struct IRQ_SRC   IRQ_Source ;
	IRQ_Source.TXE = ((SPI1->SR & (1 << 1)) >> 1 );
	IRQ_Source.RXNE = ((SPI1->SR & (1 << 0)) >> 0 );
	IRQ_Source.ERRIE = ((SPI1->SR & (1 << 4)) >> 4 );

	G_SPI_Config[SPI1_Index]->Ptr_ISR_Func(IRQ_Source) ;

}

void SPI2_IRQHandler (void)
{
	    struct IRQ_SRC   IRQ_Source ;

		IRQ_Source.TXE = ((SPI2->SR & (1 << 1)) >> 1 );
		IRQ_Source.RXNE = ((SPI2->SR & (1 << 0)) >> 0 );
		IRQ_Source.ERRIE = ((SPI2->SR & (1 << 4)) >> 4 );

	    G_SPI_Config[SPI2_Index]->Ptr_ISR_Func(IRQ_Source) ;

}



