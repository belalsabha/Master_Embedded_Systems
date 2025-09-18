
/*

 * main.c
 *
 *  Created on: 11 Sep 2025
 *

 *      Author: Eng-Belal Hani Sabha
 */




//EX2: C Program to Add Two Distances (in inch-feet) System Using Structures
#include <stdio.h>
#include <string.h>

struct sDistances{
	float inch , feet ;


};
struct sDistances Add_Two_Distances(struct sDistances d1 , struct sDistances d2  );

int main() {
	struct  sDistances d1,d2,result;
	printf("Enter information for 1st distance :\nEnter feet:");
	scanf("%f",&d1.feet);
	printf(" \nEnter inch: :");
	scanf("%f",&d1.inch);
	printf("Enter information for 2nt distance :\nEnter feet:");
	scanf("%f",&d2.feet);
	printf(" \nEnter inch: :");
	scanf("%f",&d2.inch);
	result=Add_Two_Distances(d1,d2);
	printf("sum in feet = %.2f :\n sum in inch= %.2f",result.feet,result.inch);
	return 0;
}
struct sDistances Add_Two_Distances(struct sDistances d1 , struct sDistances d2)
{
	struct sDistances sum;
	sum.inch=d1.feet+d2.feet;
	sum.feet=d1.feet+d2.feet;

	return sum;

}





