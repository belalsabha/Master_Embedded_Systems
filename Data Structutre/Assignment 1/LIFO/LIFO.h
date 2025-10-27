
/*
 * LIFO.h
 * Created on: 30 Sep 2025
 * Author: Eng-Belal Hani Abu Sabha
 */

#ifndef LIFO_H_           // header Protection
#define LIFO_H_

#include <stdint.h>       

#define type uint8_t      // define type 



// Structure to represent LIFO buffer
// ============= Data Types =============
typedef struct {
    type *Base;           // Ptr to the buffer start
    type *Head;           // Ptr to next free position
    uint32_t Length;      //  size
    uint32_t Count;       // number of items
} LIFO_BUF;

// Enum to represent LIFO status
// ============= Status Enum =============
typedef enum {
    BUF_NO_ERROR,         
    BUF_FULL,            
    BUF_EMPTY,            
    BUF_NULL,            
    BUF_NOT_FULL          
} BUF_Status;

// ============= APIs =============
BUF_Status Push(LIFO_BUF *Pu_buf, type Item);         // Push item to stack
BUF_Status Pop (LIFO_BUF *Po_buf, type *Item_add);    // Pop item from stack
BUF_Status Is_BUF_FULL (LIFO_BUF *Full_buf);          // check if full
BUF_Status BUF_INIT(LIFO_BUF *lifo ,type *buff, uint32_t buf_Length); // init buffer

#endif /* LIFO_H_ */      
