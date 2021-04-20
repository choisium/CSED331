#include <stdio.h>
#include <stdlib.h>

int sum(int n, int m) {
    if (n <= m) 
        return n + sum(n+1, m);
    else
        return 0;
}

int main()
{
    printf("%d\n", sum(3, 6));
}
