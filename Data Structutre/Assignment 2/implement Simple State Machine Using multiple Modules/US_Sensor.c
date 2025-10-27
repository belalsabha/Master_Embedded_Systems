/*
 * US_Sensor.c
 *
 * Created on: Oct 11 , 2025
 *      Author: Eng - Belal
 */



#include"US_Sensor.h"

unsigned int Distance= 0 ;
extern void (*Ptr_TO_US_State)();

void US_Init(){
	printf("\nInit US_Sensor done \n");
}

void US_Read_Distance(){
	US_STATE=US_Is_Reading_Distance;
	Distance=generate_random_Distance(45,55,1);

	printf("\nUS_Read_Distance:distance %d\n",Distance);

	US_Set_Speed(Distance);
	Ptr_TO_US_State = US_Read_Distance;
}



int generate_random_Distance(int l,int r,int count){
	int i, random_number;
	for(i=0;i<count;i++)
		random_number =(rand()%(r-l+1))+l;
	return random_number;

}



