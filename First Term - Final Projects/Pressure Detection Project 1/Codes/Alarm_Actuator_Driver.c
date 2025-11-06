/*
 * Alarm_Actuator_Driver.c
 *
 *  Created on: 31 Oct 2025
 *      Author: Belal
 */
#include "Alarm_Actuator_Driver.h"
#include "driver.h"
unsigned int time=600000; 

void Alarm_Off(){
	Set_Alarm_actuator(1);
}
void Alarm_On(){
	Set_Alarm_actuator(0);
	Delay(time);
	Alarm_Off();
	
}
void Init_Alarm_Actuator(){

}

