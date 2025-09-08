/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//EX4_C_Program_to_Calculate_the_Power_of_a_Number_Using_Recursion.
#include<stdio.h>
int find_power(int base,int power_number) {
if(power_number==0)
    return 1;
else if(power_number>0){
        return  base*find_power(base,power_number-1);
    }

}

int main() {
    int base,power_number;
    printf("Enter base  number: ");
    scanf("%d",&base);
    printf("Enter power  number: ");
    scanf("%d",&power_number);
    printf("%d ^ %d = %d : ",base,power_number,find_power(base,power_number));


    return 0;
}

