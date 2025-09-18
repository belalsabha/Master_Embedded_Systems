/*
 * main.c
 *
 *  Created on: 5 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//Exl: C Program to Find the Frequency of Characters in a Strin
#include <stdio.h>
#include <string.h>
int main() {
    char words[30],ch;int i=0;

    printf("Enter A String : ");
    gets(words);
    printf("Enter A Character To Find Frequency : ");
    scanf("%c",&ch);

    for (int j=0;j<strlen(words);j++) {
        if(words[j]==ch){
            i++;
        }
    }
    printf(" Frequency of %c = %d : ",ch,i);
    return 0;
}