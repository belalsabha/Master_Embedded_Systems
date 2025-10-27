/*
 * DC_Motor.h
 *
 *  Created on: Oct 11 , 2025
 *      Author: Eng - Belal
 */


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


#include"AC.h"


void DC_Off();
void DC_On();
void DC_Init();
void DC_Motor(int s);
void (*Ptr_TO_DC_State)();

enum{
	Motor_Off,
	Motor_On
}Motor_STATE;


#endif /* DC_MOTOR_H_ */

/* DC_MOTOR_H_ */
