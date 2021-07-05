#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <limits.h>
#include <utility>
#include <vector>
#include <math.h>

using namespace std;

// first: bitmasking. second: total value
typedef pair<long long int, long long int> Subset;

int main() {
    int tc;
    scanf("%d", &tc);
    for(int t = 0; t < tc; t++) {
        int n;
        long long int w;
        scanf("%d %lld", &n, &w);

        long long int value[20];
        for(int i = 0; i < n; i++) {
            long long int v;
            scanf("%lld", &v);
            value[i] = v;
        }

        bool satisfy = 0;
        for (long long int bit = 0; bit < (long long int) pow(2, n); bit++) {
            long long int sum = 0;
            for (int i = 0; i < n; i++) {
                if (bit & (1 << i)) {
                    sum += value[i];
                }
            }
            if (sum == w) {
                satisfy = 1;
                break;
            }
        }
            
        if (satisfy) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}