/*

 * main.c
 *
 *  Created on: 8 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//Q3 c function to print all prime numbers between two numbers
#include <stdio.h>

int prime_numbers(int num);

int main() {
    int num1, num2, found = 0;

    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    printf("Prime numbers between %d and %d are: ", num1, num2);

    for (int i = num1; i <= num2; i++) {
        if (prime_numbers(i)) {
            printf("%d ", i);
            found++;
        }
    }

    if (found == 0) {
        printf("No prime numbers found");
    }

    return 0;
}

int prime_numbers(int num) {
    
    if (num == 1) {
        return 1;
    }
    if (num <= 0) {
        return 0;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}