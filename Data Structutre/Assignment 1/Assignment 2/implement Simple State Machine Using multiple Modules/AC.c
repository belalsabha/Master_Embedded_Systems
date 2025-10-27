/*
 * AC.c
 *
 *  Created on: Oct 11 , 2025
 *      Author: Eng - Belal
 */

#include"AC.h"

static unsigned int Distance= 0 ,Speed = 0 , Threshold = 50 ;

extern void (*Ptr_TO_STATEfunc)();

void US_Set_Speed(int d){
	Distance = d;
	if(Distance < Threshold )
		Ptr_TO_STATEfunc = ST_Waiting ;
	else
		Ptr_TO_STATEfunc = ST_Driving ;
	printf("\nUS Distance  : %d \n",Distance);

}


void ST_Waiting(){
	STATE=waiting;
	printf("\nwaiting state : speed %d distance %d \n",Speed,Distance);
	Speed =0;
	DC_Motor(Speed);

}

void ST_Driving(){
	STATE=driving;



	printf("\ndriving state : speed %d distance %d\n",Speed,Distance);
	Speed =30;
	DC_Motor(Speed);
}



