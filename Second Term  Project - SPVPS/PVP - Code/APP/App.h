/*
 * App.h
 *
 *  Created on: Jan 28, 2026
 *  Developer & Tester : Eng - Belal Hani Sabha
 */

#ifndef APP_H_
#define APP_H_

//----------------------------------
//Includes
//----------------------------------
#include "KeyPad.h"
#include "Lcd.h"
#include "GPIO.h"
#include "stm32f103x6.h"
#include "USART.h"
#include "SERVO_MOTOR.h"
#include "TIMER2.h"


/*
 * =======================================================================================
 * 										APIs
 * =======================================================================================
 */
void APP_Init(void);
void APP_Start(void);

#endif /* APP_H_ */
