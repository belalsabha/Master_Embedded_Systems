/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//Q7)check if a given number is power of 3.
#include <stdio.h>

int isPowerOfThree(int number) {
    if (number <= 0) {
        return 1;
    }
    
    while (number % 3 == 0) {
        number /= 3;
    }
    
    return (number == 1) ? 0 : 1;
}

int main() {
   
    printf("9 ==> %d\n", isPowerOfThree(9));   
    printf("20 ==> %d\n", isPowerOfThree(20));  

    
    return 0;
}