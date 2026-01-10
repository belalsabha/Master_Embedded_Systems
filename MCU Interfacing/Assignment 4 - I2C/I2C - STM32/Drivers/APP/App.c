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
//Global Macros
//----------------------------------


#define SPI_Act_As_Master
//#define SPI_Act_As_Slave

//----------------------------------
//Global Variables
//----------------------------------
	volatile uint8_t Data;




//----------------------------------
//Local Function
//----------------------------------
	void SPI_IRQ_CallBack(struct IRQ_SRC irq_src)
	{
	#ifdef SPI_Act_As_Slave
		if(irq_src.RXNE)
		{
			MCAL_SPI_TX_RX(SPI1, &Data, PollingMechanism_Dis);
			MCAL_USART_SendData(USART1, &Data,PollingMechanism_EN);
		}

	#endif



	}


	/* USART IRQ Callback */
	void USART_IRQ_Callback(void)
	{
		MCAL_USART_ReceiveData(USART1, &Data, PollingMechanism_Dis);
		MCAL_USART_SendData(USART1, &Data, PollingMechanism_EN);
		 MCAL_GPIO_WritePin(GPIOA,  GPIO_PIN4, 0);

		MCAL_SPI_TX_RX(SPI1, &Data, PollingMechanism_EN);

		 MCAL_GPIO_WritePin(GPIOA,  GPIO_PIN4, 1);
	}


	void delay(unsigned int count)
	{
	    volatile unsigned int i;
	    for (i = 0; i < count; i++)
	    {
	        /* Do nothing – just waste time */
	    }
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
	 *                 -  Configures SPI1
	 */
void APP_Init(void){


    RCC_AFIO_CLK_EN();
    RCC_GPIOA_CLK_EN();
    RCC_GPIOB_CLK_EN();


/*
	//==========================USART Init============================
	//PA9 TX
	//PA10 RX
	//PA11 CTS
	//PA12 RTS
	USART_Config_t uartConfig;
	uartConfig.BaudRate     = USART_BaudRate_115200;
	uartConfig.DataSize     = USART_DataSize_8bit;
	uartConfig.FlowCtrl     = USART_CTS_RTS_Disable;
	uartConfig.IRQ_Enable   = USART_IRQ_Enable_RXNEIE;
	uartConfig.Parity       = USART_Parity_Disable;
	uartConfig.Ptr_ISR_Func = USART_IRQ_Callback;
	uartConfig.StopBitNo    = USART_StopBitNo_1;
	uartConfig.USART_Mode   = USART_Mode_TX_RX_Enable;

	MCAL_USART_GPIO_Set_Pins(USART1);
	MCAL_USART_Init(USART1, &uartConfig);


	//==========================SPI1 Init============================
	// PA4  : SPI1_NSS
	// PA5  : SPI1_SCK
	// PA6  : SPI1_MISO
	// PA7  : SPI1_MOSI
    SPI_Config_t spiConfig;
    spiConfig.ClockPhase =  SecondClockTransition_isTheFirstDataCaptureEdge ;
    spiConfig.ClockPolarity = ClkPolartitIdle_HIGH ;
	spiConfig.SPIClockSpeed = SPI_BAUDRATEPRESCALER_8 ;
	spiConfig.DataSize = DataFrameFormat_8Bit ;
	spiConfig.Frame_Format = MSB_First ;
	spiConfig.Communication_Mode = SPI_DIRECTION_2LINES ;
#ifdef SPI_Act_As_Master
	spiConfig.Device_Mode = SPI_Master_Mode ;
	spiConfig.IRQ_Enable  = SPI_IRQ_Enable_Disabled ;
	spiConfig.NSS         = SPI_NSS_Soft_NSSInternalSoft_Set;
	spiConfig.Ptr_ISR_Func = NULL ;
	MCAL_SPI_Init(SPI1, &spiConfig);
	MCAL_SPI_GPIO_Set_Pins(SPI1);

	GPIO_Configure_Pin_t PIN_CFG;

	PIN_CFG.GPIO_Mode =  output_push_pull    ;
	PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz ;
    PIN_CFG.GPOI_Pin_Number = GPIO_PIN4 ;
	MCAL_GPIO_Init(GPIOA, &PIN_CFG);

	 MCAL_GPIO_WritePin(GPIOA,  GPIO_PIN4, 1);
#endif

#ifdef SPI_Act_As_Slave
	spiConfig.Device_Mode  = SPI_Slave_Mode;
	spiConfig.IRQ_Enable   = SPI_IRQ_Enable_RXNEIE ;
	spiConfig.NSS          = SPI_NSS_Hard_Slave;
	spiConfig.Ptr_ISR_Func = SPI_IRQ_CallBack ;
	MCAL_SPI_Init(SPI1, &spiConfig);
	MCAL_SPI_GPIO_Set_Pins(SPI1);
#endif


*/

    // =======================================================================================
    // EEPROM Test Cases
    // =======================================================================================
    // ------------------------------
    // Test Case 1: Write and Read 7 bytes
    // ------------------------------
    unsigned char ch1[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7}; // Data to write
    unsigned char ch2[7] = {0};                               // Buffer to read data into

    eeprom_init();                                            // Initialize I2C and EEPROM
    eeprom_write_Nbytes(0xAF, ch1, 7);                       // Write 7 bytes starting at address 0xAF
    eeprom_read_byte(0xAF, ch2, 7);                          // Read back 7 bytes from address 0xAF

    delay(1000);                                              // Wait 1 second (optional for EEPROM write cycle)

    // ------------------------------
    // Test Case 2: Write and Read 4 bytes at a different address
    // ------------------------------
    ch1[0] = 0xA;
    ch1[1] = 0xB;
    ch1[2] = 0xC;
    ch1[3] = 0xD;

    eeprom_write_Nbytes(0xFFF, ch1, 4);                      // Write 4 bytes starting at address 0xFFF
    eeprom_read_byte(0xFFF, ch2, 4);                         // Read back 4 bytes from address 0xFFF

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


}
