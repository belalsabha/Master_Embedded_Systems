/*
 * 			GPIO.h
 *
 *  Created on: Dec 8, 2025
 *      Author:  Belal Hani Sabha
 */


#ifndef GPIO_DRIVER_GPIO_H_
#define GPIO_DRIVER_GPIO_H_


//----------------------------------
//Includes
//----------------------------------
#include "stm32f103x6.h"



//----------------------------------
//User type definitions (structures)
//----------------------------------

typedef struct{

uint16_t  GPOI_Pin_Number	 	;   // Specifies the GPIO pins to be configured.
 	 	 	 	 	 	 	 	 	// This parameter must be set based on @ref GPIO_PINS_define

uint8_t	  GPIO_Mode		  	    ;	// Specifies the operating mode for the selected pins
									// This parameter can be a value of @ref GPIO_MODE_define

uint8_t  GPIO_Output_Frequency	;	// Specifies the speed for the selected pins
									// This parameter can be a value of @ref GPIO_SPEED_define

}GPIO_Configure_Pin_t;


//@ref GPIO_PIN_state
#define SET_PIN    	  1
#define RESET_PIN     0



//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_Enabled       	 1
#define GPIO_RETURN_LOCK_ERROR  		 0


//----------------------------------
//Macros Configuration References
//----------------------------------
/* @ref Module REF NAME define */


//@ref GPIO_PINS_define
#define GPIO_PIN0       ((uint16_t)0x0001)   // Pin 0   = 0000 0000 0000 0001
#define GPIO_PIN1       ((uint16_t)0x0002)   // Pin 1   = 0000 0000 0000 0010
#define GPIO_PIN2       ((uint16_t)0x0004)   // Pin 2   = 0000 0000 0000 0100
#define GPIO_PIN3       ((uint16_t)0x0008)   // Pin 3   = 0000 0000 0000 1000
#define GPIO_PIN4       ((uint16_t)0x0010)   // Pin 4   = 0000 0000 0001 0000
#define GPIO_PIN5       ((uint16_t)0x0020)   // Pin 5   = 0000 0000 0010 0000
#define GPIO_PIN6       ((uint16_t)0x0040)   // Pin 6   = 0000 0000 0100 0000
#define GPIO_PIN7       ((uint16_t)0x0080)   // Pin 7   = 0000 0000 1000 0000
#define GPIO_PIN8       ((uint16_t)0x0100)   // Pin 8   = 0000 0001 0000 0000
#define GPIO_PIN9       ((uint16_t)0x0200)   // Pin 9   = 0000 0010 0000 0000
#define GPIO_PIN10      ((uint16_t)0x0400)   // Pin 10  = 0000 0100 0000 0000
#define GPIO_PIN11      ((uint16_t)0x0800)   // Pin 11  = 0000 1000 0000 0000
#define GPIO_PIN12      ((uint16_t)0x1000)   // Pin 12  = 0001 0000 0000 0000
#define GPIO_PIN13      ((uint16_t)0x2000)   // Pin 13  = 0010 0000 0000 0000
#define GPIO_PIN14      ((uint16_t)0x4000)   // Pin 14  = 0100 0000 0000 0000
#define GPIO_PIN15      ((uint16_t)0x8000)   // Pin 15  = 1000 0000 0000 0000
#define GPIO_ALL_Pins   ((uint16_t)0xFFFF)   // All Pins = 1111 1111 1111 1111


#define GPIO_PIN_MASK              0x0000FFFFu  //PIN mask for assert test

/*
In input mode (MODE[1:0]=00):
0: Analog mode
1: Floating input (reset state)
2: Input with  pull-down
3: Input with  pull-down
In output mode (MODE[1:0] > 00):
4: General purpose output push-pull
5: General purpose output Open-drain
6: Alternate function output Push-pull
7: Alternate function output Open-drain   */
//@ref GPIO_MODE_define
// 	In input mode (MODE[1:0]=00):
#define GPIO_Analog_Mode     				 		(uint8_t)0x00000000 //Analog mode
#define GPIO_Floating_Input 					 	(uint8_t)0x00000001 //Floating input (reset state)
#define GPIO_Input_pull_up 				            (uint8_t)0x00000002 //Input with pull-up
#define GPIO_Input_pull_down 						(uint8_t)0x00000003 //Input with  pull-down

//In output mode (MODE[1:0] > 00
#define output_push_pull     				 		(uint8_t)0x00000004 //General purpose output push-pull
#define output_Open_drain 					 		(uint8_t)0x00000005 //General purpose output Open-drain
#define Alternate_function_output_Push_pull  		(uint8_t)0x00000006 //Alternate function output Push-pull
#define Alternate_function_output_Open_drain  		(uint8_t)0x00000007 //Alternate function output Open-drain

#define  GPIO_Alternate_function_INPUT              (uint8_t)0x00000008 //Alternate function INPUT





//@ref GPIO_SPEED_define
/*00: Input mode (reset state)
1: Output mode, max speed 10 MHz.
2: Output mode, max speed 2 MHz.
3: Output mode, max speed 50 MHz.*/
#define Frequency_10MHz                         (uint8_t)0x00000001 //Output mode, max speed 10 MHz.
#define Frequency_2MHz                          (uint8_t)0x00000002 //Output mode, max speed 2  MHz.
#define Frequency_50MHz                         (uint8_t)0x00000003 //Output mode, max speed 50 MHz.





/*
 * =======================================================================================
 * 							APIs Supported by "MCAL GPIO DRIVER"
 * =======================================================================================
 */

// 					APIs For GPIOx
void MCAL_GPIO_Init(GPIOx_t *GPIOx , GPIO_Configure_Pin_t* PinNumber_Configuration );
void MCAL_GPIO_DeInit(GPIOx_t *GPIOx);

uint8_t  MCAL_GPIO_ReadPin(GPIOx_t *GPIOx , uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIOx_t *GPIOx);

void MCAL_GPIO_WritePin(GPIOx_t *GPIOx , uint16_t PinNumber , uint8_t Value);
void MCAL_GPIO_WritePort(GPIOx_t *GPIOx , uint16_t Value);

void MCAL_GPIO_TogglePin(GPIOx_t *GPIOx , uint16_t PinNumber);
uint8_t MCAL_GPIO_LockPin(GPIOx_t *GPIOx , uint16_t PinNumber);

//---------------------------------------------------



#endif /* GPIO_DRIVER_GPIO_H_ */
