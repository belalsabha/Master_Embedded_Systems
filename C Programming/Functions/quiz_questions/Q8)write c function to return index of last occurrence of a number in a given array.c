/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//Q8)write c function to return index of last occurrence of a number in a given array .
#include <stdio.h>

void findLastOccurrence(int array[], int searchNumber);

int main()
{
    int numbers[10] = {10, 20, 5, 8, 9, 20, 5, 45, 90, 10};
    int searchValue;
    
    printf("Enter your search number: ");
    fflush(stdin); fflush(stdout);
    scanf("%d", &searchValue);
    
    findLastOccurrence(numbers, searchValue);
    
    return 0;
}

void findLastOccurrence(int array[], int searchNumber)
{
    int index, lastFoundIndex = -1; // Initialize to -1 if number not found
    
    for(index = 0; index < 10; index++)
    {
        if(searchNumber == array[index])
        {
            lastFoundIndex = index; // Update with the latest found index
        }
    }
    
    printf("Last occurrence index = %d", lastFoundIndex);
}