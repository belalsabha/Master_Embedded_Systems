
/*

 * main.c
 *
 *  Created on: 11 Sep 2025
 *

 *      Author: Eng-Belal Hani Sabha
 */




//EX5: C Program to find area of a circle, passing arguments to macros.
#include <stdio.h>


#define PI  3.14
#define AREA (PI * r * r)

int main() {
	float r, area;

	printf("Enter the radius: ");
	scanf("%f", &r);


	area = AREA;

	printf("Area = %.2f\n", area);

	return 0;
}