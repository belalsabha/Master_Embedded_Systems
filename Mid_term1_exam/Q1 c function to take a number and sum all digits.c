/*
 * main.c
 *
 * Created on: 8 Sep 2025
 * Author: Eng-Belal Hani Sabha
 */
 
// C function to take a number and sum all digits
#include <stdio.h>

int sum_digits(int num); 
int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    int sum = sum_digits(number);
    printf("Sum of digits: %d", sum);
    
    return 0;
}
int sum_digits(int num); {
    int sum = 0;
    
    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}
