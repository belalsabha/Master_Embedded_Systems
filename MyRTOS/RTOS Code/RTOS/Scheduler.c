/*
 * Scheduler.c
 *
 *  Created on: Aug 15, 2026
 *      Author: Eng - Belal Hani Sabha
 */

#include "Scheduler.h"
#include "MyRTOS_FIFO.h"
#include <string.h>


//------------------------------------------------------------------------------
// OS Control Structure
//------------------------------------------------------------------------------
typedef enum {
	OS_Suspend,   // Scheduler/OS is suspended, no task switching occurs
	OS_Run        // Scheduler/OS is running normally
}OS_Mode_t;

typedef struct {
	Task_Reference_t *OS_Tasks[100];     // Array of pointers to manage all created tasks
	Task_Reference_t *Current_Task;      // Pointer to the currently running task
	Task_Reference_t *Next_Task;         // Pointer to the next task to be scheduled

	uint32_t   S_MSP_Task;               // Start address of the Main Stack Pointer
	uint32_t   E_MSP_Task;               // End address of the Main Stack Pointer
	uint32_t   PSP_Task_Locator;         // Locator used to track task stack memory allocations
	uint32_t   Number_of_Active_Task;    // Total number of currently created tasks
	OS_Mode_t  OS_ID_Mode;               // Current operating mode of the RTOS
	uint8_t    Ready_Group_Priority;     // priority of the task group currently sitting
	// in Ready_FIFO (Ready_FIFO always holds a single,
	// highest-eligible priority group by construction).
	// Needed so Decide_What_Next() can tell whether the
	// Current_Task is actually part of that group.
} OS_Control_t;

typedef enum {
	SVC_ACTIVATE_TASK,
	SVC_TERMINATE_TASK,
	SVC_TASK_WAITNG_TIME,
	SVC_AquireMutex,
	SVC_ReleaseMutex
}SVC_ID;

//------------------------------------------------------------------------------
// Global OS Control Instance
//------------------------------------------------------------------------------
static OS_Control_t 	   OS_Ctrl;   					// The single instance holding the OS scheduler state
static FIFO_BUF_t          Ready_FIFO;					// Ready Queue control structure
static Task_Reference_t   *Ready_Queue_Buf[100];		// storage array for the Ready Queue
static Task_Reference_t	   MyRTOS_IDLE_Task ;
uint8_t	   IDLE_LED ;


