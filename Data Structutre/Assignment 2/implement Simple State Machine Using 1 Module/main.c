/*
 * main.c
 *
 *  Created on: Oct 10 , 2025
 *      Author: Eng - Belal
 */

#include"AC.h"
void setup(){
	Ptr_TO_STATEfunc = ST_Waiting ;
}
void main(){

	setup();
	while(1){
		Ptr_TO_STATEfunc();
        volatile int delay;
        for (delay = 0; delay < 1000000; delay++);


	}
}
