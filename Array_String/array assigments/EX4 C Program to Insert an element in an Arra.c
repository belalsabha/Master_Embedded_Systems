/*
 * main.c
 *
 *  Created on: 5 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX4: C Program to Insert an element in an Array
#include <stdio.h>

int main() {
    int number_of_elements,inserted_number,location;
    float arr1[10]={1,2,3,4,5,6,7,8,9,10};

    printf("Enter Number of Elements: ");
    fflush(stdin);  fflush(stdout);
    scanf("%d",&number_of_elements);
    for (int j = 0; j <number_of_elements; j++) {
        printf("%f\t",arr1[j]);
    }

    printf("\nEnter element to be inserted:");
    fflush(stdin);  fflush(stdout);
    scanf("%d",&inserted_number);
    printf("\nEnter Location:");
    fflush(stdin);  fflush(stdout);
    scanf("%d",&location);

    for (int var=number_of_elements; location <= var;var--) {
        arr1[var]=arr1[var-1];
    }
    arr1[location] = inserted_number;
    number_of_elements++;


    printf("\nAfter insertion:\n");
    for (int j = 0; j < number_of_elements; j++) {
        printf("%f\t", arr1[j]);
    }


    return 0;
}