__attribute ((naked)) void PendSV_Handler(){

	//====================================
	//Save the Context of the Current Task
	//====================================
	//Get the Current Task "Current PSP from CPU register" as CPU Push XPSR,.....,R0
	OS_GET_PSP(OS_Ctrl.Current_Task->Current_PSP);

	// Use Current PSP  to Store R4 -> R11
	OS_Ctrl.Current_Task->Current_PSP--;
	__asm("mov %0 , R4" : "=r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP--;
	__asm("mov %0 , R5" : "=r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP--;
	__asm("mov %0 , R6" : "=r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP--;
	__asm("mov %0 , R7" : "=r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP--;
	__asm("mov %0 , R8" : "=r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP--;
	__asm("mov %0 , R9" : "=r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP--;
	__asm("mov %0 , R10" : "=r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP--;
	__asm("mov %0 , R11" : "=r" (*(OS_Ctrl.Current_Task->Current_PSP)));

	//====================================
	// FIX: switch the "Current Task" pointer to "Next Task" BEFORE restoring
	// context. Without this line the OS kept saving/restoring the SAME task
	// forever and no real task switching ever happened.
	//====================================
	OS_Ctrl.Current_Task = OS_Ctrl.Next_Task;

	//====================================
	//Restore the Context of the Next Task
	// FIX: removed the stray closing brace "}" that was here before, which
	// terminated the function early and made all the restore code below
	// (and the whole context switch) unreachable / a compile error.
	//====================================
	__asm("mov R11 , %0" : :"r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP++;
	__asm("mov R10 , %0" : :"r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP++;
	__asm("mov R9 , %0" : :"r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP++;
	__asm("mov R8 , %0" : :"r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP++;
	__asm("mov R7 , %0" : :"r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP++;
	__asm("mov R6 , %0" : :"r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP++;
	__asm("mov R5 , %0" : :"r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP++;
	__asm("mov R4 , %0" : :"r" (*(OS_Ctrl.Current_Task->Current_PSP)));
	OS_Ctrl.Current_Task->Current_PSP++;

	// Update PSP Pointer
	OS_SET_PSP(OS_Ctrl.Current_Task->Current_PSP);
	__asm volatile("BX LR");

}




void MyRTOS_Creat_MainStack(void)
{
	OS_Ctrl.S_MSP_Task       = (uint32_t)&_estack;
	OS_Ctrl.E_MSP_Task       = OS_Ctrl.S_MSP_Task - MainStack_Size;
	OS_Ctrl.PSP_Task_Locator = OS_Ctrl.E_MSP_Task - 8;
}
void MyRTOS_idleTask(void){
	while(1){
		IDLE_LED ^=1;
		__asm("wfe");
	}
}

MyRTOS_Error_t MyRTOS_Init(void)
{
	MyRTOS_Error_t ID_error = No_Error;

	// Update OS Mode (Suspend)
	OS_Ctrl.OS_ID_Mode = OS_Suspend;

	// Specify Main Stack for OS
	MyRTOS_Creat_MainStack();
	// Create OS Ready Queue
	if(BUF_INIT(&Ready_FIFO , Ready_Queue_Buf, 100) != BUF_NO_ERROR){
		ID_error +=  Ready_Queue_Init_Error ;
	}
	// Configure IDLE Task
	strcpy((char*)MyRTOS_IDLE_Task.Task_Name,"idletask");
	MyRTOS_IDLE_Task.Priority     = 255 ;
	MyRTOS_IDLE_Task.Stack_Size   = 300 ;
	MyRTOS_IDLE_Task.Ptr_To_Task  = MyRTOS_idleTask;
	MyRTOS_IDLE_Task.Auto_Start   = 1 ;

	ID_error += MyRTOS_Create_Task(&MyRTOS_IDLE_Task);
	return ID_error;
}

void MyRTOS_Create_TaskStack(Task_Reference_t *T_REF){
	/*
	 * ============ Task Frame ============
	 * LR    -> Link Register (saved before task does context switching)
	 * PC    -> Return address (next instruction)
	 * xPSR  -> Program Status Register
	 * R12   ---------------  Auto
	 * R3    ---------------  Push
	 * R2    ---------------  to
	 * R1    ---------------  Stack
	 * R0    ---------------  By CPU
	 * ========================
	 * R4 ->>> R11 Manually pushed, popped by my context switch code
	 */
	// FIX: Current_PSP is now uint32_t* (see Scheduler.h), so the starting
	// address (a plain uint32_t) must be cast to a pointer here.
	T_REF->Current_PSP = (uint32_t*)T_REF->PSP_Start_Addr;

	T_REF->Current_PSP -= 1;
	*(T_REF->Current_PSP) = 0x01000000;              // xPSR (Thumb bit set)

	T_REF->Current_PSP -= 1;
	*(T_REF->Current_PSP) = (uint32_t)T_REF->Ptr_To_Task; // PC = task entry point

	T_REF->Current_PSP -= 1;
	*(T_REF->Current_PSP) = 0xFFFFFFFD;               // LR = EXC_RETURN (Thread mode, use PSP)

	for (uint8_t Counter = 0 ; Counter < 13 ; Counter++) {
		T_REF->Current_PSP -= 1;
		*(T_REF->Current_PSP) = 0;                     // R12,R3,R2,R1,R0, then R11..R4
	}


}

MyRTOS_Error_t MyRTOS_Create_Task(Task_Reference_t *T_REF){
	MyRTOS_Error_t ID_error = No_Error;

	// Create Its Own PSP Stack
	T_REF->PSP_Start_Addr = OS_Ctrl.PSP_Task_Locator ;
	T_REF->PSP_End_Addr   = T_REF->PSP_Start_Addr - T_REF->Stack_Size ;

	// Check Task Stack Exceeded PSP Stack
	if (T_REF->PSP_End_Addr < ((uint32_t)&_end + (uint32_t)&_Min_Heap_Size)) {
		return Task_Exceeded_PSP_Stack_Error;
	}
	// Align 8 Byte Space Between PSP Tasks
	/* 	 	-- Task A --
	 * 		Start PSP Stack_A
	 * 		Size of Satck_A
	 * 		End PSP Stack_A
	 * 		8 byte Space
	 * 		-- Task B --	...
	 */
	OS_Ctrl.PSP_Task_Locator = T_REF->PSP_End_Addr - 8;

	MyRTOS_Create_TaskStack(T_REF);

	// Add Task to Scheduler Table then Update Number of  ActiveTask
	OS_Ctrl.OS_Tasks[OS_Ctrl.Number_of_Active_Task] =  T_REF ;
	OS_Ctrl.Number_of_Active_Task++ ;

	// Task Status Update to Suspend
	T_REF->Task_Status = Suspend ;
	return ID_error;
}

void MyRTOS_Start_OS(){
	OS_Ctrl.OS_ID_Mode = OS_Run ;
	//Set Default "Current Task =Idle Task"
	OS_Ctrl.Current_Task = &MyRTOS_IDLE_Task ;
	//Activate IDLE Task
	MyRTOS_ActivateTask(&MyRTOS_IDLE_Task);
	//Start Ticker
	Start_Ticker();

	OS_SET_PSP(OS_Ctrl.Current_Task->Current_PSP);
	//Switch Thread Mode SP from MSP to PSP
	OS_SWITCH_SP_TO_PSP;
	Unprivileged_CPU_AccessLevel;
	MyRTOS_IDLE_Task.Ptr_To_Task();

}

// handler mode
//------------------------------------------------------------------------------
// Sort OS_Tasks[] by Priority (lower number = higher priority)
//------------------------------------------------------------------------------
void Bubble_Sort(void)
{
	uint32_t i, j;
	Task_Reference_t *Temp = NULL;
	uint32_t n = OS_Ctrl.Number_of_Active_Task;


	if (n == 0) {
		return;
	}
	for (i = 0; i + 1 < n; i++) {
		for (j = 0; j + i + 1 < n; j++) {
			// FIX: compare/swap two adjacent elements of the SAME array,
			// instead of swapping two unrelated single pointers
			if (OS_Ctrl.OS_Tasks[j]->Priority > OS_Ctrl.OS_Tasks[j + 1]->Priority) {
				Temp                     = OS_Ctrl.OS_Tasks[j];
				OS_Ctrl.OS_Tasks[j]      = OS_Ctrl.OS_Tasks[j + 1];
				OS_Ctrl.OS_Tasks[j + 1]  = Temp;
			}
		}
	}
}

// handler mode
void MyRTOS_Update_Scheduler_Table_and_Ready_Buffer(void){
	Task_Reference_t *Temp = NULL ;
	Task_Reference_t *P_current_Task ;
	uint8_t i = 0 ;
	uint8_t n = OS_Ctrl.Number_of_Active_Task ;
	uint8_t Group_Priority = 0 ;
	uint8_t Group_Started =  0 ;
	// Use any algorithm you want to reorder the Scheduling Table according to priority
	Bubble_Sort();
	// Scheduling table is now sorted by priority -> clear the Ready FIFO
	while(GET_ITEM(&Ready_FIFO,&Temp /*pointer to pointer*/) !=  BUF_EMPTY);
	// Add tasks in the new order
	for (i = 0; i < n ; i++) {
		P_current_Task = OS_Ctrl.OS_Tasks[i];
		if(P_current_Task ->Task_Status == Suspend)
			continue ;
		if (!Group_Started) {
			Group_Priority =  P_current_Task->Priority ;
			Group_Started = 1 ;
		}else if (P_current_Task->Priority != Group_Priority ) {
			break ;
		}
		ADD_ITEM(&Ready_FIFO, P_current_Task);
		P_current_Task->Task_Status = Ready ;
	}
	// NEW: remember which priority group is now sitting in Ready_FIFO.
	if (Group_Started) {
		OS_Ctrl.Ready_Group_Priority = Group_Priority;
	}
}
// handler mode
void Decide_What_Next(void){
	if ((OS_Ctrl.Current_Task != NULL) && (OS_Ctrl.Current_Task->Task_Status != Suspend) && (Ready_FIFO.Count != 0) && (OS_Ctrl.Current_Task->Priority == OS_Ctrl.Ready_Group_Priority)) {

		OS_Ctrl.Current_Task->Task_Status = Ready ;

		// Add Back Again to Ready Queue (Round Robin)
		ADD_ITEM(&Ready_FIFO, OS_Ctrl.Current_Task);

		GET_ITEM(&Ready_FIFO, &OS_Ctrl.Next_Task);
		OS_Ctrl.Next_Task->Task_Status = Run ;

	} else{
		if (GET_ITEM(&Ready_FIFO, &OS_Ctrl.Next_Task) == BUF_NO_ERROR) {
			OS_Ctrl.Next_Task->Task_Status = Run ;
			if ((OS_Ctrl.Current_Task != NULL) && (OS_Ctrl.Current_Task->Priority == OS_Ctrl.Next_Task->Priority) && (OS_Ctrl.Current_Task->Task_Status != Suspend)) {
				ADD_ITEM(&Ready_FIFO, OS_Ctrl.Current_Task);
				OS_Ctrl.Current_Task->Task_Status = Ready ;
			}
		}

	}
}
// handler mode
//--------------------------------------------------------------------
// SVC Service that Passes Parameters and Returns a Value
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
	case SVC_ACTIVATE_TASK     : 	// 1- Reorder Scheduler Table 		2- Update Ready Buffer   //3-OS is in Running State
	case SVC_TERMINATE_TASK    :
		MyRTOS_Update_Scheduler_Table_and_Ready_Buffer();
		if (OS_Ctrl.OS_ID_Mode == OS_Run) {
			// FIX: strcmp must compare the task NAME (char array),
			// not the Task_Reference_t* struct pointer itself.
			if(OS_Ctrl.Current_Task->Priority != 255 ){
				// Decide What Next ?!
				Decide_What_Next();
				// Set PendSV (Do Context Switch / restore )
				OS_SET_PendSV();
			}

		}
		break ;
	case  SVC_TASK_WAITNG_TIME :MyRTOS_Update_Scheduler_Table_and_Ready_Buffer();
	break ;
	default : // SVC Request Unknown
		break ;
	}
	return ;
}

//Thread Mode
void MyRTOS_SVC_OS_SET(SVC_ID ID){
	switch(ID){
	case SVC_ACTIVATE_TASK    : __asm("SVC #0x00");  // activate  task
	break;
	case SVC_TERMINATE_TASK   : __asm("SVC #0x01"); //  terminate task
	break;
	case SVC_TASK_WAITNG_TIME : __asm("SVC #0x02"); // wait time task
	break;
	case SVC_AquireMutex : __asm("SVC #0x03"); 		//Aquire Mutex
	break;
	case SVC_ReleaseMutex : __asm("SVC #0x04"); 	//Release Mutex
	break;
	}
}
void MyRTOS_ActivateTask (Task_Reference_t *T_REF){
	T_REF->Task_Status = Wait ;
	MyRTOS_SVC_OS_SET(SVC_ACTIVATE_TASK);
}
void MyRTOS_TerminateTask (Task_Reference_t *T_REF){
	T_REF->Task_Status = Suspend ;
	MyRTOS_SVC_OS_SET(SVC_TERMINATE_TASK);
}
void MyRTOS_TimeWaitTask(uint32_t Ticks,Task_Reference_t *T_REF){
	T_REF->TimingWaiting.Blocking = Enable ;
	T_REF->TimingWaiting.Ticks_Count =  Ticks;
	T_REF->Task_Status = Suspend ;
	MyRTOS_SVC_OS_SET(SVC_TERMINATE_TASK);
}

void Update_Task_WaitingTime(){

	for (uint8_t i = 0; i < OS_Ctrl.Number_of_Active_Task ; ++i) {
		if (OS_Ctrl.OS_Tasks[i]->Task_Status == Suspend) {
			if(OS_Ctrl.OS_Tasks[i]->TimingWaiting.Blocking == Enable){
				OS_Ctrl.OS_Tasks[i]->TimingWaiting.Ticks_Count--;
				if (OS_Ctrl.OS_Tasks[i]->TimingWaiting.Ticks_Count == 1) {
					OS_Ctrl.OS_Tasks[i]->TimingWaiting.Blocking = Disable ;
					OS_Ctrl.OS_Tasks[i]->Task_Status = Wait ;
					MyRTOS_SVC_OS_SET(SVC_TASK_WAITNG_TIME);
				}
			}

		}
	}
}


MyRTOS_Error_t MyRTOS_AcquireMutex(Mutex_Reference_t *M_REF,Task_Reference_t *T_REF){
	if(M_REF->Current_Task_Use_Mutex == NULL){ // No one has Mutex
		M_REF->Current_Task_Use_Mutex = T_REF ;
	}else{
		if (M_REF->Next_Task_Use_Mutex == NULL) { // No Task Request the Mutex
			M_REF->Next_Task_Use_Mutex = T_REF ;
			// Move to Suspend State
			T_REF->Task_Status =Suspend ;
			// Ensure its Suspend
			MyRTOS_SVC_OS_SET(SVC_TERMINATE_TASK);
		} else {
			return Mutex_Is_Reached_Max_Number_Of_Users ;

		}
	}
	return No_Error ;

}
void MyRTOS_ReleaseMutex(Mutex_Reference_t *M_REF){
	if (M_REF->Current_Task_Use_Mutex != NULL) { // Task Want To Release Mutex
		M_REF->Current_Task_Use_Mutex =M_REF->Next_Task_Use_Mutex ; // Make Next  is Current
		M_REF->Next_Task_Use_Mutex = NULL ; // Next IS NULL
		M_REF->Current_Task_Use_Mutex->Task_Status = Wait ; // Update Task Status From Suspend to Wait
		MyRTOS_SVC_OS_SET(SVC_ACTIVATE_TASK);      // Activate the Task that take Mutex
	}
}
