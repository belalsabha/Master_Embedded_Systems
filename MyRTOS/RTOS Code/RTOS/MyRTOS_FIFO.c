/*
 * MyRTOS_FIFO.c
 *
 *  Created on: Aug 15, 2026
 *      Author: Eng - Belal Hani Sabha
 */
#include "MyRTOS_FIFO.h"
//------------------------------------------------------------------------------
// Initialize FIFO buffer
//------------------------------------------------------------------------------
BUF_Status_t BUF_INIT(FIFO_BUF_t *fifo, type *buff, uint32_t Buf_Length)
{
    if (fifo == NULL || buff == NULL || Buf_Length == 0)   // Check for invalid parameters
        return BUF_NULL;
    fifo->Base   = buff;        // Base address of the buffer
    fifo->Head   = fifo->Base;  // Head starts at base
    fifo->Tail   = fifo->Base;  // Tail starts at base
    fifo->Length = Buf_Length;  // Buffer capacity
    fifo->Count  = 0;           // Buffer is empty at first
    return BUF_NO_ERROR;
}
//------------------------------------------------------------------------------
// Check if FIFO is full
//------------------------------------------------------------------------------
BUF_Status_t Is_BUF_FULL(FIFO_BUF_t *Full_buf)
{

    if (!Full_buf || !Full_buf->Base || !Full_buf->Head || !Full_buf->Tail)  // Invalid buffer
        return BUF_NULL;
    if (Full_buf->Count >= Full_buf->Length)  // Full when count reaches length
        return BUF_FULL;
    return BUF_NO_ERROR;  // Otherwise not full
}
//------------------------------------------------------------------------------
// Push item (pointer to a task) into FIFO
//------------------------------------------------------------------------------
BUF_Status_t ADD_ITEM(FIFO_BUF_t *ADD_PTR, type add_data)
{
    BUF_Status_t Status = Is_BUF_FULL(ADD_PTR);
    if (Status == BUF_FULL)
        return BUF_FULL;
    if (Status == BUF_NULL)
        return BUF_NULL;

    *(ADD_PTR->Head) = add_data;  // Store the pointer at current head
    ADD_PTR->Count++;             // Increment count
    if (ADD_PTR->Head == (ADD_PTR->Base + ADD_PTR->Length - 1))
        ADD_PTR->Head = ADD_PTR->Base;   // Wrap around
    else
        ADD_PTR->Head++;
    return BUF_NO_ERROR;
}
//------------------------------------------------------------------------------
// Get item (pointer to a task) from FIFO
//------------------------------------------------------------------------------
BUF_Status_t GET_ITEM(FIFO_BUF_t *GET_PTR, type *get_data)
{
    //  check GET_PTR and get_data themselves before dereferencing
    if (!GET_PTR || !get_data || !GET_PTR->Base || !GET_PTR->Head || !GET_PTR->Tail)  // Invalid buffer
        return BUF_NULL;
    if (GET_PTR->Count == 0)  // Empty buffer
        return BUF_EMPTY;
    *get_data = *(GET_PTR->Tail);  // Read pointer from tail
    GET_PTR->Count--;              // Decrement count
    if (GET_PTR->Tail == (GET_PTR->Base + GET_PTR->Length - 1))
        GET_PTR->Tail = GET_PTR->Base;   // Wrap around
    else
        GET_PTR->Tail++;
    return BUF_NO_ERROR;
}
/*
//------------------------------------------------------------------------------
// Print all FIFO elements (task names, since items are Task_Reference_t*)
//------------------------------------------------------------------------------
void print_elements(FIFO_BUF_t *fifo)
{
    if (fifo->Count == 0) {   // If empty
        printf("FIFO Empty\n");
        return;
    }
    type *Temp = fifo->Tail;  // Start from tail
    printf("-------------FIFO print-------------\n");
    for (uint32_t i = 0; i < fifo->Count; i++) {   // Loop through all elements
        Task_Reference_t *Task = *Temp;            // Dereference to get the task pointer
        if (Task != NULL)
            printf("Task: %-20s | Priority: %u\n", Task->Task_Name, Task->Priority);
        else
            printf("Task: (null)\n");
        Temp++;   // Move to next slot
        if (Temp == fifo->Base + fifo->Length)
            Temp = fifo->Base;   // Wrap around
    }
    printf("\n-----------------------------------\n");
}
*/
