#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

// weight, u, v
typedef pair<long long int, pair<int, int> > edge;

typedef struct node {
    long long int dist;
    int prev;
    int finished;
} node;

node graph[501];
edge edges[6000];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        graph[i].dist = LLONG_MAX;
        graph[i].prev = -1;
        graph[i].finished = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        long long int w;
        scanf("%d %d %lld", &u, &v, &w);
        edges[i].first = w;
        edges[i].second.first = u;
        edges[i].second.second = v;
    }

    // for (int i = 1; i <= n; i++) {
    //     printf("%d-th vertex: ", i);
    //     for (int j = 0; j < graph[i].edges.size(); j++) {
    //         printf("%d(%d) ", graph[i].edges[j].first, graph[i].edges[j].second);
    //     }
    //     printf("\n");
    // }
    graph[1].dist = 0;
    bool flag = 0;

    // n-1: for update shortest path / nth: to check it has negative cycle
    for (int i = 0; i <= n; i++) {
        // printf("%d-th iteration\n", i);
        int changed = 0;
        for (int j = 0; j < m; j++) {
            edge e = edges[j];
            node& u = graph[e.second.first];
            node& v = graph[e.second.second];
            if (u.dist != INT_MAX && v.dist > u.dist + e.first) {
                v.dist = u.dist + e.first;
                v.prev = e.second.first;
                changed += 1;
                // printf("%d updated %d to %lld\n", e.second.first, e.second.second, v.dist);
            }
        }
        if (i == n && changed) {
            flag = 1;
        }
    }

    if (flag) printf("-1\n");
    else {
        for(int i = 2; i <= n; i++) {
            printf("%lld\n", graph[i].dist == LLONG_MAX? -1: graph[i].dist);
        }
    }
}