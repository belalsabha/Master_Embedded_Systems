/*
 * Scheduler.h
 *
 *  Created on: Aug 15, 2026
 *      Author: Eng - Belal Hani Sabha
 */
#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include "CortexMX_OS_porting.h"
//------------------------------------------------------------------------------
// RTOS Error States
//------------------------------------------------------------------------------
typedef enum {
    No_Error,   				  // Operation completed successfully
    Ready_Queue_Init_Error ,      // Operation failed
	Task_Exceeded_PSP_Stack_Error,
	Max_Tasks_Reached_Error,       // NEW: OS_Tasks[] array is full (100 tasks max)
	Ready_Queue_Full_Error,         // NEW: Ready_FIFO could not accept the task
	Mutex_Is_Reached_Max_Number_Of_Users
} MyRTOS_Error_t;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// *************************************************************************TASKS Structure*************************************************************************
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Task States and Blocking Enums
//------------------------------------------------------------------------------
typedef enum {
    Suspend,    // Task is suspended and not eligible for scheduling
    Wait,       // Task is blocked waiting for a delay/event/timeout to finish
    Ready,      // Task is ready to run and waiting for the CPU
    Run         // Task is currently running on the CPU
} Task_State_t;
typedef enum {
    Disable,    // Blocking is disabled
    Enable      // Blocking is enabled
} Blocking_State_t;
//------------------------------------------------------------------------------
// Task Structure
//------------------------------------------------------------------------------
typedef struct {
    uint32_t     Stack_Size;             // Stack size allocated for this task
    uint8_t      Priority;               // Task priority level
    void         (*Ptr_To_Task)(void);   // Pointer to the tasks entry function
    uint8_t      Auto_Start;             // 1 : task starts automatically at scheduler init , 0 : manual start
    uint32_t     PSP_Start_Addr;       // Start address of the task stack
    uint32_t     PSP_End_Addr;         // End address of the task stack
    uint32_t     *Current_PSP;           // FIX: must be a pointer (it is dereferenced everywhere
                                          // in PendSV_Handler / context switching code).
                                          // Previously declared as plain uint32_t, which made
                                          // every *(Current_PSP) dereference invalid.
    uint8_t     Task_Name[20];          // Task name string , useful for debugging
    Task_State_t Task_Status;            // Current state of the task : Suspend, Wait, Ready, Run
    struct {
        Blocking_State_t Blocking;       // Indicates if the task is currently blocked
        uint32_t          Ticks_Count;   // Remaining ticks for delay or timeout expiration
    } TimingWaiting;
} Task_Reference_t;

//------------------------------------------------------------------------------
// Mutex Structure
//------------------------------------------------------------------------------
typedef struct {
    uint8_t      *Ptr_PayLoad;               // Point to Array , use to exchange Data
    uint32_t     PayLoad_Size;             // Size of PayLoad
    Task_Reference_t *Current_Task_Use_Mutex ;
    Task_Reference_t *Next_Task_Use_Mutex ;
    uint8_t       Mutex_Name[20];
} Mutex_Reference_t;
//------------------------------------------------------------------------------
// APIs
//------------------------------------------------------------------------------
MyRTOS_Error_t MyRTOS_Init(void);
MyRTOS_Error_t MyRTOS_Create_Task(Task_Reference_t *T_REF);
void MyRTOS_ActivateTask (Task_Reference_t *T_REF);
void MyRTOS_TerminateTask (Task_Reference_t *T_REF);
void MyRTOS_Start_OS(void);
void Decide_What_Next(void);   // needed by SysTick_Handler in CortexMX_OS_porting.c
void MyRTOS_TimeWaitTask(uint32_t Ticks,Task_Reference_t *T_REF);
MyRTOS_Error_t MyRTOS_AcquireMutex(Mutex_Reference_t *M_REF,Task_Reference_t *T_REF);
void MyRTOS_ReleaseMutex(Mutex_Reference_t *M_REF);

#endif /* INC_SCHEDULER_H_ */
