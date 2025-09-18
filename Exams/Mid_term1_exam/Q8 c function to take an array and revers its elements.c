/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//Q8 c function to take an array and revers its elements
#include <stdio.h>
#include <string.h>
void take_Array_Elements(int array[], int length);
void reversing_Array(int array[], int length);
void displaying_Array(int array[], int length);


int main() {
    int  Capacity;
    int Array[20];
    printf("Enter size of  array: ");
    fflush(stdin); fflush(stdout);
    scanf("%d", &Capacity);
    printf("\n enter elements of array: ");
    take_Array_Elements(Array,Capacity);


    printf("\n Array before reversing: ");
    displaying_Array(Array,Capacity);
    reversing_Array(Array,Capacity);
    printf("\n Array after reversing: ");
    displaying_Array(Array,Capacity);




    return 0;
}

void take_Array_Elements(int array[], int length){

    for(int counter = 0; counter < length; counter++)
    {
        scanf("%d", &array[counter]);
    }
}

void displaying_Array(int array[], int length)
{

    for(int counter = 0; counter < length; counter++)
    {
        printf("%d ", array[counter]);
    }
}

void reversing_Array(int array[], int length)
{
    int reverse_array[20];
    for(int counter = 0,down_counter=length-1; counter < length; counter++,down_counter--)
    {
        reverse_array[counter]=array[down_counter];


    }
    for(int counter = 0; counter < length; counter++)
    {
        array[counter]=reverse_array[counter];


    }


}
