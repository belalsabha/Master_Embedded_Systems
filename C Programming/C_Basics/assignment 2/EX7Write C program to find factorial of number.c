/*
 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
/*EX7:Write C program to find factorial of number */
#include<stdio.h>
int main(){
	int n,factorial=1;
	printf("Enter An Integer :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	if(n>0)
	{for(int i=1;i<=n;i++){

		factorial*=i;
	}
	printf("factorial=%d",factorial);
	}
	else

		printf(" no factorial for =%d",n);





	return 0;}
