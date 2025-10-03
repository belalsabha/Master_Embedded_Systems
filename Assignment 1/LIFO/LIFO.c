/*
 * LIFO.c
 * Created on: 30 Sep 2025
 * Author: Eng-Belal Hani Abu Sabha
 */

#include "LIFO.h"   // include LIFO.h

// Push item to LIFO stack
BUF_Status Push(LIFO_BUF *Pu_buf, type Item) {
    if (!Pu_buf || !Pu_buf->Head || !Pu_buf->Base) // check if buffer is valid
        return BUF_NULL;

    if (Is_BUF_FULL(Pu_buf) == BUF_FULL)           // check if buffer is Full
        return BUF_FULL;

    *(Pu_buf->Head) = Item;   // put item at current head
    Pu_buf->Head++;           // make head point to next position
    Pu_buf->Count++;          // increase count

    return BUF_NO_ERROR;    
}

// Pop item from LIFO stack
BUF_Status Pop(LIFO_BUF *Po_buf, type *Item_add) {
    if (!Po_buf || !Po_buf->Head || !Po_buf->Base) // Check if buffer is valid
        return BUF_NULL;

    if (Po_buf->Base == Po_buf->Head)             // empty buffer
        return BUF_EMPTY;

    Po_buf->Head--;            // make head point to previous position
    *Item_add = *(Po_buf->Head); 
    Po_buf->Count--;           // decrease count

    return BUF_NO_ERROR;       
}

// Check if LIFO is full
BUF_Status Is_BUF_FULL(LIFO_BUF *Full_buf) {
    if (!Full_buf || !Full_buf->Head || !Full_buf->Base) // invalid buffer
        return BUF_NULL;

    if (Full_buf->Head >= (Full_buf->Base + Full_buf->Length)) // full check
        return BUF_FULL;
    else
        return BUF_NOT_FULL;
}

// Initialize LIFO buffer
BUF_Status BUF_INIT(LIFO_BUF *lifo ,type *buff, uint32_t buf_Length){
    if(buff == NULL || buf_Length == 0) // invalid arguments
        return BUF_NULL;

    lifo->Base = buff;        // assign base address
    lifo->Head = lifo->Base;  // head starts at base
    lifo->Length = buf_Length; // store buffer length
    lifo->Count = 0;          // initially empty

    return BUF_NO_ERROR;      }
