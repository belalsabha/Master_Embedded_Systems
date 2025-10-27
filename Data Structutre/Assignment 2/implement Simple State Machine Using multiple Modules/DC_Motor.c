/*
 * DC_Motor.c
 *
 *  Created on: Oct 11 , 2025
 *      Author: Eng - Belal
 */


#include"DC_Motor.h"

static unsigned int Speed = 0 ;

extern void (*Ptr_TO_DC_State)();

void DC_Init(){

		printf("\nInit DC_Motor done \n");

}

void DC_Motor(int s){
	Speed=s;
	Ptr_TO_DC_State=DC_On;
	printf("\nCA->                     DC\n");

}

void DC_Off(){
	Motor_STATE=Motor_Off;
	Ptr_TO_DC_State=Motor_Off;
	printf("\nDC OFF Speed %d \n",Speed);
}

void DC_On(){
	Motor_STATE=Motor_On;
	Ptr_TO_DC_State=DC_Off;
	printf("\nDC On Speed %d \n",Speed);
}







