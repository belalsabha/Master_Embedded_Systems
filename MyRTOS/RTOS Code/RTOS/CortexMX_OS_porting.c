/*
 * CortexMX_OS_porting.c
 *
 *  Created on: Aug 15, 2026
 *      Author: Eng - Belal Hani Sabha
 */

#include "CortexMX_OS_porting.h"
uint8_t SysTick_LED = 0 ;
void HardFault_Handler(void){
	while(1);
}
void MemManage_Handler(void){
	while(1);
}
void BusFault_Handler(void){
	while(1);
}
void UsageFault_Handler(void){
	while(1);
}

__attribute__((naked)) void SVC_Handler()  //__attribute ((naked)) means that this function in Assembly , compiler don't add anything
{
__asm("TST LR,#4 \n\t"  		 //is bit *no.3 in LR Equal 1
		"ITE EQ \n\t "  		 // IF They are equal
		"MRSEQ R0,MSP \n\t"  	 // Put MSP in R0
		"MRSNE R0,PSP \n\t"		 // not equal Put PSP in R0
		"B OS_SVC_Services_C"
	);
}


void HardWare_Init(){
	// Initialize ClockTree (RCC -> SysTick Timer & CPU ) by Default RCC  = 8MHz , HardWare
	// F = 8MHz
	// One Count = 0.125 US
	// We need the time between two Interrupt = 1ms , so We need 8000 Count

	// Change Priority of PendSV to make it less than Priority or SySTick = 14
	__NVIC_SetPriority(PendSV_IRQn,15);


}
void OS_SET_PendSV(void){
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;
}
void Start_Ticker(void){
   // The Clock Must be definer in HardWare_Init()
   //  clock = 8Hz
   // One Count = 0.125 US
   // We need the time between two Interrupt = 1ms , so We need 8000 Count
   SysTick_Config(8000);
}

void SysTick_Handler(){
	SysTick_LED ^= 1 ;
	Update_Task_WaitingTime();
	Decide_What_Next();
	OS_SET_PendSV();

}


