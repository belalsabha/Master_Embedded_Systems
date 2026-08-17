/*
 * MyRTOS_FIFO.h
 *
 *  Created on: Aug 15, 2026
 *      Author: Eng - Belal Hani Sabha
 */
#ifndef INC_MYRTOS_FIFO_H_
#define INC_MYRTOS_FIFO_H_
#include <stdio.h>
#include <stdint.h>
#include "Scheduler.h"
#define type Task_Reference_t*   // Item stored in the FIFO: pointer to a task (can change if needed)
//------------------------------------------------------------------------------
// FIFO Buffer Structure
//------------------------------------------------------------------------------
typedef struct {
    type      *Base;     // Ptr to buffer base (&array[0])
    type      *Head;     // Ptr to next write position
    type      *Tail;     // Ptr to next read position
    uint32_t   Length;    // Total buffer size (capacity)
    uint32_t   Count;     // Current number of elements in buffer
} FIFO_BUF_t;
//------------------------------------------------------------------------------
// FIFO Status Enum
//------------------------------------------------------------------------------
typedef enum {
    BUF_NO_ERROR,   // Operation successful
    BUF_FULL,       // Buffer is full
    BUF_EMPTY,      // Buffer is empty
    BUF_NULL        // Invalid buffer or parameters
} BUF_Status_t;
//------------------------------------------------------------------------------
// API Prototypes
//------------------------------------------------------------------------------
BUF_Status_t ADD_ITEM(FIFO_BUF_t *ADD_PTR, type add_data);
BUF_Status_t GET_ITEM(FIFO_BUF_t *GET_PTR, type *get_data);
BUF_Status_t Is_BUF_FULL(FIFO_BUF_t *Full_buf);
BUF_Status_t BUF_INIT(FIFO_BUF_t *fifo, type *buff, uint32_t Buf_Length);


#endif /* INC_MYRTOS_FIFO_H_ */
