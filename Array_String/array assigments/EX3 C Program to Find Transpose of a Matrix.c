/*
 * main.c
 *
 *  Created on: 5 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX3: C Program to Find Transpose of a Matrix
#include <stdio.h>

int main() {
    int Rows, Columns;
    float arr1[100][100], arr2[100][100];

    printf("Enter Rows and Columns of Matrix: ");
    scanf("%d %d", &Rows, &Columns);

    printf("Enter elements of matrix:\n");
    for (int j = 0; j < Rows; j++) {
        for (int i = 0; i < Columns; i++) {
            printf("Enter element arr1[%d][%d]: ", j, i);
            scanf("%f", &arr1[j][i]);
        }
    }

  
    for (int j = 0; j < Rows; j++) {
        for (int i = 0; i < Columns; i++) {
            arr2[i][j] = arr1[j][i];
        }
    }

  
    printf("\nOriginal Matrix:\n");
    for (int j = 0; j < Rows; j++) {
        for (int i = 0; i < Columns; i++) {
            printf("%.2f\t", arr1[j][i]);
        }
        printf("\n");
    }

  
    printf("\nTranspose of Matrix:\n");
    for (int j = 0; j < Columns; j++) {
        for (int i = 0; i < Rows; i++) {
            printf("%.2f\t", arr2[j][i]);
        }
        printf("\n");
    }

    return 0;
}
