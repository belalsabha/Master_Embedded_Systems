/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX2:Write C Program to Print a Integer Entered by a User
#include<stdio.h>
int main(){
	int var;
	printf("Enter a integer:");
	fflush(stdin);fflush(stdout);
	scanf("%d",&var);
	printf("You entered:%d",var);
	return 0;}
