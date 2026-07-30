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
#include "core_cm3.h"

//----------------------------------
//Global Varibles
//----------------------------------
uint32_t IRQ_Flag ;


//----------------------------------***************************************************************************************//////////////////////////////////////

/*---------------------------------- SVC & PendSV LAB ----------------------------------*/
//--------------------------------------------------------------------
//LAB 2 : PendSV
//--------------------------------------------------------------------
/*
 * PendSV Flow:
 * Main -> SVC -> PendSV -> Main
 *
 * PENDSVSET (Bit 28):
 *   Write 1: Set PendSV pending.
 *   Write 0: No effect.
 *   Read 1 : PendSV is pending.
 *   Read 0 : PendSV is not pending.
 *
 * PENDSVCLR (Bit 27):
 *   Write 1: Clear PendSV pending.
 *   Write 0: No effect.
 */
void PendSV_Handler(){
	//Clear PendSV
	// SCB->ICSR |= SCB_ICSR_PENDSVCLR_Msk ;
}
//--------------------------------------------------------------------
//LAB 1 : SVC Service that Passes Parameters and Returns a Value
//--------------------------------------------------------------------
void OS_SVC_Services_C(uint32_t* StackFramePointer){ //StackFramePointer = R0 = MSP = SP before go to  SVC_Handler()
	// Stack Frame Contains :
	// R0,R1,R2,R3,R12,LR,PC,xPSR
	// Stacked R0   = StackFramePointer[0]
	// Stacked R1   = StackFramePointer[1]
	// Stacked R2   = StackFramePointer[2]
	// Stacked R3   = StackFramePointer[3]
	// Stacked R12  = StackFramePointer[4]
	// Stacked LR   = StackFramePointer[5]
	// Stacked PC   = StackFramePointer[6]
	// Stacked xPSR = StackFramePointer[7]
	uint32_t SVC_Number ;
	SVC_Number = ((uint8_t*)StackFramePointer[6])[-2];//go up with 24byte=PC, take value of PC then Sub2 byte that mean we arrive to address of SVC Instruction
													  //take the first byte = SVC_Number
	// another way to find SVC_Number
	// SVC_Number = *(uint8_t*)((uint8_t*)StackFramePointer[6] - 2 ) ;
	switch(SVC_Number){
	case 0 : StackFramePointer[0] = StackFramePointer[0] + StackFramePointer[1] ;
		break ;
	case 1 : StackFramePointer[0] =   StackFramePointer[1] - StackFramePointer[0] ;
		break ;
	case 2 : StackFramePointer[0] = StackFramePointer[0] * StackFramePointer[1] ;
		break ;
	case 3 : SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;   // Trigger PendSV exception
	default : // SVC Request Unknown
		break ;
	}
	return ;
}
__attribute ((naked)) void SVC_Handler()  //__attribute ((naked)) means that this function in Assembly , compiler don't add anything
{
__asm("TST LR,#4 \n\t"  		 //is bit *no.3 in LR Equal 1
		"ITE EQ \n\t "  		 // IF They are equal
		"MRSEQ R0,MSP \n\t"  	 // Put MSP in R0
		"MRSNE R0,PSP \n\t"		 // not equal Put PSP in R0
		"B OS_SVC_Services_C"
	);
}
uint32_t OS_SVC_SET(uint32_t NUM1 , uint32_t NUM2 , uint32_t SVC_ID){
	uint32_t Result ;
	switch(SVC_ID){
	case 0 : __asm("SVC #0x00"); // ADD
		break;
	case 1 : __asm("SVC #0x01"); // SUB
		break;
	case 2 : __asm("SVC #0x02"); // MUL
		break;
	case 3 : __asm("SVC #0x03"); // PendSV
	}
	__asm("MOV %0 , R0 " : "=r"(Result));
	return Result ;
}
//----------------------------------
//Main
//----------------------------------
int main(void)
{
	IRQ_Flag=OS_SVC_SET( 1 ,2 , 0); //ADD
	IRQ_Flag=OS_SVC_SET( 1 ,2 , 1); //SUB
	IRQ_Flag=OS_SVC_SET( 1 ,2 , 2); //MUL
	IRQ_Flag=OS_SVC_SET( 0 ,0 , 3); //PendSV

	while(1);
}
