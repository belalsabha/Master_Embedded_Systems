/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
/*EX3:Write C program to Find largest number among three numbers  */
#include<stdio.h>
int main(){
	float var1,var2,var3;
	printf("Enter three numbers :");
	fflush(stdin);fflush(stdout);
	scanf("%f",&var1);
	scanf("%f",&var2);
	scanf("%f",&var3);
	if(var1>var2&&var1>var3)
		printf(" Number %f is the largest ",var1);
	else if (var2>var1&&var2>var3)
		printf(" Number %f is  the largest ",var2);
	else
		printf(" Number %f is  the largest ",var3);

	return 0;}
