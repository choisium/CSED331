#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <math.h>

// #define MOD 1000000000
#define MOD 1234567890

using namespace std;

int main() {
    int tc;
    scanf("%d", &tc);

    unsigned long long int t_n;
    unsigned long long int t_n2 = 2;
    unsigned long long int t_n1 = 7;
    unsigned long long int sum = 9;
    unsigned long long int prev_n = 2;
    unsigned long long int n;


    for(int t = 0; t < tc; t++) {
        scanf("%llu", &n);

        if(n == 1) t_n = 2;
        else if (n == 2) t_n = 7;
        else {
            if (prev_n > n) {
                prev_n = 2;
                t_n2 = 2;
                t_n1 = 7;
                sum = 9;
            }
            for(unsigned long long int i = prev_n + 1; i <= n; i++) {
                // printf("i: %lld, t_n2: %lld, t_n1: %lld, sum: %lld\n", i, t_n2, t_n1, sum);
                t_n = (2 * sum + 2 + t_n2) % MOD;
                t_n2 = t_n1;
                t_n1 = t_n;
                sum = (sum += t_n) % MOD;
            }
            prev_n = n;
        }
        printf("%llu\n", t_n);
    }
}