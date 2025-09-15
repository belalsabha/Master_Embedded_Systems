
/*

 * main.c
 *
 *  Created on: 15 Sep 2025
 *

 *      Author: Eng-Belal Hani Sabha
 */




//Q1:Write a program in C to demonstrate how to handle the pointers in the program.



#include <stdio.h>

int main() {
    int m = 29;
    int *ab = &m;  

    printf("Address of m: %p\n", (void*)&m);
    printf("Value of m: %d\n\n", m);

    printf("Now ab is assigned with the address of m.\n");
    printf("Address stored in pointer ab: %p\n", (void*)ab);
    printf("Content pointed to by ab: %d\n\n", *ab);

    m = 34;
    printf("The value of m is assigned to 34 now.\n");
    printf("Address stored in pointer ab: %p\n", (void*)ab);
    printf("Content pointed to by ab: %d\n\n", *ab);

    *ab = 7;
    printf("The pointer variable ab is assigned with the value 7 now.\n");
    printf("Address of m: %p\n", (void*)&m);
    printf("Value of m: %d\n", m);

    return 0;
}
