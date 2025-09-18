

/*

 * main.c
 *
 *  Created on: 8 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */



//Q10 c function to count the max number of ones between two zeros
#include <stdio.h>
void max_ones(int number);

int main() {
    int number;
    printf("enter a number  ");
    scanf("%d",&number);
    max_ones(number);

    return 0;
}
void max_ones(int number) {
    int i;
    for(i=0; number != 0; i++){
        number= number & (number << 1);

}
    printf("max ones between two zeros = %d",i);
}
