/*
 * main.c
 *
 *  Created on: 5 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */

//EX5: C Program to Search an element in Array
#include <stdio.h>

int main() {
    int number_of_elements,searched_number;
    float arr1[10]={11,22,33,44,55,66,77,88,99,100};

    printf("Enter Number of Elements: ");
    fflush(stdin);  fflush(stdout);
    scanf("%d",&number_of_elements);
    for (int j = 0; j <number_of_elements; j++) {
        printf("%f\t",arr1[j]);
    }
    
    printf("\n\nEnter element to be searched:");
    fflush(stdin);  fflush(stdout);
    scanf("%d",&searched_number);


    for(int var=0;var<number_of_elements;var++){
        if(arr1[var]==searched_number){
            printf("\nNumber Found At Location %d",var);
            break;
        }

    }



    return 0;
}


