/*
 * main.c
 *
 *  Created on: 5 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
// EX2: C Program to Calculate Average Using Arrays

#include <stdio.h>

int main() {
    float arr1[100], avg = 0.0;
    int n;

    printf("Enter number of data: ");
    scanf("%d", &n);

    printf("Enter elements of array to find average:\n");
    for (int j = 0; j < n; j++) {
        printf("Enter element arr1[%d]: ", j);
        scanf("%f", &arr1[j]);
        avg += arr1[j];
    }

    printf("\nAverage = %f\n", avg / n);

    return 0;
}

