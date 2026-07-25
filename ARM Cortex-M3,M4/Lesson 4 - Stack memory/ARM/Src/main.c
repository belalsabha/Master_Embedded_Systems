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

#include "App.h"
//----------------------------------
//OS Macros
//----------------------------------
#define OS_SET_PSP(add)        __asm volatile ("mov r0,%0 \n\t msr PSP,r0 \n\t" : : "r" (add))
#define OS_SWITCH_SP_TO_MSP    __asm volatile ("mrs r0,CONTROL \n\t mov r1,#0x5 \n\t and r0,r0,r1 \n\t msr CONTROL,r0 \n\t")
#define OS_SWITCH_SP_TO_PSP    __asm volatile ("mrs r0,CONTROL \n\t orr r0,r0,#0x2 \n\t msr CONTROL,r0 \n\t" )
#define OS_GEN_SWI             __asm volatile ("SVC #0x3")

#define TaskA_Stack_Size 100
#define TaskB_Stack_Size 100

//----------------------------------
//Global Varibles - use them in functions
//----------------------------------
volatile uint8_t IRQ_Flag = 0 , TaskA_Flag=0 , TaskB_Flag=0 , SumA , SumB ;
extern uint32_t _estack;
//Main Stack (MS)
uint32_t _S_MSP = (uint32_t)&_estack ;
uint32_t _E_MSP ;
//Process Stack (PS)
//Task_A
uint32_t _S_PSP_TaskA  ;
uint32_t _E_PSP_TaskA  ;
//Task_B
uint32_t _S_PSP_TaskB  ;
uint32_t _E_PSP_TaskB  ;
//----------------------------------
//Switch Access Level
//----------------------------------
#define Privileged_CPU_AccessLeval	    __asm volatile("mrs r0, control\n\t""bic r0, r0,#1\n\t""msr control, r0\n\t" )
#define Unprivileged_CPU_AccessLeval    __asm volatile("mrs r0, control\n\t""orr r0, r0,#1\n\t" "msr control	, r0\n\t")
#define No_Operation				    __asm volatile("nop\n\t nop\n\t nop\n\t")


//----------------------------------
//TASKs
//----------------------------------
uint32_t TaskA(uint32_t a , uint32_t b , uint32_t c){
	return a+b+c   ;
}
uint32_t TaskB(uint32_t a , uint32_t b , uint32_t c , uint32_t d){
	return a+b+c+d ;
}

//----------------------------------
//Main OS
//----------------------------------
void MainOS(){
	// main stack
	_E_MSP = (_S_MSP - 512) ;
	//proceess stack
	//task A
	_S_PSP_TaskA = ( _E_MSP - 8 );
	_E_PSP_TaskA = (_S_PSP_TaskA - TaskA_Stack_Size);
	//task B
	_S_PSP_TaskB = ( _E_PSP_TaskA - 8 );
	_E_PSP_TaskB = (_S_PSP_TaskB - TaskB_Stack_Size);
	while(1){
		if(TaskA_Flag == 1 ){
			// Set PSP Register = _S_PSP_TA
			OS_SET_PSP(_S_PSP_TaskA);
			// SP -> PSP
			OS_SWITCH_SP_TO_PSP;
			// Switch from Privileged to UnPrivileged
			Unprivileged_CPU_AccessLeval;
			SumA = TaskA(1,2,3);
			// Switch from Unprivileged to Privileged
			OS_GEN_SWI;
			// SP -> MSP
			OS_SWITCH_SP_TO_MSP;
			TaskA_Flag = 0;
		}else if(TaskB_Flag == 1 ){
			// Set PSP Register = _S_PSP_TB
			OS_SET_PSP(_S_PSP_TaskB);
			// SP -> PSP
			OS_SWITCH_SP_TO_PSP;
			// Switch from Privileged to Unprivileged
			Unprivileged_CPU_AccessLeval;
			SumB = TaskB(1,2,3,4);
			// Switch from UnPrivileged to Privileged
			OS_GEN_SWI;
			// SP -> MSP
			OS_SWITCH_SP_TO_MSP;
			TaskB_Flag = 0;
		}
	}
}
//----------------------------------
//ISRs
//----------------------------------
void SVC_Handler()
{
	Privileged_CPU_AccessLeval;
}
void IRQ9_Callback()
{
	if(IRQ_Flag == 0){
		TaskA_Flag = 1 ;
		IRQ_Flag = 1 ;
	}else if(IRQ_Flag == 1){
		TaskB_Flag = 1 ;
		IRQ_Flag = 0 ;
	}
}
//----------------------------------
//Main
//----------------------------------
int main(void)
{
	// enable clocks for GPIOA GPIOB AFIO
	RCC_AFIO_CLK_EN();
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	EXTI_Configure_Pin_t EXTIx;
	EXTIx.EXTI_PIN = EXTI9PB9;
	EXTIx.EDGE_CASE = RISING_EDGE;
	EXTIx.IRQ_E_D = ENABLE_IRQ_EXTI;
	EXTIx.P_IRQ_FUNC_CALLBACK = &IRQ9_Callback;
	MCAL_EXTI_GPIO_Init(&EXTIx);
	MainOS();
	while(1);
}
