/*
 * main.c
 *
 *  Created on: Oct 11 , 2025
 *      Author: Eng - Belal
 */

#include"DC_Motor.h"
#include"US_Sensor.h"
void setup(){
	void US_Init();
	void DC_Init();
	Ptr_TO_STATEfunc = ST_Waiting ;
	Ptr_TO_DC_State=DC_Off;
	Ptr_TO_US_State=US_Read_Distance;
}
void main(){

	setup();
	while(1){
		Ptr_TO_US_State();
		Ptr_TO_STATEfunc();
		Ptr_TO_DC_State();

        volatile int delay;
        for (delay = 0; delay < 1000000; delay++);


	}
}
