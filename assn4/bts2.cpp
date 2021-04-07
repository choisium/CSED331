#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);

    pair<long long int, long long int> amp_list[1000001];
    
    for(int t = 0; t < testcases; t++) {
        // get the number of vertices and edges
        long long int n, c, d;
        scanf("%lld %lld %lld", &n, &c, &d);


        // // in order of distance - power / min-heap(deletemin)
        // priority_queue<pair<long long int, long long int>, vector<pair<long long int, long long int> >, greater<pair<long long int, long long int> > > distance_queue;
        // in order of power - distance / max-heap(deletemax)
        priority_queue<pair<long long int, long long int> > power_queue;

        // create graph as adjacency list
        for (int i = 0; i < n; i++) {
            long long int di, pi;
            scanf("%lld %lld", &di, &pi);

            amp_list[i].first = di;
            amp_list[i].second = pi;
        }
        amp_list[n].first = d;
        amp_list[n].second = 0;

        sort(amp_list, amp_list + (n+1));

        long long int coverage = c;
        long long int count = 0;
        long long int i = 0;
        
        while (coverage < d) {
            // printf("%d-th try\n", i);
            if (i <= n && amp_list[i].first <= coverage) {
                // printf("push to power_queue %d, %d\n", amp_list[i].first, amp_list[i].second);
                power_queue.push(make_pair(amp_list[i].second, amp_list[i].first));
                i++;
            } else {
                // printf("check power_queue\n");
                if (power_queue.empty()) {
                    // printf("power_queue is empty!\n");
                    count = -1;
                    break;
                }
                pair <long long int, long long int> amplifier = power_queue.top();
                power_queue.pop();
                // printf("pop from power_queue %d, %d\n", amplifier.second, amplifier.first);
                coverage += amplifier.first;
                count += 1;
            }
        }

        printf("%lld\n", count);
    }
}
