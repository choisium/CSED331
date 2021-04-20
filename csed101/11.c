#include <stdio.h>

void seq(int i, int *p, int *q);

int main()
{
    int i, p, q;
    for (i = 1; i <= 4; i++)
    {
        p=0; q=0;
        seq(i, &p, &q);
        printf("i=%d, p=%d, q=%d\n", i, p, q);
    }
    
    return 0;
}

void seq(int i, int* p, int* q)
{
    int a;
    int b;
    if (i > 1) {
        seq(i-1, &a, &b);
        *p = 2 * a + b;
        *q = b + a;
    }
    else{
        *p = 2;
        *q = 1;
        return;
    }
}