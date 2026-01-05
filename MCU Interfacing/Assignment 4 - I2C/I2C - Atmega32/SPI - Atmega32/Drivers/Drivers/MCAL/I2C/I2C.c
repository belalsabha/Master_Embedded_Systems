/*
 * I2C.c
 *
 * Created: 16/07/47 08:50:17
 * Author : Belal Hani Sabha
 */
#include "I2C.h"

#define F_CPU 8000000UL

void (*I2C_Callback)(void) = 0;

// ===============================================================

void MCAL_I2C_Init(I2C_t *I2Cx , I2C_Config_t *I2C_Config)
{
	I2Cx->TWAR = (I2C_Config->Slave_Address << 1);

	switch(I2C_Config->Prescaler)
	{
		case Prescaler_1:   I2Cx->TWSR &= ~((1<<0)|(1<<1)); break;
		case Prescaler_4:   I2Cx->TWSR = (I2Cx->TWSR & ~(1<<1)) | (1<<0); break;
		case Prescaler_16:  I2Cx->TWSR = (I2Cx->TWSR & ~(1<<0)) | (1<<1); break;
		case Prescaler_64:  I2Cx->TWSR |= (1<<0)|(1<<1); break;
	}

	I2Cx->TWBR = (uint8_t)(((F_CPU / I2C_Config->Speed) - 16) / (2 * I2C_Config->Prescaler));

	// Enable TWI and ACK
	TWCR = (1<<2) | (1<<6);  // TWEN=2, TWEA=6

	// IRQ setup
	if(I2C_Config->IRQ_Enable == I2C_IRQ_Enable)
	{
		TWCR |= (1<<0);         // TWIE=0
		I2C_Callback = I2C_Config->Ptr_ISR_Func;
		SREG |= 1 << 7 ;
	}
}

void MCAL_I2C_DeInit()
{
	I2C->TWAR = 0x00;
	I2C->TWBR = 0x00;
	I2C->TWSR &= ~((1<<0)|(1<<1)); // prescaler
	TWCR &= ~(1<<2); // disable TWEN
}

void Generate_Start_Bit()
{
	TWCR = (1<<7) | (1<<5) | (1<<2); // TWINT=7, TWSTA=5, TWEN=2
	while(!(TWCR & (1<<7)));
	while((I2C->TWSR & 0xF8) != 0x08);
}

void Generate_Stop_Bit()
{
	TWCR = (1<<7) | (1<<4) | (1<<2); // TWINT=7, TWSTO=4, TWEN=2
}

void MCAL_I2C_Master_Send(uint8_t Slave_Address, uint8_t Buff)
{
	Generate_Start_Bit();

	I2C->TWDR = (Slave_Address << 1);
	TWCR = (1<<7)|(1<<2); // TWINT=7, TWEN=2
	while(!(TWCR & (1<<7)));

	I2C->TWDR = Buff;
	TWCR = (1<<7)|(1<<2);
	while(!(TWCR & (1<<7)));

	Generate_Stop_Bit();
}

uint8_t MCAL_I2C_Master_Recieve(uint8_t Slave_Address)
{
	uint8_t data;
	Generate_Start_Bit();

	I2C->TWDR = (Slave_Address << 1) | 0x01;
	TWCR = (1<<7)|(1<<2);
	while(!(TWCR & (1<<7)));

	TWCR = (1<<7)|(1<<2);
	while(!(TWCR & (1<<7)));

	data = I2C->TWDR;
	Generate_Stop_Bit();
	return data;
}

void MCAL_I2C_Slave_Send(uint8_t Buff)
{
	I2C->TWDR = Buff;
	TWCR = (1<<7)|(1<<2)|(1<<6); // TWINT=7, TWEN=2, TWEA=6
	while(!(TWCR & (1<<7)));
}

uint8_t MCAL_I2C_Slave_Recieve(void)
{
	TWCR = (1<<7)|(1<<2)|(1<<6);
	while(!(TWCR & (1<<7)));
	return I2C->TWDR;
}

void __vector_19(void) __attribute__((signal, used));
void __vector_19(void)
{
	if(I2C_Callback) I2C_Callback();
}
