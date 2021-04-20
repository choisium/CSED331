#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char grade(float score, int absence, int tardy) {
    absence += tardy/3;
    if (absence < 3) {
        if(score >= 90.0) {
            return 'A';
        }
        else if (score >= 80.0) {
            return 'B';
        }
        else if (score >= 70.0) {
            return 'C';
        }
        else if (score >= 60.0) {
            return 'D';
        }
        else {
            return 'F';
        }
    } else {
        return 'F';
    }
}

char grade2(float score, int absence, int tardy) {
    absence += tardy/3;
    switch (absence / 3) {
        case 0: break;
        default: return 'F';
    }
    switch ((int) score / 10) {
        case 9: return 'A';
        case 8: return 'B';
        case 7: return 'C';
        case 6: return 'D';
        default: return 'F';
    }
}

int main()
{
    float score;
    int absence, tardy;

    score = 75; absence = 0; tardy = 2;
    printf("compare score: %c vs %c\n", grade(score, absence, tardy), grade2(score, absence, tardy));

    score = 83; absence = 1; tardy = 3;
    printf("compare score: %c vs %c\n", grade(score, absence, tardy), grade2(score, absence, tardy));

    score = 92; absence = 2; tardy = 3;
    printf("compare score: %c vs %c\n", grade(score, absence, tardy), grade2(score, absence, tardy));

    score = 40; absence = 0; tardy = 1;
    printf("compare score: %c vs %c\n", grade(score, absence, tardy), grade2(score, absence, tardy));

    return 0;
}
