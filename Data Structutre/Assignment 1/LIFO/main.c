/*
 * main.c
 * Created on: 30 Sep 2025
 * Author: Eng-Belal Hani Abu Sabha
 */

#include <stdio.h>     
#include <stdlib.h>     // for Dynamic allocation
#include "LIFO.h"       // include LIFO definitions

#define Size 3          //  buffer size

int main(void) {
    unsigned S_Buf[Size];    // static buffer array
    uint8_t Temp;            // Temp variable for storing popped values
    LIFO_BUF First_Buf , Second_Buf;  // two stack buffers 

    // ===== Dynamic allocation =====
    if(BUF_INIT(&First_Buf ,(uint8_t*) malloc(Size * sizeof(uint8_t)), Size) == BUF_NO_ERROR){
        printf("Init done \n");
    }

    if (!First_Buf.Base){    // check if malloc failed
        printf("Malloc failed!\n");
        return -1;
    }

    printf("Dynamic Allocation PUSH\n");
    for (int i = 0; i < 5; i++) {   // Push more than capacity for testing
        printf("PUSH %d\n", i);
        Push(&First_Buf, i);
    }

    printf("Dynamic Allocation POP\n");
    for (int i = 0; i < 5; i++) {   // Poping values
        if(Pop(&First_Buf, &Temp) == BUF_NO_ERROR)
            printf("POP %d\n", Temp);
        else
            printf("POP failed\n");
    }

    // ===== Static allocation =====
    BUF_INIT(&Second_Buf, S_Buf, Size); // initialize stack with static buffer

    printf("Static Allocation PUSH\n");
    for(int i=0; i<7; i++){   // push more than capacity
        printf("PUSH %d \n", i);
        if(Push(&Second_Buf,i) == BUF_NO_ERROR){
            printf("Add %d done \n", i);
        }else{
            printf("Add %d failed \n", i);
        }
    }

    printf("Static Allocation POP\n");
    for (int i = 0; i < Size; i++) {   // Pop all available values
        if(Pop(&Second_Buf, &Temp) == BUF_NO_ERROR)
            printf("POP %d\n", Temp);
        else
            printf("POP failed\n");
    }

    free(First_Buf.Base);  // Free dynamic memory
    return 0;
}
