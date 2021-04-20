// backjoon 1260

#include <stdio.h>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct Node {
    bool visited;
    int edges[10000];
    int edge_num;
} Node;

Node g[1001];

void dfs(int v) {
    printf("%d ", v);
    g[v].visited = 1;
    for(int i = 0; i < g[v].edge_num; i++) {
        int idx = g[v].edges[i];
        if (!g[idx].visited) {
            dfs(idx);
        }
    }
}

void bfs(int s) {
    // printf("bfs\n");
    queue<int> q;
    q.push(s);
    g[s].visited = 0;

    while(!q.empty()) {
        int v = q.front();
        printf("%d ", v);
        q.pop();
        for (int i = 0; i < g[v].edge_num; i++) {
            int idx = g[v].edges[i];
            // printf("%d visited %d(%d)\n", v, idx, g[idx].visited);
            if (g[idx].visited) {
                g[idx].visited = 0;
                q.push(idx);
            }
        }
    }
}

int main() {
    int n, m, v;
    scanf("%d %d %d", &n, &m, &v);

    for (int i = 0; i < n; i++) {
        g[i + 1].visited = 0;
        g[i + 1].edge_num = 0;
    }
    
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        int idx = g[u].edge_num;
        g[u].edges[idx] = v;
        g[u].edge_num = idx + 1;

        idx = g[v].edge_num;
        g[v].edges[idx] = u;
        g[v].edge_num = idx + 1;
    }

    for (int i = 0; i < n; i++) {
        sort(g[i].edges, g[i].edges + g[i].edge_num);
    }

    dfs(v);
    printf("\n");
    bfs(v);
    printf("\n");

    return 0;
}