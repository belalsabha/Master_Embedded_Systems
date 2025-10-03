/*
 * FIFO.c
 *
 *  Created on: 30 Sep 2025
 *      Author: Eng- Bela Hani Abu Sabha
 */
// FIFO.c


#include "FIFO.h"   // Include FIFO.h

// Initialize FIFO buffer
BUF_Status BUF_INIT(FIFO_BUF *fifo ,type *buff, uint32_t Buf_Length){
    if(buff == NULL || Buf_Length == 0) // Check for invalid parameters
        return BUF_NULL;

    fifo->Base = buff;     //  base address of buffer
    fifo->Head = fifo->Base;  // Head starts at base
    fifo->Tail = fifo->Base;  // Tail starts at base
    fifo->Length = Buf_Length; // size
    fifo->Count = 0;       // at first buffer is empty

    return BUF_NO_ERROR;
}

// check if FIFO is full
BUF_Status Is_BUF_FULL(FIFO_BUF *Full_buf){
    if(!Full_buf->Base || !Full_buf->Head || !Full_buf->Tail) // invalid buffer
        return BUF_NULL;

    if(Full_buf->Count >= Full_buf->Length) // full when count reaches length
        return BUF_FULL;

    return BUF_NO_ERROR;  // otherwise not full
}

// psuh item to FIFO
BUF_Status ADD_ITEM(FIFO_BUF *ADD_PTR,type *add_data){
    if(Is_BUF_FULL(ADD_PTR) == BUF_FULL) // FIFO is Full
        return BUF_FULL;

    *(ADD_PTR->Head) = *add_data;  // write data to current head
    ADD_PTR->Count++;              // increment count

    
    if(ADD_PTR->Head == (ADD_PTR->Base + ADD_PTR->Length - 1))
        ADD_PTR->Head = ADD_PTR->Base;  
    else
        ADD_PTR->Head++;                

    return BUF_NO_ERROR;
}

// Get item from FIFO
BUF_Status GET_ITEM(FIFO_BUF *GET_PTR,type *get_data){
    if(!GET_PTR->Base || !GET_PTR->Head || !GET_PTR->Tail) // invalid buffer
        return BUF_NULL;

    if(GET_PTR->Count == 0) // empty buffer
        return BUF_EMPTY;

    *get_data = *(GET_PTR->Tail);  // read data from tail
    GET_PTR->Count--;              // decrement count

   
    if(GET_PTR->Tail == (GET_PTR->Base + GET_PTR->Length - 1))
        GET_PTR->Tail = GET_PTR->Base;  
    else
        GET_PTR->Tail++;                

    return BUF_NO_ERROR;
}

// Print all FIFO elements
void print_elements(FIFO_BUF *fifo){
    if(fifo->Count == 0){  // If empty
        printf("FIFO Empty\n");
        return;
    }

    type *Temp = fifo->Tail;  // start from tail
    printf("-------------FIFO print-------------\n");
    for(uint32_t i=0; i<fifo->Count; i++){   // Loop through all elements
        printf("%x ", *Temp);  // print element
        Temp++;                // Temp point to next address
        if(Temp == fifo->Base + fifo->Length) 
            Temp = fifo->Base;
    }
    printf("\n-----------------------------------\n");
}


