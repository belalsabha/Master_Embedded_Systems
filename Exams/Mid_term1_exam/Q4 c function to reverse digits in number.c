#include <stdio.h>

int countOnes(int num) {
    int count = 0;
    int i = 0;
    
    while (i < 32) {
        if (num & (1 << i)) {
            count++;
        }
        i++;
    }
    
    return count;
}

int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    
    printf("Number of ones of  %d: %d\n", number,countOnes(number));
    
    return 0;
}