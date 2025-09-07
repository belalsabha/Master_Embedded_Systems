/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX2_C_Program_to_Calculate_Factorial_of_a_Number_Using_Recursion
#include <stdio.h>
int factorial (int num);
int main() {
	int num;

	printf("Enter a number to find its factorial : ");
	scanf("%d",&num);

if(num>=0)
	printf("your factorial for  %d = %d: ",num,factorial(num));
else
	printf("no factorial for negative numbers");



	return 0;
}
int factorial(int num) {
	if (num <0) 
		return 0;
	else if(num == 0)
		return 1;
	else
		return num*factorial(num-1);

	}
