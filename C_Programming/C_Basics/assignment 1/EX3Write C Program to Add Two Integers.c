/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX3:Write C Program to Add Two Integers
#include<stdio.h>
int main(){
	int var1,var2,sum;
	printf("Enter Two integers :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&var1);
	scanf("%d",&var2);
	sum=var1+var2;
	printf("Sum:%d",sum);
	return 0;}