#include <iostream>
#include <vector>
#include <limits.h>
#include <set>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>
using namespace std;

// weight, (u, v)
typedef pair<long long int, pair<int, int> > Edge;
// store parent of each vertex
int parent[10000];

int find(int x) {
    if (x != parent[x]) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);

    
    for(int t = 0; t < testcases; t++) {
        int n, m;
        scanf("%d %d", &n, &m);
        priority_queue<Edge> q;     // delete max by weight
        unordered_map<int, int> group;  // disjoint set

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            group.insert(make_pair(i, 1));
        }

        for (int i = 0; i < m; i++) {
            int u, v;
            long long int w;
            scanf("%d %d %lld", &u, &v, &w);
            q.push(make_pair(w, make_pair(u, v)));
        }

        long long int sum = 0;
        int comb_count = 0;

        while (!q.empty()) {
            Edge e = q.top();
            q.pop();
            int u_idx, v_idx, u_parent, v_parent;
            u_idx = e.second.first;
            v_idx = e.second.second;

            // printf("Edge: %d %d %d\n", e.first, u_idx, v_idx);

            u_parent = find(u_idx);
            v_parent = find(v_idx);

            // two groups are connected this time!
            if (u_parent != v_parent) {
                // printf("union!\n");
                unordered_map<int, int>::iterator u = group.find(u_parent);
                unordered_map<int, int>::iterator v = group.find(v_parent);
                // printf("Group: %d(%d), %d(%d)\n", u->first, u->second, v->first, v->second);
                // update comb_count
                comb_count += u->second * v->second;
                // union
                group.erase(u_parent);
                group.erase(v_parent);
                group.insert(make_pair(u_parent, u->second + v->second));
                parent[v_parent] = u_parent;
            }
            
            // update sum of cost
            sum = (sum + e.first * comb_count) % (int) pow(10, 9);
            // printf("comb_count: %d, weight: %llu, sum: %lld\n\n", comb_count, e.first, sum);
        }
        printf("%lld\n", sum);
    }
}
