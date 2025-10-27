/*
 * AC.h
 *
 *  Created on: Oct 11 , 2025
 *      Author: Eng - Belal
 */


#ifndef AC_H_
#define AC_H_


#include<stdio.h>
#include<stdlib.h>

void (*Ptr_TO_STATEfunc)();
void ST_Waiting();
void ST_Driving();
void US_Set_Speed(int d);

enum{
	waiting,
	driving
}STATE;




#endif /* AC_H_ */
