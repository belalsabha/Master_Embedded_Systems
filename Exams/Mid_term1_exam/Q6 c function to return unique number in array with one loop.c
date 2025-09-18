
/*

 * main.c
 *
 *  Created on: 8 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */



// Q6 c function to return unique number in array with one loop
#include <stdio.h>

int find_unique_number(int arr[], int size);

int main() {

    int a1[] = {4, 2, 5, 2, 5, 7, 4};
    int size1 = sizeof(a1) / sizeof(a1[0]);
    printf("Unique number: %d\n", find_unique_number(a1, size1));


    int a2[] = {4, 2, 4};
    int size2 = sizeof(a2) / sizeof(a2[0]);
    printf("Unique number: %d\n", find_unique_number(a2, size2));

    return 0;
}
int find_unique_number(int arr[], int size) {
    int unique_number = 0;

    for (int i = 0; i < size; i++) {
        unique_number ^= arr[i];
    }

    return unique_number;
}