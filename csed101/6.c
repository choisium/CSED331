#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dec2bin(int n);

int main()
{

    int a, b, c;

    a = 0; b = 1; c = 1;

    printf("0. a=%d, b=%d, c=%d\n", a, b, c);

    if(a||b)
        printf("1. a=%d, b=%d, c=%d\n", a, b, c--);
    
    if(c&&b++)
        printf("2. a=%d, b=%d, c=%d\n", a++, b, c);

    if(++a&&b)
        printf("3. a=%d, b=%d, c=%d\n", a, b, ++c);

    printf("4. a=%d, b=%d, c=%d\n", a, b, c);

    return 0;
}
