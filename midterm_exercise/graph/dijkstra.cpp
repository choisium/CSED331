// backjoon 1753

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <queue>
#include <limits.h>
#include <vector>
using namespace std;

typedef pair<int, int> edge;

typedef struct Node {
    int dist;
    int prev;
    vector<edge> edges;
    int edge_num;
    bool finish;
} Node;

Node g[20001];

int main() {
    // printf("main!");
    int n, m, k;
    scanf("%d %d", &n, &m);
    scanf("%d", &k);

    for (int i = 1; i <= n; i++) {
        g[i].dist = INT_MAX;
        g[i].prev = -1;
        g[i].edge_num = 0;
        g[i].finish = 0;
    }

    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        g[a].edges.push_back(make_pair(b, w));
        // g[b].edges.push_back(make_pair(a, w));
        g[a].edge_num += 1;
        // g[b].edge_num += 1;
    }

    // for (int i = 1; i <= n; i++) {
    //     printf("%d-th vertex: ", i);
    //     for (int j = 0; j < g[i].edge_num; j++) {
    //         edge e = g[i].edges[j];
    //         printf("%d(%d) ", e.first, e.second);
    //     }
    //     printf("\n");
    // }

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    g[k].dist = 0;
    q.push(make_pair(g[k].dist, k));

    while(!q.empty()) {
        pair<int, int> v = q.top();
        q.pop();
        if (g[v.second].finish) continue;
        g[v.second].finish = 1;
        for (int i = 0; i < g[v.second].edge_num; i++) {
            edge e = g[v.second].edges[i];
            if (g[e.first].dist > g[v.second].dist + e.second) {
                g[e.first].dist = g[v.second].dist + e.second;
                q.push(make_pair(g[e.first].dist, e.first));
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        // printf("%d - %d\n", i, g[i].dist);
        if (g[i].dist == INT_MAX) printf("INF\n");
        else printf("%d\n", g[i].dist);
    }
}