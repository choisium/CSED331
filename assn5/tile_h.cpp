#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <math.h>

// #define MOD 1000000000
#define MOD 1234567890

using namespace std;

long long int matrix[3][3] = {{3, 1, -1}, {1, 0, 0}, {0, 1, 0}};

void multiply_matrix(unsigned long long int n, long long int (&res)[3][3]) {
    if (n == 1) {
        res[0][0] = 3;
        res[0][1] = 1;
        res[0][2] = -1;
        res[1][0] = 1;
        res[1][1] = 0;
        res[1][2] = 0;
        res[2][0] = 0;
        res[2][1] = 1;
        res[2][2] = 0;
    } else {
        long long int temp_res[3][3];
        multiply_matrix(n/2, temp_res);

        res[0][0] = (temp_res[0][0] * temp_res[0][0] + temp_res[0][1] * temp_res[1][0] + temp_res[0][2] * temp_res[2][0]) % MOD;
        res[0][1] = (temp_res[0][0] * temp_res[0][1] + temp_res[0][1] * temp_res[1][1] + temp_res[0][2] * temp_res[2][1]) % MOD;
        res[0][2] = (temp_res[0][0] * temp_res[0][2] + temp_res[0][1] * temp_res[1][2] + temp_res[0][2] * temp_res[2][2]) % MOD;
        res[1][0] = (temp_res[1][0] * temp_res[0][0] + temp_res[1][1] * temp_res[1][0] + temp_res[1][2] * temp_res[2][0]) % MOD;
        res[1][1] = (temp_res[1][0] * temp_res[0][1] + temp_res[1][1] * temp_res[1][1] + temp_res[1][2] * temp_res[2][1]) % MOD;
        res[1][2] = (temp_res[1][0] * temp_res[0][2] + temp_res[1][1] * temp_res[1][2] + temp_res[1][2] * temp_res[2][2]) % MOD;
        res[2][0] = (temp_res[2][0] * temp_res[0][0] + temp_res[2][1] * temp_res[1][0] + temp_res[2][2] * temp_res[2][0]) % MOD;
        res[2][1] = (temp_res[2][0] * temp_res[0][1] + temp_res[2][1] * temp_res[1][1] + temp_res[2][2] * temp_res[2][1]) % MOD;
        res[2][2] = (temp_res[2][0] * temp_res[0][2] + temp_res[2][1] * temp_res[1][2] + temp_res[2][2] * temp_res[2][2]) % MOD;

        if (n % 2 == 1) {
            temp_res[0][0] = res[0][0];
            temp_res[0][1] = res[0][1];
            temp_res[0][2] = res[0][2];
            temp_res[1][0] = res[1][0];
            temp_res[1][1] = res[1][1];
            temp_res[1][2] = res[1][2];
            temp_res[2][0] = res[2][0];
            temp_res[2][1] = res[2][1];
            temp_res[2][2] = res[2][2];
            res[0][0] = (temp_res[0][0] * matrix[0][0] + temp_res[0][1] * matrix[1][0] + temp_res[0][2] * matrix[2][0]) % MOD;
            res[0][1] = (temp_res[0][0] * matrix[0][1] + temp_res[0][1] * matrix[1][1] + temp_res[0][2] * matrix[2][1]) % MOD;
            res[0][2] = (temp_res[0][0] * matrix[0][2] + temp_res[0][1] * matrix[1][2] + temp_res[0][2] * matrix[2][2]) % MOD;
            res[1][0] = (temp_res[1][0] * matrix[0][0] + temp_res[1][1] * matrix[1][0] + temp_res[1][2] * matrix[2][0]) % MOD;
            res[1][1] = (temp_res[1][0] * matrix[0][1] + temp_res[1][1] * matrix[1][1] + temp_res[1][2] * matrix[2][1]) % MOD;
            res[1][2] = (temp_res[1][0] * matrix[0][2] + temp_res[1][1] * matrix[1][2] + temp_res[1][2] * matrix[2][2]) % MOD;
            res[2][0] = (temp_res[2][0] * matrix[0][0] + temp_res[2][1] * matrix[1][0] + temp_res[2][2] * matrix[2][0]) % MOD;
            res[2][1] = (temp_res[2][0] * matrix[0][1] + temp_res[2][1] * matrix[1][1] + temp_res[2][2] * matrix[2][1]) % MOD;
            res[2][2] = (temp_res[2][0] * matrix[0][2] + temp_res[2][1] * matrix[1][2] + temp_res[2][2] * matrix[2][2]) % MOD;
        }
    }
}

int main() {
    int tc;
    scanf("%d", &tc);

    for(int t = 0; t < tc; t++) {
        unsigned long long int n;
        scanf("%llu", &n);

        if (n == 1) printf("2\n");
        else if (n == 2) printf("7\n");
        else if (n == 3) printf("22\n");
        else {
            long long int temp_res[3][3];
            multiply_matrix(n - 3, temp_res);
            // for(int i = 0; i < 3; i++) {
            //     for(int j = 0; j < 3; j++) {
            //         printf("%lld ", temp_res[i][j]);
            //     }
            //     printf("\n");
            // }
            long long int t = (temp_res[0][0] * 22 + temp_res[0][1] * 7 + temp_res[0][2] * 2) % MOD;
            printf("%lld\n", t < 0? t + MOD: t);
        }
    }
}