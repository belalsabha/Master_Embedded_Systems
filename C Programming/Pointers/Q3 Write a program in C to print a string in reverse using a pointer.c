/*

 * main.c
 *
 *  Created on: 15 Sep 2025
 *

 *      Author: Eng-Belal Hani Sabha
 */


//Q3 Write a program in C to print a string in reverse using a pointer

#include <stdio.h>
#include <string.h>

int main() {
	char string[100];
	char *rev_ptr;

	printf("Input a string: ");
	scanf("%s", string);

	int length = strlen(string);
	rev_ptr = string + length - 1;

	printf("String in reverse order:\n");


	for(int i = 0; i < length; i++) {
		printf("%c", *rev_ptr);
		rev_ptr--;
	}

	printf("\n");

	return 0;
}
