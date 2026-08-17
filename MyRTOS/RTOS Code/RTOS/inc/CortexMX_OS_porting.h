/*
 * CortexMX_OS_porting.h
 *
 *  Created on: Aug 15, 2026
 *      Author: Eng - Belal Hani Sabha
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

#include"core_cm3.h"

//----------------------------------
// OS Macros
//----------------------------------
#define OS_SET_PSP(add)             __asm volatile ("mov r0, %0 \n\t msr PSP, r0 \n\t" : : "r" (add))
#define OS_GET_PSP(add)             __asm volatile ("mrs r0, PSP \n\t mov %0, r0  \n\t" : "=r" (add))
#define OS_SWITCH_SP_TO_MSP         __asm volatile ("mrs r0, CONTROL \n\t mov r1, #0x5 \n\t and r0, r0, r1 \n\t msr CONTROL, r0 \n\t")
#define OS_SWITCH_SP_TO_PSP         __asm volatile ("mrs r0, CONTROL \n\t orr r0, r0, #0x2 \n\t msr CONTROL, r0 \n\t")

//----------------------------------
// Switch Access Level
//----------------------------------
#define Privileged_CPU_AccessLevel   __asm volatile ("mrs r0, control \n\t bic r0, r0, #1 \n\t msr control, r0 \n\t")
#define Unprivileged_CPU_AccessLevel __asm volatile ("mrs r0, control \n\t orr r0, r0, #1 \n\t msr control, r0 \n\t")
#define No_Operation                 __asm volatile ("nop \n\t nop \n\t nop \n\t")

extern uint32_t _estack;
extern uint32_t _end;
extern uint32_t _Min_Heap_Size;
#define MainStack_Size 3072  	// 3Kb = 3*1024 = 3072 byte

void OS_SET_PendSV(void);
void Start_Ticker(void);
#endif /* INC_CORTEXMX_OS_PORTING_H_ */
