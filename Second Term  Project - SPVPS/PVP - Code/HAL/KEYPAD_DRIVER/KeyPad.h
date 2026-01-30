/*
 * KeyPad.h
 *
 *  Created on: Jan 22, 2026
 *  Developer & Tester : Eng - Belal Hani Sabha
 *  KeyPad Type : 4*3
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
//----------------------------------
//Includes
//----------------------------------
#include "stm32f103x6.h"
#include "GPIO.h"

//----------------------------------
//Macros
//----------------------------------
#define KeyPad_Port        GPIOB
// Rows
#define R0                 GPIO_PIN4
#define R1                 GPIO_PIN3
#define R2                 GPIO_PIN1
#define R3                 GPIO_PIN0
// Columns
#define C0                 GPIO_PIN5
#define C1                 GPIO_PIN6
#define C2                 GPIO_PIN7

/*
 * =======================================================================================
 * 							APIs Supported by "HAL KeyPad DRIVER"
 * =======================================================================================
 */
void    HAL_Keypad_Init();
uint8_t HAL_GetData_FromKeyPad();

#endif  /* KEYPAD_H_ */
