/*
 * Action_Controller.c
 *
 *  Created on: 31 Oct 2025
 *      Author: Belal
 */

#include "Action_Controller.h"
#include "Pressure_Sensor_Driver.h"
#include "Alarm_Actuator_Driver.h"


static const unsigned int Threshold = 20;

void (*Ptr_TO_StateFunction)();


void PSensor_detect_pressure(){

	if(Pressure < Threshold )
		Alarm_Off();
	else
		Alarm_On();

}








