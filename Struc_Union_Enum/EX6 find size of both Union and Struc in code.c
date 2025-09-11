
/*

 * main.c
 *
 *  Created on: 11 Sep 2025
 *

 *      Author: Eng-Belal Hani Sabha
 */




//EX6: find size of both Union and Struc in code
#include <stdio.h>

union job {         
    char name[32];
    float salary;
    int worker_no;
}u;

struct job1 {
    char name[32];
    float salary;
    int worker_no;
}s;

int main() {
	// output should be 
    printf("size of union = %d", sizeof(u)); //size of union =  32 
    printf("\nsize of structure = %d", sizeof(s));   //size of structure = 40
    return 0;
}