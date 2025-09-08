
/*

 * main.c
 *
 *  Created on: 8 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */



//Q7 c function to sum numbers from 1 to 100(without loop)
#include <stdio.h>
int sum_numbers(int number);

int main() {
    int sum = sum_numbers(100);
    printf("Sum  from 1 to 100=  %d", sum);
    return 0;
}
int sum_numbers(int number) {
    if (number == 0) {
        return 0;
    }
    return number + sum_numbers(number - 1);
}
