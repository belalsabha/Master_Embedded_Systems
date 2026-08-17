/*
 * I2C.h
 *
 *  Created on: Jan 9, 2026
 *      Author:  Belal Hani Sabha
 */

#ifndef MCAL_I2C_DRIVER_I2C_H_
#define MCAL_I2C_DRIVER_I2C_H_

//----------------------------------
// Includes
//----------------------------------
#include "stm32f103x6.h"
#include "GPIO.h"


//----------------------------------
// Slave Address Structure
//----------------------------------
struct S_I2C_Slave_Device_Address
{
	uint16_t	Dual_ADD_ack;					// 1-Enable  0-Disable
	uint16_t	Primary_slave_address;
	uint16_t	Secondary_slave_address;
	uint32_t	I2C_Addressing_Slave_Mode;		// @ref I2C_Addressing_Slave
};


//----------------------------------
// Enumerations
//----------------------------------
typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,	// APP layer should send data
	I2C_EV_DATA_RCV		// APP layer should read data
} Slave_State;


typedef enum
{
	With_Stop,
	Without_Stop
} Stop_Condition;


typedef enum
{
	Start,
	repeated_Start
} Repeated_Start;


typedef enum
{
	RESET = 0,
	SET   = 1
} FlagStatus;


typedef enum
{
	DISABLE = 0,
	ENABLE  = 1
} FunctionalState;


typedef enum
{
	I2C_FLAG_BUSY = 0,
	EV5,		// SB=1, cleared by reading SR1 then writing DR with Address
	EV6,		// ADDR=1, cleared by reading SR1 then SR2
	EV8,		// TxE=1, DR empty
	EV8_1,		// TxE=1, shift register empty
	EV8_2,		// TxE=1, BTF=1, Stop requested
	EV7,
	MASTER_BYTE_TRANSMITTING = ((uint32_t)0x00070000)	// TRA, MSL, TXE, BUSY
} Status;


typedef enum
{
	I2C_Direction_Transmitter = 0,
	I2C_Direction_Reciever   = 1
} I2C_Direction;


#define I2C_EVENT_MASTER_BYTE_TRANSMITTING	((uint32_t)0x00070000)


//----------------------------------
// User Configuration Structure
//----------------------------------
typedef struct
{
	uint16_t	CLK_SPEED;						// @ref I2C_SCLK
	uint32_t	StretchMode;					// @ref I2C_StretchMode
	uint32_t	I2C_Mode;						// @ref I2C_Mode
	uint32_t	I2C_ACK_Control;				// @ref I2C_ACK
	uint32_t	General_Call_Address_Detection;	// @ref I2C_ENGC

	struct S_I2C_Slave_Device_Address I2C_Slave_Address;

	void (*P_Slave_Event_CallBack)(Slave_State state);	// Slave ISR callback

} I2C_Config_t;


//========================================================================================
// Reference Macros
//========================================================================================

// @ref I2C_SCLK
#define I2C_SCLK_SM_50K			(0x50000U)
#define I2C_SCLK_SM_100K		(0x100000U)
#define I2C_SCLK_FM_200K		(0x200000U)		// Not supported yet
#define I2C_SCLK_FM_400K		(0x400000U)		// Not supported yet


// @ref I2C_StretchMode
#define I2C_StretchMode_Enable		(0)
#define I2C_StretchMode_Disable		I2C_CR1_NOSTRETCH


// @ref I2C_Mode
#define I2C_Mode_I2C				(0U)
#define I2C_Mode_SMBus				I2C_CR1_SMBUS


// @ref I2C_ACK
#define I2C_ACK_Enable				I2C_CR1_ACK
#define I2C_ACK_Disable				(0)


// @ref I2C_Addressing_Slave
#define I2C_Addressing_Slave_7Bit	(0)
#define I2C_Addressing_Slave_10Bit	(1 << 15)


// @ref I2C_ENGC
#define I2C_ENGC_Enable				I2C_CR1_ENGC
#define I2C_ENGC_Disable			(0)


//========================================================================================
// APIs Supported by "MCAL I2C DRIVER"
//========================================================================================
void MCAL_I2C_Init(I2Cx_t* I2Cx, I2C_Config_t* I2C_Config);
void MCAL_I2C_DeInit(I2Cx_t* I2Cx);

void MCAL_I2C_GPIO_Set_Pins(I2Cx_t* I2Cx);

// Master Polling APIs
void MCAL_I2C_Master_TX(I2Cx_t* I2Cx, uint16_t devAdder, uint8_t* dataOut,
						uint32_t dataLen, Stop_Condition Stop, Repeated_Start Start);

void MCAL_I2C_Master_RX(I2Cx_t* I2Cx, uint16_t devAdder, uint8_t* dataOut,
						uint32_t dataLen, Stop_Condition Stop, Repeated_Start Start);

// Slave Interrupt APIs
void MCAL_I2C_SlaveSendData(I2Cx_t* I2Cx, uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData(I2Cx_t* I2Cx);


// Generic APIs
void I2C_GenerateStart(I2Cx_t* I2Cx, FunctionalState NewStart, Repeated_Start Start);
void I2C_GenerateSTOP(I2Cx_t* I2Cx, FunctionalState NewState);
FlagStatus I2C_GetFlagStatus(I2Cx_t* I2Cx, Status Flag);
void I2C_SendAddress(I2Cx_t* I2Cx, uint16_t Address, I2C_Direction Direction);
void I2C_AcknowledgeConfig(I2Cx_t* I2Cx, FunctionalState NewState);


#endif /* MCAL_I2C_DRIVER_I2C_H_ */



