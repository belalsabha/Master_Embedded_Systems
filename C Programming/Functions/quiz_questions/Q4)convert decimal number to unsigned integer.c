/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//Q4)convert decimal number to unsigned integer.
#include <stdio.h>

unsigned int ascii_to_uint(char ascii_array[], int size) ;




int main() {
    char number[] = {'1', '2', '3', '4', '5'};


    printf("ascii_to_uint: %d \n",ascii_to_uint(number, 5));

    return 0;
}

unsigned int ascii_to_uint(char ascii_array[], int size) {
    unsigned int result = 0;
    
    for (int i = 0; i < size; i++) {
        if (ascii_array[i] >= '0' && ascii_array[i] <= '9') {
            result = result * 10 + (ascii_array[i] - '0');
        }
    }
    
    return result;
}

