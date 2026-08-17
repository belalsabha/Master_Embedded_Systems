/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Eng - Belal Hani Sabha
 * @brief          : Main program body
 ******************************************************************************
 */
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
//----------------------------------
//Includes
//----------------------------------
#include"Scheduler.h"
#include "core_cm3.h"
#include <string.h>
//----------------------------------
//Main
//----------------------------------
Task_Reference_t T1 , T2 , T3 , T4;
uint8_t T1_LED , T2_LED , T3_LED , T4_LED , Payload1[3] = {1,2,3} , Payload2[3] = {4,5,6};
Mutex_Reference_t Mutex1 ,  Mutex2;
MyRTOS_Error_t error = No_Error;

void task_1(void){
	static uint8_t Counter = 0 ;
	while(1){
		T1_LED ^= 1 ;
		Counter++;
		if(Counter == 100){
			error += MyRTOS_AcquireMutex(&Mutex1,&T1);
			MyRTOS_ActivateTask(&T4);
			error += MyRTOS_AcquireMutex(&Mutex2,&T1);

		}if (Counter == 200) {
			Counter = 0 ;
			MyRTOS_ReleaseMutex(&Mutex1);
		}
	}
}
void task_2(void){
	static uint8_t Counter = 0 ;
	while(1){
		T2_LED ^= 1 ;
		Counter++;
		if(Counter == 100){
			MyRTOS_ActivateTask(&T3);
		}
		if(Counter == 200){
			Counter = 0 ;
			MyRTOS_TerminateTask(&T2);
		}
	}
}
void task_3(void){
	static uint8_t Counter = 0 ;
	while(1){
		T3_LED ^= 1 ;
		Counter++;
		if(Counter == 100){
			MyRTOS_ActivateTask(&T4);
		}if(Counter == 200){
			MyRTOS_TerminateTask(&T3);
		}

	}
}
void task_4(void){
	static uint8_t Counter = 0 ;
	while(1){
		T4_LED ^= 1 ;
		Counter++;
		if (Counter == 3) {

			error += MyRTOS_AcquireMutex(&Mutex2,&T4);
			error += MyRTOS_AcquireMutex(&Mutex1,&T4);
		}
		if(Counter == 200){
			Counter = 0 ;
			MyRTOS_ReleaseMutex(&Mutex1);
			MyRTOS_TerminateTask(&T4);
		}
	}
}

int main(void)
{
	Mutex1.Ptr_PayLoad = Payload1 ;
	Mutex1.PayLoad_Size= 3 ;
	strcpy((char*)Mutex1.Mutex_Name,"mutex1_t1_t4");

	Mutex2.Ptr_PayLoad = Payload2 ;
	Mutex2.PayLoad_Size= 3 ;
	strcpy((char*)Mutex2.Mutex_Name,"mutex2_t4_t1");

	HardWare_Init();
	if(MyRTOS_Init() != No_Error)
		while(1);

	T1.Stack_Size = 1024 ;
	T1.Priority = 4 ;
	T1.Ptr_To_Task = task_1;
	strcpy((char*)T1.Task_Name,"task_1");

	T2.Stack_Size = 1024 ;
	T2.Priority = 3 ;
	T2.Ptr_To_Task = task_2;
	strcpy((char*)T2.Task_Name,"task_2");

	T3.Stack_Size = 1024 ;
	T3.Priority = 2 ;
	T3.Ptr_To_Task = task_3;
	strcpy((char*)T3.Task_Name,"task_3");

	T4.Stack_Size = 1024 ;
	T4.Priority = 1 ;
	T4.Ptr_To_Task = task_4;
	strcpy((char*)T4.Task_Name,"task_4");

	error+=MyRTOS_Create_Task(&T1);
	error+=MyRTOS_Create_Task(&T2);
	error+=MyRTOS_Create_Task(&T3);
	error+=MyRTOS_Create_Task(&T4);

	MyRTOS_ActivateTask(&T1);

	MyRTOS_Start_OS();

	while(1);
}
