/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
/*EX5:Write C program to Check Whether a character is alphabet or not */
#include<stdio.h>
int main(){
	char alphabet;
	printf("Enter An alphabet :");
	fflush(stdin);fflush(stdout);
	scanf("%c",&alphabet);
	if(alphabet>='a'&&alphabet<='z'||alphabet>='A'&&alphabet<='Z')
		printf("%c is an alphabet",alphabet);
	else

		printf("%c is not an alphabet",alphabet);


	return 0;}