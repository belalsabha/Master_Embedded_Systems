/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
/*EX7:Write Source Code to Swap Two Numbers without temp variable. */ 
#include<stdio.h>
int main(){
	float var1,var2;
	printf("Enter Value of a:");
	fflush(stdin);fflush(stdout);
	scanf("%f",&var1);
	printf("Enter Value of b:");
	fflush(stdin);fflush(stdout);
	scanf("%f",&var2);
	var1+=var2;
	var2=var1-var2;
	var1=var1-var2;
	printf("After swapping, value of a =%f \nAfter swapping, value of b =%f",var1,var2);
	return 0;}