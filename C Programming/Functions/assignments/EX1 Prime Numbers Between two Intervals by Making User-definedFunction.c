/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX1 Prime Numbers Between two Intervals by Making User-definedFunction
#include <stdio.h>
int prime_numbers(int num);
int main() {
	int num1,num2;

	printf("Enter two numbers (intervals): ");
	scanf("%d %d", &num1, &num2);


	printf("Prime numbers between %d and %d are: ",num1,num2);

	int found = 0;
	for (int i =num1; i <=num2; i++) {
		if (prime_numbers(i)) {
			printf("%d ", i);
			found++;
		}
	}

	if (found == 0) {
		printf("No prime numbers found");
	}



	return 0;
}
int prime_numbers(int num) {
	if (num <= 1) {
		return 0;
	}

	for (int i = 2; i * i <= num; i++) {
		if (num % i == 0) {
			return 0;
		}
	}
	return 1;
}
