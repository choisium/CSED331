/*
    마지막에 print할 때 % 연산 결과가 -인 경우 주의
    n도 long long int여야함!!!!
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <vector>

#define ANS 1234567890

using namespace std;

void mul(long long int m[][3], long long int n) {
    if (n == 1) {
        m[0][0] = 2; m[0][1] = 2; m[0][2] = 1;
        m[1][0] = 1; m[1][1] = 1; m[1][2] = 0;
        m[2][0] = 1; m[2][1] = 0; m[2][2] = 0;
    } else {
        long long int temp[3][3];
        mul(temp, n/2);
        m[0][0] = (temp[0][0] * temp[0][0] + temp[0][1] * temp[1][0] + temp[0][2] * temp[2][0]) % ANS;
        m[0][1] = (temp[0][0] * temp[0][1] + temp[0][1] * temp[1][1] + temp[0][2] * temp[2][1]) % ANS;
        m[0][2] = (temp[0][0] * temp[0][2] + temp[0][1] * temp[1][2] + temp[0][2] * temp[2][2]) % ANS;
        m[1][0] = (temp[1][0] * temp[0][0] + temp[1][1] * temp[1][0] + temp[1][2] * temp[2][0]) % ANS;
        m[1][1] = (temp[1][0] * temp[0][1] + temp[1][1] * temp[1][1] + temp[1][2] * temp[2][1]) % ANS;
        m[1][2] = (temp[1][0] * temp[0][2] + temp[1][1] * temp[1][2] + temp[1][2] * temp[2][2]) % ANS;
        m[2][0] = (temp[2][0] * temp[0][0] + temp[2][1] * temp[1][0] + temp[2][2] * temp[2][0]) % ANS;
        m[2][1] = (temp[2][0] * temp[0][1] + temp[2][1] * temp[1][1] + temp[2][2] * temp[2][1]) % ANS;
        m[2][2] = (temp[2][0] * temp[0][2] + temp[2][1] * temp[1][2] + temp[2][2] * temp[2][2]) % ANS;
        if (n % 2) {
            temp[0][0] = m[0][0]; temp[0][1] = m[0][1]; temp[0][2] = m[0][2];
            temp[1][0] = m[1][0]; temp[1][1] = m[1][1]; temp[1][2] = m[1][2];
            temp[2][0] = m[2][0]; temp[2][1] = m[2][1]; temp[2][2] = m[2][2];
            m[0][0] = (temp[0][0] * 2 + temp[0][1] * 1 + temp[0][2] * 1) % ANS;
            m[0][1] = (temp[0][0] * 2 + temp[0][1] * 1 + temp[0][2] * 0) % ANS;
            m[0][2] = (temp[0][0] * 1 + temp[0][1] * 0 + temp[0][2] * 0) % ANS;
            m[1][0] = (temp[1][0] * 2 + temp[1][1] * 1 + temp[1][2] * 1) % ANS;
            m[1][1] = (temp[1][0] * 2 + temp[1][1] * 1 + temp[1][2] * 0) % ANS;
            m[1][2] = (temp[1][0] * 1 + temp[1][1] * 0 + temp[1][2] * 0) % ANS;
            m[2][0] = (temp[2][0] * 2 + temp[2][1] * 1 + temp[2][2] * 1) % ANS;
            m[2][1] = (temp[2][0] * 2 + temp[2][1] * 1 + temp[2][2] * 0) % ANS;
            m[2][2] = (temp[2][0] * 1 + temp[2][1] * 0 + temp[2][2] * 0) % ANS;
        }
    }
}

int main() {
    int tc;
    scanf("%d", &tc);

    for(int t = 0; t < tc; t++) {
        long long int n;
        scanf("%lld", &n);
        
        if (n == 1) {
            printf("2\n");
            continue;
        }
        long long int mat[3][3], result;
        mul(mat, n - 1);
        result = (mat[0][0] * 2 + mat[0][1] * 1 + mat[0][2] * 1) % ANS;
        if (result < 0) result += ANS;
        printf("%lld\n", result);
    }
}