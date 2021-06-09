#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <limits.h>

using namespace std;

int main() {
    int tc;
    scanf("%d", &tc);
    long long int arr[1000];
    int dp[1000];

    for(int t = 0; t < tc; t++) {
        int n;
        scanf("%d", &n);


        int max = 0;
        for(int i = 0; i < n; i++) {
            scanf("%lld", &arr[i]);
            dp[i] = 1;

            for(int j = 0; j < i; j++) {
                if (arr[j] < arr[i] && dp[j]+1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }

            if (dp[i] > max) max = dp[i];
        }
        printf("%d\n", max);
    }
}