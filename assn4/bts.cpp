#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
using namespace std;

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);

    pair<unsigned int, unsigned int> amp_list[1000001];
    
    for(int t = 0; t < testcases; t++) {
        // get the number of vertices and edges
        unsigned int n, c, d;
        scanf("%d %d %d", &n, &c, &d);


        // // in order of distance - power / min-heap(deletemin)
        // priority_queue<pair<unsigned int, unsigned int>, vector<pair<unsigned int, unsigned int> >, greater<pair<unsigned int, unsigned int> > > distance_queue;
        // in order of power - distance / max-heap(deletemax)
        priority_queue<pair<unsigned int, unsigned int> > power_queue;

        // create graph as adjacency list
        for (int i = 0; i < n; i++) {
            unsigned int di, pi;
            scanf("%d %d", &di, &pi);

            amp_list[i].first = di;
            amp_list[i].second = pi;
        }
        amp_list[n].first = d;
        amp_list[n].second = 0;

        int coverage = c;
        int count = 0;
        int i = 0;
        
        while (coverage <= d && i <= n) {
            // printf("%d-th try\n", i);
            if (amp_list[i].first <= coverage) {
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
                pair <unsigned int, unsigned int> amplifier = power_queue.top();
                power_queue.pop();
                // printf("pop from power_queue %d, %d\n", amplifier.second, amplifier.first);
                coverage += amplifier.first;
                count += 1;
            }
        }

        printf("%d\n", count);
    }
}
