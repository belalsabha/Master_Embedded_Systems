
/*

 * main.c
 *
 *  Created on: 8 Sep 2025
 *
 *
 *
 *
 *      Author: Eng-Belal Hani Sabha
 */




//Q10 c function to count the max number of ones between two zeros
#include <stdio.h>
#include <string.h>

void reverse_words(char str[]);


int main() {

    char str1[] = "belal sabha";
    printf(" %s\n", str1);
    reverseWords(str1);
    printf(" %s\n\n", str1);


    

    return 0;
}







void reverse_words(char str[]) {
    int length = strlen(str);

    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }

    int start = 0;
    for (int i = 0; i <= length; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            for (int j = 0; j < (i - start) / 2; j++) {
                char temp = str[start + j];
                str[start + j] = str[i - j - 1];
                str[i - j - 1] = temp;
            }
            start = i + 1;
        }
    }
}