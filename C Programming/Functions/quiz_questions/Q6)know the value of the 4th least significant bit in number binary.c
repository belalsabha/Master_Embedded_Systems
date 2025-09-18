/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//Q6)know the value of the 4th least significant bit in number binary.
#include <stdio.h>

int main()
{
	int decimalNumber, bitPosition, shiftedValue;

	printf("Enter an integer in decimal number system: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &decimalNumber);

	printf("%d in binary number system is:\n", decimalNumber);

	for (bitPosition = 31; bitPosition >= 0; bitPosition--)
	{
		shiftedValue = decimalNumber >> bitPosition;

		if (shiftedValue & 1)
			printf("1");
		else
			printf("0");
	}

	printf("\n");

	shiftedValue = decimalNumber >> 3;

	if (shiftedValue & 1)
		printf("4th least significant bit is 1");
	else
		printf("4th least significant bit is 0");

	return 0;
}