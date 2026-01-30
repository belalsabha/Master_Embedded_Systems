/*
 * main.c
 *
 *  Created on: Jan 28, 2026
 *  Developer & Tester : Eng - Belal Hani Sabha
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "App.h"
int main(void)
{
	APP_Init();

    while(1)
    {
    	APP_Start();
    }
}




