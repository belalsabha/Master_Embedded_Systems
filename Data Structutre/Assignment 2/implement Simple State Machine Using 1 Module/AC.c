/*
 * AC.c
 *
 *  Created on: Oct 10 , 2025
 *      Author: Eng - Belal
 */

#include"AC.h"

static unsigned int Distance= 0 ,Speed = 0 , Threshold = 50 ;

 void (*Ptr_TO_STATEfunc)();


void ST_Waiting(){
	STATE=waiting;
	Speed =0;
	Distance=generate_random_Distance(45,55,1);
	if(Distance < Threshold )
		Ptr_TO_STATEfunc = ST_Waiting ;
	else
		Ptr_TO_STATEfunc = ST_Driving ;


	printf("\nwaiting state : speed %d distance %d \n",Speed,Distance);
}

void ST_Driving(){
	STATE=driving;
	Speed =30;
	Distance=generate_random_Distance(45,55,1);
	if(Distance < Threshold )
		Ptr_TO_STATEfunc = ST_Waiting;
	else
		Ptr_TO_STATEfunc = ST_Driving ;


	printf("\ndriving state : speed %d distance %d\n",Speed,Distance);
}



int generate_random_Distance(int l,int r,int count){
	int i, random_number;
	for(i=0;i<count;i++)
		random_number =(rand()%(r-l+1))+l;
	return random_number;

}
