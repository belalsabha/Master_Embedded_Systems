
/*

 * main.c
 *
 *  Created on: 11 Sep 2025
 *

 *      Author: Eng-Belal Hani Sabha
 */




//EX3: C Program to Add Two Complex Numbers by Passing Structure to aFunction
#include <stdio.h>
#include <string.h>

struct complex_numbers{
	float real , imaginary ;

};
struct complex_numbers Add_Complex_Number(struct complex_numbers d1 ,struct complex_numbers d2 );

int main() {
	struct complex_numbers d1,d2,result;
	printf("Enter information for 1st number :\nEnter real part:");
	scanf("%f",&d1.real);
	printf(" \nEnter imaginary part: :");
	scanf("%f",&d1.imaginary);
	printf("Enter information for 2nd number :\nEnter real part:");
	scanf("%f",&d2.real);
	printf(" \nEnter imaginary part :");
	scanf("%f",&d2.imaginary);
	result=Add_Complex_Number(d1,d2);
	printf("sum = %.2f + %.2fj",result.real,result.imaginary);
	return 0;
}
struct complex_numbers Add_Complex_Number(struct complex_numbers d1 , struct complex_numbers d2)
{
	struct complex_numbers sum;
	sum.real=d1.real+d2.real;
	sum.imaginary=d1.imaginary+d2.imaginary;

	return sum;

}





