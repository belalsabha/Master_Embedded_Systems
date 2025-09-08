
/*

 * main.c
 *
 *  Created on: 8 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */



// Q5 c function to count number of ones in binary number
#include <stdio.h>

int countOnes(int num) {
	int count = 0;
	int i = 0;

	while (i < 32) {
		if (num & (1 << i)) {
			count++;
		}
		i++;
	}

	return count;
}

int main() {
	int number;

	printf("Enter a number: ");
	scanf("%d", &number);


	printf("Number of ones of  %d: %d\n", number,countOnes(number));

	return 0;
}
