/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//Q1)Write a C program takes string from the user and check if it the same USERNAME or not.
#include <stdio.h>
#include <string.h>
int check_user(char firstString[], char secondString[]);
int main() {
	char username[50]="belal sabha",check_username[50];

	printf("Enter A Username : ");
	gets(check_username);
	fflush(stdin); fflush(stdout);

	if(check_user(username, check_username)==1){
		printf("Same Username");


	}else{
		printf(" Not Same Username");

	}


	return 0;
}

int check_user(char firstString[], char secondString[]){
	for(int i=0;i<strlen(firstString);i++){
		if(firstString[i]==secondString[i])
			continue;
		else
			return 0;

	}
	return 1;
}