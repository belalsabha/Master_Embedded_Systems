/*
 * I2C.c
 *
 *  Created on: Jan 9, 2026
 *      Author:  Belal Hani Sabha
 */

#include "I2C.h"
#include "RCC.h"

/*
 * =======================================================================================
 * Generic Variables
 * =======================================================================================
 */
I2C_Config_t G_I2C_Config[2] = { NULL, NULL };

/*
 * =======================================================================================
 * Generic Macros
 * =======================================================================================
 */
#define I2C1_Index		0
#define I2C2_Index		1

/*
 * =======================================================================================
 * APIs Implementation
 * =======================================================================================
 */

/**================================================================
 * @Fn            - MCAL_I2C_Init
 * @brief         - Initialize the I2C peripheral according to user configuration
 * @param [in]    - I2Cx
 * @param [in]    - I2C_Config
 * @retval        - None
 */
void MCAL_I2C_Init(I2Cx_t* I2Cx, I2C_Config_t* I2C_Config)
{
	uint16_t tempreg = 0, freqRenge = 0, result;
	uint32_t pclk1;

	if (I2Cx == I2C1)
	{
		G_I2C_Config[I2C1_Index] = *I2C_Config;
		RCC_I2C1_CLK_EN();
	}
	else if (I2Cx == I2C2)
	{
		G_I2C_Config[I2C2_Index] = *I2C_Config;
		RCC_I2C2_CLK_EN();
	}

	if (I2C_Config->I2C_Mode == I2C_Mode_I2C)
	{
		tempreg = I2Cx->CR2;
		tempreg &= ~(I2C_CR2_FREQ);

		pclk1 = MCAL_RCC_Get_PCLK1Freqency();
		freqRenge = (uint16_t)(pclk1 / 1000000);

		tempreg |= freqRenge;
		I2Cx->CR2 = tempreg;

		I2Cx->CR1 &= ~(I2C_CR1_PE);
		tempreg = 0;

		if ((I2C_Config->CLK_SPEED == I2C_SCLK_SM_50K) ||
		    (I2C_Config->CLK_SPEED == I2C_SCLK_SM_100K))
		{
			result = (uint16_t)(pclk1 / (I2C_Config->CLK_SPEED << 1));
			tempreg |= result;
			I2Cx->CCR = tempreg;
			I2Cx->TRISE = freqRenge + 1;
		}

		tempreg = I2Cx->CR1;
		tempreg |= (uint16_t)(
				I2C_Config->I2C_ACK_Control |
				I2C_Config->General_Call_Address_Detection |
				I2C_Config->StretchMode |
				I2C_Config->I2C_Mode);
		I2Cx->CR1 = tempreg;

		tempreg = 0;
		if (I2C_Config->I2C_Slave_Address.Dual_ADD_ack)
		{
			tempreg = I2C_OAR2_ENDUAL;
			tempreg |= (I2C_Config->I2C_Slave_Address.Secondary_slave_address
			            << I2C_OAR2_ADD2_Pos);
			I2Cx->OAR2 = tempreg;
		}

		tempreg = 0;
		tempreg |= (I2C_Config->I2C_Slave_Address.Primary_slave_address << 1);
		tempreg |= I2C_Config->I2C_Slave_Address.I2C_Addressing_Slave_Mode;
		I2Cx->OAR1 = tempreg;
	}

	if (I2C_Config->P_Slave_Event_CallBack != NULL)
	{
		I2Cx->CR2 |= (I2C_CR2_ITERREN | I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN);

		if (I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_Enable;
			NVIC_IRQ32_I2C1_Enable;
		}
		else
		{
			NVIC_IRQ33_I2C2_Enable;
			NVIC_IRQ34_I2C2_Enable;
		}

		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}

	I2Cx->CR1 |= I2C_CR1_PE;
}

/**================================================================
 * @Fn            - MCAL_I2C_DeInit
 * @brief         - Deinitialize I2C peripheral
 * @param [in]    - I2Cx
 * @retval        - None
 */
