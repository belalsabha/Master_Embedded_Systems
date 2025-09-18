/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
/*EX6:Write C program to calculate sum of natural numbers */
#include<stdio.h>
int main(){
	int n,sum=0;
	printf("Enter An Integer :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	for(int i=0;i<=n;i++){
		sum+=i;
	}


	printf("sum=%d",sum);


	return 0;}
