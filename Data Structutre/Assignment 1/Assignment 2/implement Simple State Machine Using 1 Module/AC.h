/*
 * AC.h
 *
 *  Created on: Oct 10 , 2025
 *      Author: Eng - Belal
 */


#ifndef AC_H_
#define AC_H_


#include<stdio.h>
#include<stdlib.h>


extern void (*Ptr_TO_STATEfunc)();
void ST_Waiting();
void ST_Driving();
int generate_random_Distance(int l,int r,int count);
enum{
	waiting,
	driving
}STATE;




#endif /* AC_H_ */
