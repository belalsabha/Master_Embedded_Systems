
/*

 * main.c
 *
 *  Created on: 11 Sep 2025
 *

 *      Author: Eng-Belal Hani Sabha
 */




/*
EX4 C Program to Store Information ofStudents Using Structure
In this program, a structure(student) is created *ich contains name, roll
and narks as its data Then, an array Of Structure Of is
created. Then, data(nane, roll and marks) for 10 elements is asked to user
and stored in array of structure. Finally, the data entered by user is
displayed.
*/
#include <stdio.h>
#include <string.h>

struct sStudent_info{
	char name[20];

	float marks;


};

int main() {
	struct sStudent_info students[10];
	int number;
	printf("Enter number of students you want to insert their information  :");
	scanf("%d",&number);
	for(int i=0;i<number;i++){
		printf("Enter  information of student with  number roll  %d ",i+1);
		printf(" \nEnter Name :");
		scanf("%s",students[i].name);
		printf(" \nEnter marks :");
		scanf("%f",&students[i].marks);


	}


	printf("\nDisplaying information of students \n ");
	for(int i=0;i<number;i++){
		printf("Information for roll number %d \n Name :%s  \n Marks :%.2f \n ",i+1,students[i].name,students[i].marks);

	}



	return 0;
}

