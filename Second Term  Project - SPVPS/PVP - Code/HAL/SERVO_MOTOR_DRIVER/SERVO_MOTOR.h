/*
 * SERVO_MOTOR.h
 *
 *  Created on: Jan 22, 2026
 *  Developer & Tester : Eng - Belal Hani Sabha
 */

#ifndef HAL_SERVO_MOTOR_DRIVER_SERVO_MOTOR_H_
#define HAL_SERVO_MOTOR_DRIVER_SERVO_MOTOR_H_



#include "GPIO.h"
#include "stm32f103x6.h"
#include "TIMER2.h"


//Direction of motion
#define UP   1
#define Down 2


void Servo1_Entry_Gate_Init(void);
void Servo1_Entry_Gate(uint8_t Direction);

void Servo2_Exit_Gate_Init(void);
void Servo2_Exit_Gate(uint8_t Direction);



#endif /* HAL_SERVO_MOTOR_DRIVER_SERVO_MOTOR_H_ */
