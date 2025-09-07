/*

 * main.c
 *
 *  Created on: 5 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX3: C Program to Reverse String Without Using Library Function
#include <stdio.h>
#include <string.h>

int main() {
	char words[10],reverse_words[10];

	printf("Enter A String : ");
	scanf("%s",words);
	for (int j=0,i=strlen(words)-1;j<strlen(words);j++,i--) {
		reverse_words[j]=words[i];

	}
	reverse_words[strlen(words)]='\0';
	printf("Before Reversing : %s\nAfter Reversing :%s",words,reverse_words);
	return 0;
}