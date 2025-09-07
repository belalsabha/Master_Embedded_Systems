/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX3_C_Program_to_Reverse_a_Sentence_Using_Recursion
#include <stdio.h>

void reverseSentence();
int main() {
	printf("Enter a sentence: ");
	reverseSentence(); 
	printf("\n");

	return 0;
}


void reverseSentence() {
	char c;

	scanf("%c", &c);

	if (c != '\n') {
		reverseSentence(); 
		printf("%c", c);   
	}
}