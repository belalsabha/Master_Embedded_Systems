/*
 * Action_Controller.h
 *
 *  Created on: 31 Oct 2025
 *      Author: Belal
 */

#ifndef ACTION_CONTROLLER_H_
#define ACTION_CONTROLLER_H_
#include "Pressure_Sensor_Driver.h"
#include "Alarm_Actuator_Driver.h"
extern void (*Ptr_TO_StateFunction)();

void PSensor_detect_pressure();


#endif /* ACTION_CONTROLLER_H_ */


