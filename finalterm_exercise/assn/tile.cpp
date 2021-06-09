/*
    tile half짜리가 n개일 때가 언제를 의미하는지 잘 생각하고 풀어야함
    시간 때문에 약간의 트릭을 써야함
*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

#define ANS 1000000000

int main() {
    int tc;
    scanf("%d", &tc);

    int last_n = 1;
    long long int full[3] = {1, 2, 2};
    long long int half[3] = {0, 1, 1};

    for (int t = 0; t < tc; t++) {
        int n;
        scanf("%d", &n);

        if (last_n > n) {
            last_n = 1;
            full[0] = 1; full[1] = 2; full[2] = 2;
            half[0] = 0; half[1] = 1; half[2] = 1;
        }


        for(int i = last_n + 1; i <= n; i++) {
            full[2] = (full[1] * 2 + full[0] + half[1] * 2) % ANS;
            half[2] = (half[1] + full[1]) % ANS;
            full[0] = full[1];
            full[1] = full[2];
            half[0] = half[1];
            half[1] = half[2];
        }

        printf("%lld\n", full[2]);
        last_n = n;
    }
}