#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int split_one(int n) {
    return n % 10;
}

int split_ten(int n) {
    return (n / 10) % 10;
}

int split_hundred(int n) {
    return (n / 100) % 10;
}

void split(int n, int* one, int* ten, int* hundred) {
    *one = split_one(n);
    *ten = split_ten(n);
    *hundred = split_hundred(n);
}

int main()
{
    int one, ten, hundred;
    int n = 123;

    split (n, &one, &ten, &hundred);

    printf("%d = %d*1 + %d*10 + %d*100\n", n, one, ten, hundred);
    printf("%d = %d*1 + %d*10 + %d*100\n", n, split_one(n), split_ten(n), split_hundred(n));

    return 0;
}