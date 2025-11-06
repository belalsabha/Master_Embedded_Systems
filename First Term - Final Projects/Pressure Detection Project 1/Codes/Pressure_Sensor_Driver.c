/*
 * Pressure_Sensor_Driver.c
 *
 *  Created on: 31 Oct 2025
 *      Author: Belal
 */




#include "Pressure_Sensor_Driver.h"
#include "driver.h"
unsigned int Pressure= 0 ;
void (*Ptr_TO_PSensor_State)();

void PSensor_Init(){
	Ptr_TO_PSensor_State=PSensor_Read_Pressure;
}
void PSensor_Read_Pressure(){
	Pressure= (unsigned int)getPressureVal();
	PSensor_waiting();
	Ptr_TO_PSensor_State=PSensor_Read_Pressure;

}

void PSensor_waiting(){
	int delay=1000;
	Delay(delay);
}