void MCAL_I2C_DeInit(I2Cx_t* I2Cx)
{
	if (I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_Disable;
		NVIC_IRQ32_I2C1_Disable;
		RCC_I2C1_CLK_Reset();
	}
	else if (I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_Disable;
		NVIC_IRQ34_I2C2_Disable;
		RCC_I2C2_CLK_Reset();
	}
}

/**================================================================
 * @Fn            - MCAL_I2C_GPIO_Set_Pins
 * @brief         - Configure GPIO pins for I2C
 * @param [in]    - I2Cx
 * @retval        - None
 */
void MCAL_I2C_GPIO_Set_Pins(I2Cx_t* I2Cx)
{
	GPIO_Configure_Pin_t PIN_CFG;

	PIN_CFG.GPIO_Mode = Alternate_function_output_Open_drain;
	PIN_CFG.GPIO_Output_Frequency = Frequency_10MHz;

	if (I2Cx == I2C1)
	{
		PIN_CFG.GPOI_Pin_Number = GPIO_PIN6;
		MCAL_GPIO_Init(GPIOB, &PIN_CFG);

		PIN_CFG.GPOI_Pin_Number = GPIO_PIN7;
		MCAL_GPIO_Init(GPIOB, &PIN_CFG);
	}
	else if (I2Cx == I2C2)
	{
		PIN_CFG.GPOI_Pin_Number = GPIO_PIN10;
		MCAL_GPIO_Init(GPIOB, &PIN_CFG);

		PIN_CFG.GPOI_Pin_Number = GPIO_PIN11;
		MCAL_GPIO_Init(GPIOB, &PIN_CFG);
	}
}

/**================================================================
 * @Fn            - MCAL_I2C_Master_TX
 * @brief         - Master transmit data
 */
void MCAL_I2C_Master_TX(I2Cx_t* I2Cx, uint16_t devAdder,
                       uint8_t* dataOut, uint32_t dataLen,
                       Stop_Condition Stop, Repeated_Start Start)
{
	int i;

	I2C_GenerateStart(I2Cx, ENABLE, Start);
	while (!I2C_GetFlagStatus(I2Cx, EV5));

	I2C_SendAddress(I2Cx, devAdder, I2C_Direction_Transmitter);
	while (!I2C_GetFlagStatus(I2Cx, EV6));
	while (!I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANSMITTING));

	for (i = 0; i < dataLen; i++)
	{
		I2Cx->DR = dataOut[i];
		while (!I2C_GetFlagStatus(I2Cx, EV8));
	}

	if (Stop != Without_Stop)
		I2C_GenerateSTOP(I2Cx, ENABLE);
}

/**================================================================
 * @Fn            - MCAL_I2C_Master_RX
 * @brief         - Master receive data
 */
void MCAL_I2C_Master_RX(I2Cx_t* I2Cx, uint16_t devAdder,
                       uint8_t* dataOut, uint32_t dataLen,
                       Stop_Condition Stop, Repeated_Start Start)
{
	uint8_t index = (I2Cx == I2C1) ? I2C1_Index : I2C2_Index;
	int i;

	I2C_GenerateStart(I2Cx, ENABLE, Start);
	while (!I2C_GetFlagStatus(I2Cx, EV5));

	I2C_SendAddress(I2Cx, devAdder, I2C_Direction_Reciever);
	while (!I2C_GetFlagStatus(I2Cx, EV6));

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	for (i = dataLen; i > 1; i--)
	{
		while (!I2C_GetFlagStatus(I2Cx, EV7));
		*dataOut++ = I2Cx->DR;
	}

	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	while (!I2C_GetFlagStatus(I2Cx, EV7));
	*dataOut = I2Cx->DR;

	if (Stop != Without_Stop)
		I2C_GenerateSTOP(I2Cx, ENABLE);

	if (G_I2C_Config[index].I2C_ACK_Control == I2C_ACK_Enable)
		I2C_AcknowledgeConfig(I2Cx, ENABLE);
}

