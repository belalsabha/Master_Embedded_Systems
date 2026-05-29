/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Jan 10, 2026
 *      Author: Belal Hani Sabha
 */

#include "I2C_Slave_EEPROM.h"

// =======================================================================================
// Initialize I2C Peripheral for EEPROM communication
// =======================================================================================
/**================================================================
 * @Fn            - eeprom_init
 * @brief         - Initialize the I2C peripheral and configure pins for EEPROM
 * @retval        - None
 */
void eeprom_init(void)
{
	I2C_Config_t I2C1CFG;

	// Configure I2C settings
	I2C1CFG.General_Call_Address_Detection = I2C_ENGC_Enable; // Enable general call
	I2C1CFG.I2C_ACK_Control = I2C_ACK_Enable;                  // Enable ACK
	I2C1CFG.CLK_SPEED = I2C_SCLK_SM_100K;                     // Standard mode 100kHz
	I2C1CFG.I2C_Mode = I2C_Mode_I2C;                          // I2C mode
	I2C1CFG.P_Slave_Event_CallBack = NULL;                    // No callback for master
	I2C1CFG.StretchMode = I2C_StretchMode_Enable;             // Enable clock stretching

	// Initialize GPIO pins for I2C1 (PB6=SCL, PB7=SDA)
	MCAL_I2C_GPIO_Set_Pins(I2C1);

	// Initialize I2C1 peripheral
	MCAL_I2C_Init(I2C1, &I2C1CFG);
}

// =======================================================================================
// Write multiple bytes to EEPROM starting from a memory address
// =======================================================================================
/**================================================================
 * @Fn            - eeprom_write_Nbytes
 * @brief         - Write multiple bytes to EEPROM
 * @param [in]    - Memory_address: EEPROM memory location to start writing
 * @param [in]    - bytes: pointer to the buffer containing data to write
 * @param [in]    - Data_Length: number of bytes to write
 * @retval        - status (0=success)
 */
unsigned char eeprom_write_Nbytes(unsigned int Memory_address, unsigned char* bytes, uint8_t Data_Length)
{
	uint8_t i;
	uint8_t buffer[258]; // 2 bytes for memory address + data

	// Split memory address into two bytes (MSB first)
	buffer[0] = (uint8_t)(Memory_address >> 8);  // Upper memory address
	buffer[1] = (uint8_t)(Memory_address);       // Lower memory address

	// Copy data bytes into buffer
	for(i = 0; i < Data_Length; i++)
	{
		buffer[i + 2] = bytes[i];
	}

	// Send the address + data via I2C
	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_address, buffer, (Data_Length + 2), With_Stop, Start);

	return 0;
}

// =======================================================================================
// Read bytes from EEPROM starting from a memory address
// =======================================================================================
/**================================================================
 * @Fn            - eeprom_read_byte
 * @brief         - Read bytes from EEPROM
 * @param [in]    - address: EEPROM memory location to start reading
 * @param [out]   - dataOut: pointer to buffer to store read data
 * @param [in]    - dataLen: number of bytes to read
 * @retval        - status (0=success)
 */
unsigned char eeprom_read_byte(unsigned int address, uint8_t* dataOut, uint8_t dataLen)
{
	uint8_t buffer[2];

	// Split memory address into two bytes (MSB first)
	buffer[0] = (uint8_t)(address >> 8); // Upper memory address
	buffer[1] = (uint8_t)(address);      // Lower memory address

	// Send memory address to EEPROM (no STOP, repeated start will follow)
	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_address, buffer, 2, Without_Stop, Start);

	// Read dataLen bytes from EEPROM
	MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_address, dataOut, dataLen, With_Stop, repeated_Start);

	return 0;
}
