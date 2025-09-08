
/*

 * main.c
 *
 *  Created on: 8 Sep 2025
 *      Author: Eng-Belal Hani Sabha
 */

#include <stdio.h>


// Q2 c function to take an integer number and calculate it's square root
#include <stdio.h>


float square_root(int number);


int main()
{
    int number;
    printf("enter a number");
    scanf("%d",&number);



    printf("your square root for %d = %f ",number, square_root(number));
    return 0;
}
float square_root(int number)
{
    int b,a = 0, z = number,i=0;
    float ans,counter= 0.1;

    while (a <= z) {

        b = (a + z) / 2;

        if (b * b == number) {
            ans = b;
            break;
        }

        if (b * b < number) {
            ans=a;
            a = b + 1;
        }


        else {
            z= b - 1;
        }
    }



    while ( i < 5) {
        while (ans * ans <= number) {
            ans += counter;
        }

        ans = ans - counter;
        counter = counter / 10;
        i++;
    }
    return ans;
}

