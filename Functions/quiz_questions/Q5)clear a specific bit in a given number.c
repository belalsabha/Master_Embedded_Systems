/*

 * main.c
 *
 *  Created on: 7 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */
//Q5)clear a specific bit in a given number.
#include <stdio.h>

int main()
{
    int originalNumber, bitPosition, modifiedNumber;

    printf("Enter any number: ");

    scanf("%d", &originalNumber);

    printf("Enter bit position to clear (0-31): ");
    scanf("%d", &bitPosition);

    modifiedNumber = originalNumber & (~(1 << bitPosition));

    printf("Bit cleared successfully.\n\n");
    printf("Number before clearing bit %d: %d (in decimal)\n", bitPosition, originalNumber);
    printf("Number after clearing bit %d: %d (in decimal)\n", bitPosition, modifiedNumber);

    return 0;
}
