#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void putch (char c) {
    printf("%c", c);
}

int main()
{
    int i, j;

    for (i = 0; i<11; i++) {
        if (i < 5) {
            for (j = 0; j < 5; j++) {
                if (j >= 4-i) putch('*');
                else putch(' ');
            }
            putch(' ');
            for (j = 0; j < 5; j++) {
                if (j <= i) putch('*');
                else putch(' ');
            }
            putch('\n');
        }
        else if (i > 5) {
            for (j = 0; j < 5; j++) {
                if (j > i - 7) putch('*');
                else putch(' ');
            }
            putch(' ');
            for (j = 0; j < 5; j++) {
                if (j < 11 - i) putch('*');
                else putch(' ');
            }
            putch('\n');
        }
        else
            putch('\n');
    }
    return 0;
}