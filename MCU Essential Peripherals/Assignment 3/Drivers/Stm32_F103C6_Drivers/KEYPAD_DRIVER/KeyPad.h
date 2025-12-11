/*
 * keyPad.h
 *
 * Created: 13/06/47 01:36:40
 *  Author: Belal
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 8000000UL

#include "Stm32f103x6.h"
#include "Stm32F103C6_GPIO_Driver.h"

GPIO_Configure_Pin_t *Pin_Config ;

#define R0 GPIO_PIN0
#define R1 GPIO_PIN1
#define R2 GPIO_PIN2
#define R3 GPIO_PIN3
#define C0 GPIO_PIN4
#define C1 GPIO_PIN5
#define C2 GPIO_PIN6
#define C3 GPIO_PIN7

#define KEYPAD_PORT GPIOB

void Keypad_Init();
uint8_t GetData_FromKeyPad();

#endif /* KEYPAD_H_ */
