/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
/*EX1:Write C program to Check Whether a  Number is even or odd. */
#include<stdio.h>
int main(){
	int var1;
	printf("Enter a Number to Check:");
	fflush(stdin);fflush(stdout);
	scanf("%d",&var1);
	if(var1%2==0)
		printf(" Number %d is even ",var1);
	else
		printf(" Number %d is odd ",var1);
	return 0;}