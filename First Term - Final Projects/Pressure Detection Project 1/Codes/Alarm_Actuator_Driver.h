/*
 * Alarm_Actuator_Driver.h
 *
 *  Created on: 31 Oct 2025
 *      Author: Belal
 */

#ifndef ALARM_ACTUATOR_DRIVER_H_
#define ALARM_ACTUATOR_DRIVER_H_

#include "driver.h"
void Alarm_Off();
void Alarm_On();
void Init_Alarm_Actuator();
extern void (*Ptr_TO_Alarm_State);


#endif /* ALARM_ACTUATOR_DRIVER_H_ */


