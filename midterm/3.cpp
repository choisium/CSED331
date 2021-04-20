#include <stdio.h>
#include <queue>
#include <vector>
#include <utility>
#include <limits.h>
#include <algorithm>
using namespace std;

// distance / price
typedef pair<long long int, long long int> station;

station arr[1000000];

int main() {
    // printf("main\n");
    int tc;
    scanf("%d", &tc);
    
    for (int t = 0; t < tc; t++) {
        int n, l;
        scanf("%d %d", &l, &n);

        for (int i = 0; i < n; i++) {
            scanf("%lld", &arr[i].first);
        }
        for (int i = 0; i < n; i++) {
            scanf("%lld", &arr[i].second);
        }

        // price, distance
        priority_queue<pair<long long int, long long int>, vector<station>, greater<station> > q;
        long long int remain = l;
        long long int sum = 0;
        for(int i = 0; i < n; i++) {
            q.push(make_pair(arr[i].second, arr[i].first));
        }
        while(!q.empty() && remain > 0) {
            station s = q.top();
            q.pop();
            if (remain < s.second) {
                continue;
            }
            sum += s.first * (remain - s.second);
            // printf("price: %lld, distance: %lld, remain: %lld\n", s.first, remain - s.second, remain);
            remain = s.second;
        }

        printf("%lld\n", sum);


    }

}