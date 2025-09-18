/*
 * main.c
 *
 *  Created on: 5 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EXI: Example of Multidimensional Array In C

#include <stdio.h>

int main() {
	float arr1[2][2], arr2[2][2], sum[2][2];

	printf("Enter Elements of 1st matrix\n");
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			printf("Enter element arr1[%d][%d]: ", i, j);
			scanf("%f", &arr1[i][j]);
		}
	}

	printf("Enter Elements of 2nd matrix\n");
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			printf("Enter element arr2[%d][%d]: ", i, j);
			scanf("%f", &arr2[i][j]);
			sum[i][j] = arr1[i][j] + arr2[i][j];
		}
	}

	printf("\nSum of Matrix:\n");
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%f\t", sum[i][j]);
		}
		printf("\n");
	}

	return 0;
}

