/*
 * IO.h
 * Created on: Dec 14, 2025
 * Author: Belal Hani Sabha
 */

#ifndef IO_H_
#define IO_H_

#include <stdint.h>
#include "Atmega32.h"

//----------------------------------
// User type definitions
//----------------------------------
typedef struct {
    uint8_t IO_Pin_Number;  // Pin number
    uint8_t IO_Mode;        // Mode (input/output)
} IO_Configure_Pin_t;

//----------------------------------
// Macros
//----------------------------------
#define SET_PIN    1
#define RESET_PIN  0

#define IO_PIN0    ((uint8_t)0x01)
#define IO_PIN1    ((uint8_t)0x02)
#define IO_PIN2    ((uint8_t)0x04)
#define IO_PIN3    ((uint8_t)0x08)
#define IO_PIN4    ((uint8_t)0x10)
#define IO_PIN5    ((uint8_t)0x20)
#define IO_PIN6    ((uint8_t)0x40)
#define IO_PIN7    ((uint8_t)0x80)

#define input_without_pull_up	0
#define input_with_pull_up		1
#define output_Low				2
#define output_Hight			 3

#define PULL_UP_DISABLE()      (SFIOR |= (1<<2))
#define PULL_UP_ENABLE()       (SFIOR &= ~(1<<2))

//----------------------------------
// APIs
//----------------------------------
void MCAL_IO_Init(IOx_t *IOx, IO_Configure_Pin_t* PinNumber_Configuration);
void MCAL_IO_DeInit(IOx_t *IOx);
uint8_t MCAL_IO_ReadPin(IOx_t *IOx, uint8_t PinNumber);
uint8_t MCAL_IO_ReadPort(IOx_t *IOx);
void MCAL_GPIO_WritePin(IOx_t *IOx, uint8_t PinNumber, uint8_t Value);

#endif /* IO_H_ */
