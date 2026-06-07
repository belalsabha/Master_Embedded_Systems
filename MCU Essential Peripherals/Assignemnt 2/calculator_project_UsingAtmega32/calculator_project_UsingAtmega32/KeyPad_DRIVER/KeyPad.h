/*
 * KeyPad.h
 *
 *  Created on: Jan 22, 2026
 *  Developer : Eng - Ahmad Ali Assad
 *  Tester : Eng - Belal Hani Sabha
 *  KeyPad Type : 4*4
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

//----------------------------------
// Includes
//----------------------------------
#include "IO.h"
#include "PLATFORM_TYPES.h"

//----------------------------------
//Macros
//----------------------------------

				// ----------------------------------Port Selection---------------------------------
//port				
#define KeyPad_Port    IOD
//rows & columns
#define R0    IO_PIN1
#define R1    IO_PIN2
#define R2    IO_PIN3
#define R3    IO_PIN0
#define C0    IO_PIN4
#define C1    IO_PIN5
#define C2    IO_PIN6
#define C3    IO_PIN7

/*
 * =======================================================================================
 * 							APIs Supported by "HAL KeyPad DRIVER"
 * =======================================================================================
 */
void    HAL_Keypad_Init();
uint8_t HAL_GetData_FromKeyPad();



#endif /* KEYPAD_H_ */