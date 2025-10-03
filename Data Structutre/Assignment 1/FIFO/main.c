/*
 * main.c

 *
 *  Created on: 30 Sep 2025
 *      Author: Eng- Bela Hani Abu Sabha
 */
#include "FIFO.h"   // include FIFO.h
#define SIZE 5       //  size
type arr[SIZE];     // create buffer array

int main(void){
    FIFO_BUF Uart_fifo;  
    uint8_t i , Temp=0;  

    // Initialize FIFO
    if(BUF_INIT(&Uart_fifo, arr, SIZE) == BUF_NO_ERROR){
        printf("Init done \n");
    }

    //add 7 elements 
    for(i=0; i<7; i++){
        printf("Add %x \n", i);
        if(ADD_ITEM(&Uart_fifo, &i) == BUF_NO_ERROR){
            printf("Add %x done \n", i);
        }else{
            printf("Add %x failed \n", i);
        }
    }

    // print buffer contents
    print_elements(&Uart_fifo);

    // Get 2 items from buffer

    for (int i = 0; i < 2; ++i)
    {
           if(GET_ITEM(&Uart_fifo,&Temp) == BUF_NO_ERROR)
        printf("Get %x done\n", Temp);
    else
        printf("Get failed\n");
    }



    // Add 2 new items again
    for(i=0; i<2; i++){
        printf("Add %x \n", i);
        if(ADD_ITEM(&Uart_fifo, &i) == BUF_NO_ERROR){
            printf("Add %x done \n", i);
        }else{
            printf("Add %x failed\n", i);
        }
    }

    // Print buffer contents again
    print_elements(&Uart_fifo);

    return 0;  // End program
}