/**================================================================
 * @Fn            - I2C_GenerateStart
 * @brief         - Generate START condition
 */
void I2C_GenerateStart(I2Cx_t* I2Cx, FunctionalState NewStart, Repeated_Start Start)
{
	if (Start != repeated_Start)
	{
		while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	}

	if (NewStart != DISABLE)
		I2Cx->CR1 |= I2C_CR1_START;
	else
		I2Cx->CR1 &= ~(I2C_CR1_START);
}

/**================================================================
 * @Fn            - I2C_GenerateSTOP
 * @brief         - Generate STOP condition
 */
void I2C_GenerateSTOP(I2Cx_t* I2Cx, FunctionalState NewState)
{
	if (NewState == ENABLE)
	{
		I2Cx->CR1 |= I2C_CR1_STOP;
		I2Cx->SR2 &= ~(I2C_SR2_BUSY);
	}
	else
	{
		I2Cx->CR1 &= ~(I2C_CR1_STOP);
	}
}

/**================================================================
 * @Fn            - I2C_GetFlagStatus
 * @brief         - Get I2C flag status
 */
FlagStatus I2C_GetFlagStatus(I2Cx_t* I2Cx, Status Flag)
{
	volatile uint32_t dummyRead;
	uint32_t flag1, flag2, lastEvent = 0;
	FlagStatus bitStatus = RESET;

	switch (Flag)
	{
	case I2C_FLAG_BUSY:
		bitStatus = (I2Cx->SR2 & I2C_SR2_BUSY) ? SET : RESET;
		break;

	case EV5:
		bitStatus = (I2Cx->SR1 & I2C_SR1_SB) ? SET : RESET;
		break;

	case EV6:
		bitStatus = (I2Cx->SR1 & I2C_SR1_ADDR) ? SET : RESET;
		dummyRead = I2Cx->SR2;
		break;

	case MASTER_BYTE_TRANSMITTING:
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2 << 16;
		lastEvent = (flag1 | flag2) & 0x00FFFFFF;
		bitStatus = ((lastEvent & Flag) == Flag) ? SET : RESET;
		break;

	case EV8:
	case EV8_1:
		bitStatus = (I2Cx->SR1 & I2C_SR1_TXE) ? SET : RESET;
		break;

	case EV7:
		bitStatus = (I2Cx->SR1 & I2C_SR1_RXNE) ? SET : RESET;
		break;
	}

	return bitStatus;
}

/**================================================================
 * @Fn            - I2C_SendAddress
 * @brief         - Send slave address with R/W bit
 */
void I2C_SendAddress(I2Cx_t* I2Cx, uint16_t Address, I2C_Direction Direction)
{
	Address <<= 1;

	if (Direction == I2C_Direction_Reciever)
		Address |= 1;
	else
		Address &= ~(1);

	I2Cx->DR = Address;
}

/**================================================================
 * @Fn            - MCAL_I2C_SlaveSendData
 * @brief         - Send data as slave
 */
void MCAL_I2C_SlaveSendData(I2Cx_t* I2Cx, uint8_t data)
{
	I2Cx->DR = data;
}

/**================================================================
 * @Fn            - MCAL_I2C_SlaveReceiveData
 * @brief         - Receive data as slave
 */
uint8_t MCAL_I2C_SlaveReceiveData(I2Cx_t* I2Cx)
{
	return (uint8_t)I2Cx->DR;
}

/**================================================================
 * @Fn            - I2C_AcknowledgeConfig
 * @brief         - Enable or disable ACK
 */
void I2C_AcknowledgeConfig(I2Cx_t* I2Cx, FunctionalState NewState)
{
	if (NewState != DISABLE)
		I2Cx->CR1 |= I2C_CR1_ACK;
	else
		I2Cx->CR1 &= ~(I2C_CR1_ACK);
}
