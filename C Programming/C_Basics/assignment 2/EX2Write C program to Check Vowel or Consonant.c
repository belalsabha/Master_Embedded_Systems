/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
/*EX2:Write C program to Check Vowel or Consonant. */
#include<stdio.h>
int main(){
	char alphabet;
	printf("Enter alphabet to Check:");
	fflush(stdin);fflush(stdout);
	scanf("%c",&alphabet);
	if(alphabet=='a'||alphabet=='e'||alphabet=='i'||alphabet=='o')
		printf(" Char %c is Vowel ",alphabet);
	else
		printf(" Char %c is Consonant ",alphabet);
	return 0;}



