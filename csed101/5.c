#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dec2bin(int n);

int main()
{
    int number;
    int result;

    printf("Input the number: ");
    scanf("%d", &number);

    result = dec2bin(number);
    printf("The decimal number %d is represented in binary as %d.\n", number, result);

    return 0;
}

int dec2bin(int n)
{
    if (n <= 1)
        return n;
    else
        return dec2bin(n/2) * 10 + n%2;
}