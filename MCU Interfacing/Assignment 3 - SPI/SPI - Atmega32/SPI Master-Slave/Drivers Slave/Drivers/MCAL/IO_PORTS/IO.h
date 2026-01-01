/*
 * IO.h
 * Created on: Dec 14, 2025
 * Author: Belal Hani Sabha
 */

#ifndef IO_H_
#define IO_H_


//----------------------------------
//Includes
//----------------------------------
#include "PLATFORM_TYPES.h"
#include "Atmega32.h"

//----------------------------------
//User type definitions (structures)
//----------------------------------
typedef struct {
    uint8_t IO_Pin_Number;  //  Configure Pin number , must be set based on  @ref IO_PINS_define
    uint8_t IO_Mode;        // Select Mode (input/output)  for selected pin , can be a value of @ref IO_MODE_define
} IO_Configure_Pin_t;




//----------------------------------
//Macros Configuration References
//----------------------------------
/* @ref Module REF NAME define */



/******* @ref IO_PINS_define *******/
#define IO_PIN0    ((uint8_t)0x01)
#define IO_PIN1    ((uint8_t)0x02)
#define IO_PIN2    ((uint8_t)0x04)
#define IO_PIN3    ((uint8_t)0x08)
#define IO_PIN4    ((uint8_t)0x10)
#define IO_PIN5    ((uint8_t)0x20)
#define IO_PIN6    ((uint8_t)0x40)
#define IO_PIN7    ((uint8_t)0x80)


/******* @ref IO_MODE_define *******/
#define input_without_pull_up	 0
#define input_with_pull_up		 1
#define output_Low				 2
#define output_Hight			 3


/******* @ref IO_PIN_state *******/
#define SET_PIN    1
#define RESET_PIN  0

//-----------------------------------------------------






//----------------------------------
// APIs
//----------------------------------
void MCAL_IO_Init(IOx_t *IOx, IO_Configure_Pin_t* PinNumber_Configuration);
void MCAL_IO_DeInit(IOx_t *IOx);
uint8_t MCAL_IO_ReadPin(IOx_t *IOx, uint8_t PinNumber);
uint8_t MCAL_IO_ReadPort(IOx_t *IOx);
void MCAL_IO_WritePin(IOx_t *IOx, uint8_t PinNumber, uint8_t Value);
void MCAL_IO_WritePort(IOx_t *IOx , uint8_t Value);
void MCAL_IO_TogglePin(IOx_t *IOx , uint8_t PinNumber);
//----------------------------------

#endif /* IO_H_ */
