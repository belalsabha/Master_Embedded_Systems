/*
 * FIFO.h
 *
 *  Created on: 30 Sep 2025
 *      Author:Eng- Bela Hani Abu Sabha
 */

#ifndef FIFO_H_        // header protection
#define FIFO_H_

#include <stdio.h>    
#include <stdint.h>    /

#define type uint8_t   // can change if i want

// Structure to represent FIFO buffer
typedef struct {
    type *Base;        // Ptr to buffer base &array[0]
    type *Head;        // Ptr to next  position (write)
    type *Tail;        // Ptr to next  position (read)
    uint32_t Length;   // size
    uint32_t Count;    // number of elements in buffer
} FIFO_BUF;

// Enum to represent FIFO status
typedef enum {
    BUF_NO_ERROR,      
    BUF_FULL,         
    BUF_EMPTY,         
    BUF_NULL           
} BUF_Status;

// Function prototypes
BUF_Status ADD_ITEM(FIFO_BUF *ADD_PTR, type *add_data);  
BUF_Status GET_ITEM(FIFO_BUF *GET_PTR, type *get_data);  
BUF_Status Is_BUF_FULL(FIFO_BUF *Full_buf);  
void print_elements(FIFO_BUF *fifo);  
BUF_Status BUF_INIT(FIFO_BUF *fifo ,type *buff, uint32_t Buf_Length);  

#endif /* FIFO_H_ */
