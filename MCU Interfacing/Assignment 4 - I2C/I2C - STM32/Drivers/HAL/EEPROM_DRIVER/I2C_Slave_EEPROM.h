/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Jan 10, 2026
 *      Author:  Belal Hani Sabha
 */

#ifndef EEPROM_DRIVER_I2C_SLAVE_EEPROM_H_
#define EEPROM_DRIVER_I2C_SLAVE_EEPROM_H_

#include "I2C.h"

// =======================================================================================
// EEPROM I2C Interface
// =======================================================================================

// EEPROM is an I2C SLAVE device
// Modes:
// - Idle mode: device is in high-impedance state and waits for data
// - Master Transmitter mode: the device transmits data to a slave receiver
// - Master Receiver mode: the device receives data from a slave transmitter

#define EEPROM_Slave_address   0x2A   // 7-bit I2C address of the EEPROM

// =======================================================================================
// Function Prototypes
// =======================================================================================


void eeprom_init(void);


unsigned char eeprom_write_Nbytes(unsigned int Memory_address, unsigned char* bytes, uint8_t Data_Length);


unsigned char eeprom_read_byte(unsigned int address, uint8_t* dataOut, uint8_t dataLen);






#endif /* EEPROM_DRIVER_I2C_SLAVE_EEPROM_H_ */
