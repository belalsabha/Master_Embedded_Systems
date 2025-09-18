/*
 * main.c
 *
 *  Created on: 15 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */

// Q5 Write a program in C to show a pointer to an array which contents are pointer to structure.

#include <stdio.h>

struct Semployee {
    char name[50];
    int id;
};

int main() {
    struct Semployee *EmployeePtrs[3];
    struct Semployee Employee1 = {"Belal", 20220388};
    struct Semployee Employee2 = {"Anas", 20220366};
    struct Semployee Employee3 = {"Malak", 20220399};

    EmployeePtrs[0] = &Employee1;
    EmployeePtrs[1] = &Employee2;
    EmployeePtrs[2] = &Employee3;

    
    struct Semployee **ptr_to_array = EmployeePtrs;  

    printf("OUTPUT:\n\n");

    
    for(int i = 0; i < 3; i++) {
        printf("Employee %d:\n", i+1);
        printf("ID: %d\n", ptr_to_array[i]->id);
        printf("Name: %s\n", ptr_to_array[i]->name);
        printf("\n");
    }

    return 0;
}
