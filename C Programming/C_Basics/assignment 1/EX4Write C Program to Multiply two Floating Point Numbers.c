/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX4:Write C Program to Multiply two Floating Point Numbers
#include<stdio.h>
int main(){
	float var1,var2,multiply;
	printf("Enter Two Numbers:");
	fflush(stdin);fflush(stdout);
	scanf("%f",&var1);
	scanf("%f",&var2);
	multiply=var1*var2;
	printf("Sum:%f",multiply);
	return 0;}