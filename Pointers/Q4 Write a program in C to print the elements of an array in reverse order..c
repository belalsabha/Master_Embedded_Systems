/*

 * main.c
 *
 *  Created on: 15 Sep 2025
 *

 *      Author: Eng-Belal Hani Sabha
 */


//Q4 Write a program in C to print the elements of an array in reverse order.

#include <stdio.h>


int main() {
    int arr[15];
    int *rev_ptr,size;
    printf("\nInput the number of elements to store in the array (max 15): ");
    scanf("%d",&size);
    printf("\nInput %d number of elements in the array : \n",size);

    for(int i=0;i<size;i++){
        printf("element %d ",i+1);
        scanf("%d",&arr[i]);
        printf("\n");
    }

    rev_ptr=(arr+size-1);
    printf("The elements of array in reverse order are :\n");
    for(int i=0,j=size;i<size;i++){
        printf("element %d  = %d ",j,*rev_ptr);
        j--;
        rev_ptr--;
        printf("\n");

    }


    

    return 0;
}
