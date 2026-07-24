/*
 * RCC.h
 *
 *
 *  Created on: Dec 24, 2025
 *      Author:  Belal Hani Sabha
 */

#ifndef RCC_DRIVER_RCC_H_
#define RCC_DRIVER_RCC_H_

//----------------------------------
//Includes
//----------------------------------
#include "stm32f103x6.h"

#include "GPIO.h"


//Macros
#define HSI_System_Clock	(uint32_t)8000000	//8 mega
#define HSE_System_Clock	(uint32_t)16000000  //16 mega
#define PLL_System_Clock	(uint32_t)16000000	//16 mega



/*
 * =======================================================================================
 * 							APIs Supported by "MCAL RCC DRIVER"
 * =======================================================================================
 */

uint32_t MCAL_RCC_GetSystem_ClckFreqency(void)  ;
uint32_t MCAL_RCC_Get_HClckFreqency(void)	 	;
uint32_t MCAL_RCC_Get_PCLK1Freqency(void) 		;
uint32_t MCAL_RCC_Get_PCLK2Freqency(void) 		;

#endif /* RCC_DRIVER_RCC_H_ */
