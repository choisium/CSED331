/*
    s, t에 대해선 edge를 한번만 추가해주도록 주의해야 함
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <vector>

using namespace std;

typedef struct Edge {
    int u;
    int v;
    int capacity;
    int flow;
} Edge;

typedef struct Node {
    bool visited;
    vector<Edge*> in_edges;
    vector<Edge*> out_edges;
} Node;

Node graph[2002];
int last;

bool dfs(int node) {
    // printf("\t%d\n", node);
    if (node == last) {
        // printf("found!\n");
        return true;
    }
    graph[node].visited = 1;
    // printf("\tset visited, %d, %d\n", graph[node].out_edges.size(), graph[node].in_edges.size());

    for(int i = 0; i < graph[node].out_edges.size(); i++) {
        Edge* e = graph[node].out_edges[i];
        // printf("\tout: %d\n", e->v);
        if (!graph[e->v].visited && e->capacity > e->flow) {
            bool res = dfs(e->v);
            if (res) {
                e->flow += 1;
                // printf("%d - %d +1\n", node, e->v);
                return true;
            }
        }
    }

    for(int i = 0; i < graph[node].in_edges.size(); i++) {
        Edge* e = graph[node].in_edges[i];
        // printf("\tin: %d\n", e->u);
        if (!graph[e->u].visited && e->flow > 0) {
            bool res = dfs(e->u);
            if (res) {
                e->flow -= 1;
                // printf("%d - %d -1\n", node, e->v);
                return true;
            }
        }
    }

    // printf("\t%d end\n", node);
    return false;
}

void print() {
    for(int i = 0; i <= last; i++) {
        for(int j = 0; j < graph[i].out_edges.size(); j++) {
            printf("\t%d - %d: %d\n", i, graph[i].out_edges[j]->v,graph[i].out_edges[j]->flow);
        }
        printf("\n");
    }
}

int main() {
    int tc;
    scanf("%d", &tc);

    for(int t = 0; t < tc; t++) {
        int n, m, l;
        scanf("%d %d %d", &n, &m, &l);

        last = n+m+1;
        for(int i = 0; i <= last; i++) {
            graph[i].visited=0;
            graph[i].in_edges.clear();
            graph[i].in_edges.shrink_to_fit();
            graph[i].out_edges.clear();
            graph[i].out_edges.shrink_to_fit();
        }
        for (int i = 0; i < n; i++) {
            Edge* e = new Edge();
            e->u = 0;
            e->v = i+1;
            e->capacity = 1;
            e->flow = 0;
            graph[0].out_edges.push_back(e);
            graph[i+1].in_edges.push_back(e);
        }

        for(int i = 0; i < m; i++) {
            Edge* e = new Edge();
            e->u = i+n+1;
            e->v = last;
            e->capacity = 1;
            e->flow = 0;
            graph[i+n+1].out_edges.push_back(e);
            graph[last].in_edges.push_back(e);
        }

        for (int i = 0; i < l; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            // printf("%d %d", u+1, v+n+1);
            Edge* e = new Edge();
            e->u = u+1;
            e->v = v+n+1;
            e->capacity = 1;
            e->flow = 0;
            graph[u+1].out_edges.push_back(e);
            graph[v+n+1].in_edges.push_back(e);
        }

        bool res = true;
        while (res) {
            res = dfs(0);
            // print();
            if (res) {
                for(int i = 0; i <= last; i++) {
                    graph[i].visited=0;
                }
            }
        }
        int flow = 0;
        for(int i = 0; i < graph[0].out_edges.size(); i++) {
            flow += graph[0].out_edges[i]->flow;
        }

        printf("%d\n", flow);
    }
}