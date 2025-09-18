/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//Q2)Swapping Two Arrays with Different Lengths.
#include <stdio.h>
#include <string.h>
void read_Array_Elements(int array[], int length);
void display_Array(int array[], int length);
void exchange_Arrays(int firstArray[], int secondArray[], int Capacity);


int main() {
	int  Capacity = 30;
	int firstArray[30];
	int secondArray[30];
	int firstSize, secondSize;
	printf("Enter size of first array: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &firstSize);

	printf("Enter size of second array: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &secondSize);

	printf("Enter %d elements in first array: ", firstSize);
	read_Array_Elements(firstArray, firstSize);

	printf("Enter %d elements in second array: ", secondSize);
	read_Array_Elements(secondArray, secondSize);


	printf("\n\nFirst array before exchange: ");
	display_Array(firstArray, firstSize);

	printf("\nSecond array before exchange: ");
	display_Array(secondArray, secondSize);

	exchange_Arrays(firstArray, secondArray,Capacity);


	printf("\n\nFirst array after exchange: ");
	display_Array(firstArray, secondSize);

	printf("\nSecond array after exchange: ");
	display_Array(secondArray, firstSize);

	return 0;
}

void read_Array_Elements(int array[], int length)
{
	int counter;
	for(counter = 0; counter < length; counter++)
	{
		scanf("%d", &array[counter]);
	}
}

void display_Array(int array[], int length)
{
	int counter;
	for(counter = 0; counter < length; counter++)
	{
		printf("%d ", array[counter]);
	}
}

void exchange_Arrays(int firstArray[], int secondArray[], int Capacity)
{
	int counter,swap=0;
	for(counter = 0; counter < Capacity; counter++)
	{

		swap=secondArray[counter];
		secondArray[counter]=firstArray[counter];
		firstArray[counter]=swap;


	}
}






