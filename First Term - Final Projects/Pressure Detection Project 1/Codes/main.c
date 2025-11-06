/*
 * main.c
 *
 *  Created on: 31 Oct 2025
 *      Author: Belal
 */


#include <stdint.h>
#include <stdio.h>

#include "driver.h"
#include "Pressure_Sensor_Driver.h"
#include "Action_Controller.h"
#include "Alarm_Actuator_Driver.h"


void setup(){
	Ptr_TO_StateFunction=PSensor_detect_pressure;
    Ptr_TO_PSensor_State=PSensor_Read_Pressure;
	GPIO_INITIALIZATION();

}

int main (){
	setup();
	while (1)
	{
		Ptr_TO_PSensor_State();
		Ptr_TO_StateFunction();



	}

}



