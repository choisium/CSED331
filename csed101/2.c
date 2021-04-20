#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    float x;
    int y;
    srand(time(NULL));
    
    y = rand() % 6 + 1;
    printf("%d\n", y);
    
    x = (float) rand() / RAND_MAX + 1;
    printf("%f\n", x);

    return 0;
}