/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX5:Write C Program to Find ASCII Value of a Character
#include<stdio.h>
int main(){
	char  character;
	printf("Enter a character:");
	fflush(stdin);fflush(stdout);
	scanf("%c",&character);

	printf("ASCII value of %c:%d",character,character);
	return 0;}
