
/*

 * main.c
 *
 *  Created on: 11 Sep 2025
 *

 *      Author: Eng-Belal Hani Sabha
 */




//EX1  C Program to Store Information of a Student Using Structure In this program, a created which contains name, roll and marks as its data member.
#include <stdio.h>
#include <string.h>

struct sStudent_info{
	char name[20];
	int roll ; 
	float marks;


};

int main() {
	struct sStudent_info student_1;
	printf("Enter information of student \nEnter Name :");
	gets(student_1.name);
	printf(" \nEnter roll number :");
	scanf("%d",&student_1.roll);
	printf(" \nEnter marks :");
	scanf("%f",&student_1.marks);
	printf("Displaying information \n Name :%s \n roll number : %d \n marks : %.2f",student_1.name,student_1.roll,student_1.marks);







	return 0;
}

