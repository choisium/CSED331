/*
    초기화, 검사 등등을 할 때 항상 2*n 까지 수행해야 함(node가 2배가 됐으니)
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <vector>
#include <math.h>

using namespace std;

typedef struct Edge {
    int u;
    int v;
    int capacity;
    int flow;
} Edge;

typedef struct Node {
    bool visited;
    vector<Edge*> out_edges;
    vector<Edge*> in_edges;
} Node;

Node graph[1000];
int n;

int dfs(int node, int max_flow) {
    if (node == 2*n-1) {
        return max_flow;
    }
    graph[node].visited = 1;

    for(int i = 0; i < graph[node].out_edges.size(); i++) {
        Edge* e = graph[node].out_edges[i];
        if (graph[e->v].visited == 0 && e->capacity > e->flow) {
            int res = dfs(e->v, min(e->capacity - e->flow, max_flow));
            if (res > 0) {
                e->flow += res;
                return res;
            }
        }
    }

    for(int i = 0; i < graph[node].in_edges.size(); i++) {
        Edge* e = graph[node].in_edges[i];
        if (graph[e->u].visited == 0 && e->flow > 0) {
            int res = dfs(e->u, min(e->flow, max_flow));
            if (res > 0) {
                e->flow -= res;
                return res;
            }
        }
    }

    return -1;
}

void print() {
    for(int i = 0; i < 2*n; i++) {
        printf("\t%d\n", i);
        for(int j = 0; j < graph[i].out_edges.size(); j++) {
            printf("\t%d(%d/%d) ", graph[i].out_edges[j]->v, graph[i].out_edges[j]->flow, graph[i].out_edges[j]->capacity);
        }
        printf("\n");
    }
}

int main() {
    int tc;
    scanf("%d", &tc);

    for(int t = 0; t < tc; t++) {
        int m;
        scanf("%d %d", &n, &m);

        for(int i = 0; i < n; i++) {
            graph[2*i].visited = 0;
            graph[2*i].out_edges.clear();
            graph[2*i].out_edges.shrink_to_fit();
            graph[2*i].in_edges.clear();
            graph[2*i].in_edges.shrink_to_fit();
            graph[2*i+1].visited = 0;
            graph[2*i+1].out_edges.clear();
            graph[2*i+1].out_edges.shrink_to_fit();
            graph[2*i+1].in_edges.clear();
            graph[2*i+1].in_edges.shrink_to_fit();

            int c;
            scanf("%d", &c);
            Edge* edge = new Edge();
            edge->u = 2*i;
            edge->v = 2*i+1;
            edge->capacity = c;
            edge->flow = 0;
            graph[2*i].out_edges.push_back(edge);
            graph[2*i+1].in_edges.push_back(edge);
        }

        for(int i = 0; i < m; i++) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            Edge* edge = new Edge();
            edge->u = 2*u+1;
            edge->v = 2*v;
            edge->capacity = c;
            edge->flow = 0;
            graph[2*u+1].out_edges.push_back(edge);
            graph[2*v].in_edges.push_back(edge);
        }

        int res = 1;
        while(res > 0) {
            res = dfs(0, INT_MAX);
            for(int i = 0; i < 2*n; i++) {
                graph[i].visited = 0;
            }
            // printf("\nres %d\n", res);
            // print();
        }
        printf("%d\n", graph[0].out_edges[0]->flow);

    }
}