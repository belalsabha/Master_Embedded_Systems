/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
/*EX8:Write C program to make simple calculator to  +,-,*,/ using switch case */

#include<stdio.h>

int main() {
	char operator;
	float var1,var2,result;

	printf("Enter An Operator Either + or - or * or / : ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &operator);

	printf("Enter Two Operands : ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &var1, &var2);

	switch(operator) {
	case '+':
		result = var1 + var2;
		printf("%.2f + %.2f = %.2f", var1, var2, result);
		break;
	case '-':
		result = var1 - var2;
		printf("%.2f - %.2f = %.2f", var1, var2, result);
		break;
	case '*':
		result = var1 * var2;
		printf("%.2f * %.2f = %.2f", var1, var2, result);
		break;
	case '/':
		if(var2 != 0) {
			result = var1 / var2;
			printf("%.2f / %.2f = %.2f", var1, var2, result);
		} else {
			printf("Error! We cannt divide by zero.");
		}
		break;
	default:
		printf("Invalid operator.");
	}

	return 0;
}
