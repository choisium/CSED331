#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <vector>

using namespace std;

#define MOD 1234567890

void mul(long long int mat[][3], long long int n) {
    if (n == 1) {
        mat[0][0] = 2; mat[0][1] = 1; mat[0][2] = 2;
        mat[1][0] = 1; mat[1][1] = 0; mat[1][2] = 0;
        mat[2][0] = 1; mat[2][1] = 0; mat[2][2] = 1;
        return;
    }
    long long int temp[3][3];
    mul(temp, n/2);
    mat[0][0] = (temp[0][0] * temp[0][0] + temp[0][1] * temp[1][0] + temp[0][2] * temp[2][0]) % MOD;
    mat[0][1] = (temp[0][0] * temp[0][1] + temp[0][1] * temp[1][1] + temp[0][2] * temp[2][1]) % MOD;
    mat[0][2] = (temp[0][0] * temp[0][2] + temp[0][1] * temp[1][2] + temp[0][2] * temp[2][2]) % MOD;
    mat[1][0] = (temp[1][0] * temp[0][0] + temp[1][1] * temp[1][0] + temp[1][2] * temp[2][0]) % MOD;
    mat[1][1] = (temp[1][0] * temp[0][1] + temp[1][1] * temp[1][1] + temp[1][2] * temp[2][1]) % MOD;
    mat[1][2] = (temp[1][0] * temp[0][2] + temp[1][1] * temp[1][2] + temp[1][2] * temp[2][2]) % MOD;
    mat[2][0] = (temp[2][0] * temp[0][0] + temp[2][1] * temp[1][0] + temp[2][2] * temp[2][0]) % MOD;
    mat[2][1] = (temp[2][0] * temp[0][1] + temp[2][1] * temp[1][1] + temp[2][2] * temp[2][1]) % MOD;
    mat[2][2] = (temp[2][0] * temp[0][2] + temp[2][1] * temp[1][2] + temp[2][2] * temp[2][2]) % MOD;
    if (n % 2 == 1) {
        temp[0][0] = mat[0][0]; temp[0][1] = mat[0][1]; temp[0][2] = mat[0][2];
        temp[1][0] = mat[1][0]; temp[1][1] = mat[1][1]; temp[1][2] = mat[1][2];
        temp[2][0] = mat[2][0]; temp[2][1] = mat[2][1]; temp[2][2] = mat[2][2];
        mat[0][0] = (temp[0][0] * 2 + temp[0][1] * 1 + temp[0][2] * 1) % MOD;
        mat[0][1] = (temp[0][0] * 1 + temp[0][1] * 0 + temp[0][2] * 0) % MOD;
        mat[0][2] = (temp[0][0] * 2 + temp[0][1] * 0 + temp[0][2] * 1) % MOD;
        mat[1][0] = (temp[1][0] * 2 + temp[1][1] * 1 + temp[1][2] * 1) % MOD;
        mat[1][1] = (temp[1][0] * 1 + temp[1][1] * 0 + temp[1][2] * 0) % MOD;
        mat[1][2] = (temp[1][0] * 2 + temp[1][1] * 0 + temp[1][2] * 1) % MOD;
        mat[2][0] = (temp[2][0] * 2 + temp[2][1] * 1 + temp[2][2] * 1) % MOD;
        mat[2][1] = (temp[2][0] * 1 + temp[2][1] * 0 + temp[2][2] * 0) % MOD;
        mat[2][2] = (temp[2][0] * 2 + temp[2][1] * 0 + temp[2][2] * 1) % MOD;
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
        mul(mat, n-1);
        result = (mat[0][0] * 2 + mat[0][1] * 1 + mat[0][2] * 1) % MOD;
        printf("%lld\n", result < 0? result + MOD: result);
    }
}