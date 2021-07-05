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

        queue<Subset > que;
        long long int sum[2] = {0};
        for(int i = 0; i < n; i++) {
            que.push(make_pair(1 << i, value[i]));
            if (value[i] > 0) sum[0] += value[i];
            else sum[1] += value[i];
        }
        
        if ((w > 0 && sum[0] == w) || (w < 0 && sum[1] == w)) {
            printf("YES\n");
        } else if ((w > 0 && sum[0] < w) || (w < 0 && sum[1] < w)) {
            printf("NO\n");
        } else {
            bool satisfy = 0;
            while(!que.empty()) {
                Subset p = que.front();
                que.pop();
                if (p.second == w || (sum[0]+sum[1]-p.second) == w) {
                    // printf("first or second, %d, %d, %d\n", p.first, p.second == w, (sum[0]+sum[1]-p.second) == w);
                    satisfy = 1;
                    break;
                }
                if (p.first >= (long long int) pow(2, n) - 1) {
                    continue;
                }
                for(int i = 0; i < n; i++) {
                    if (p.first & (1 << i)) {
                        continue;
                    }
                    long long int next_value = p.second + value[i];
                    if (next_value == w || (sum[0]+sum[1]-next_value) == w) {
                        // printf("first or second, %d, %d, %d\n", p.first, p.second == w, (sum[0]+sum[1]-p.second) == w);
                        satisfy = 1;
                        break;
                    }
                    que.push(make_pair((p.first | (1 << i)), next_value));
                }
            }
            
            if (satisfy) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
}