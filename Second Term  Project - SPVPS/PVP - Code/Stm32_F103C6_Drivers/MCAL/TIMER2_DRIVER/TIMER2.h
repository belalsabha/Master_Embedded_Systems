/*
 * TIMER.h
 *
 *  Created on: Jan 22, 2026
 *  Developer & Tester : Eng - Belal Hani Sabha
 */

#ifndef MCAL_TIMER2_DRIVER_TIMER2_H_
#define MCAL_TIMER2_DRIVER_TIMER2_H_



#include "GPIO.h"
#include "stm32f103x6.h"



/*
 * =======================================================================================
 * 							APIs Supported by "MCAL TIMER2 DRIVER"
 * =======================================================================================
 */
void Timer2_init(void);
void dus(int us);
void dms(int ms);


#endif /* MCAL_TIMER2_DRIVER_TIMER2_H_ */
