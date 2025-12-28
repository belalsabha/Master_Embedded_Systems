/*
 * App.h
 *
 *
 *  Created on: Dec 25, 2025
 *      Author:  Belal Hani Sabha
 */

#ifndef APP_H_
#define APP_H_

//----------------------------------
//Includes
//----------------------------------

#include "stm32f103x6.h"
#include "GPIO.h"
#include "EXTI.h"
#include "Lcd.h"
#include "KeyPad.h"
#include "Seven_Segment.h"
#include "RCC.h"
#include "USART.h"


/*
 * =======================================================================================
 * 										APIs
 * =======================================================================================
 */
 //************************************************************************

void APP_Init(void);

void APP_Start(void);




#endif /* APP_H_ */
