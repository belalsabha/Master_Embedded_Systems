/*
 * main.c
 *
 *  Created on: 5 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX2: C Program to Find the Length ofa Strign
#include <stdio.h>
int main() {
	char words[10];int len=0;

	printf("Enter A String : ");
	scanf("%s",words);


	for (int j=0;j<10;j++) {
		if(words[j]=='\0')
			break;
		else
			len++;}

	printf(" Length Of %s = %d : ",words,len);
	return 0;
}
