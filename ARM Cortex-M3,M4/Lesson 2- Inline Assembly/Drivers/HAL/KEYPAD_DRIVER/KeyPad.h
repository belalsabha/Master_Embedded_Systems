/*
 * keyPad.h
 *
 *  Created on: Dec 10, 2025
 *  Author: Belal Hani Sabha
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Stm32f103x6.h"

#include "GPIO.h"


#define KEYPAD_PORT GPIOB

// Rows
#define R0 GPIO_PIN0
#define R1 GPIO_PIN1
#define R2 GPIO_PIN3
#define R3 GPIO_PIN4

// Columns
#define C0 GPIO_PIN5
#define C1 GPIO_PIN6
#define C2 GPIO_PIN7
#define C3 GPIO_PIN8

void    Keypad_Init();
uint8_t GetData_FromKeyPad();

#endif /* KEYPAD_H_ */
