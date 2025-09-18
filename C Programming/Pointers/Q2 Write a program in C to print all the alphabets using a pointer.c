
/*

 * main.c
 *
 *  Created on: 15 Sep 2025
 *

 *      Author: Eng-Belal Hani Sabha
 */




//Q2 Write a program in C to print all the alphabets using a pointer. 



#include <stdio.h>

int main() {
    char alphabet = 'A';
    char *ptr = &alphabet;  

    printf(" The Alphabets Are :\n");

    for(int i = 0; i < 26; i++) {
        printf("%c ", *ptr + i);
    }}
