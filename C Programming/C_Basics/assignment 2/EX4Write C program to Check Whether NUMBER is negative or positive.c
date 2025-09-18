 * main.c
 *
 *  Created on: 3 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
/*EX4:Write C program to Check Whether NUMBER is negative or positive */
#include<stdio.h>
int main(){
	float var1;
	printf("Enter A Number :");
	fflush(stdin);fflush(stdout);
	scanf("%f",&var1);

	if(var1>0)
		printf(" Number %f is positive ",var1);
	else if (var1<0)
		printf(" Number %f is negative ",var1);
	else
		printf(" YOu Entered Zero ",var1);


	return 0;}