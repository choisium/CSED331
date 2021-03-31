#include <stdio.h>
#include <vector>
#include <limits.h>
#include <utility>
using namespace std;

typedef struct Edge {
    int idx;
    int node1;
    int node2;
    unsigned int length;
    bool visited;
} Edge;

typedef struct Node {
    int idx;
    int order;
    int root_order;
    vector<Edge *> edge_list;
} Node;

void explore(int current_idx, int parent_idx, Node graph[], unsigned int& shortest_bridge, int& time) {
    Node& current = graph[current_idx];
    current.root_order = current.order = ++time;

    // printf("current start - current: %d, parent: %d, order: %d\n", current_idx, parent_idx, current.order);

    for (unsigned int i = 0; i < current.edge_list.size(); i++) {
        Edge* e = current.edge_list[i];
        Node& child = graph[e->node1 == current_idx? e->node2: e->node1];
        // printf("loop - current: %d, child: %d, visited: %d\n", current_idx, child.idx, e->visited);

        // if this edge is already visited, it came from parent. Pass it.
        if (e->visited) continue;
        e->visited = 1;

        // this adjacent vertex was never been visited
        if (child.order == INT_MAX) {
            // printf("explore child - current: %d, child: %d, visited: %d(%d)\n", current_idx, child.idx, e->visited, graph[current_idx].edge_list[i]->visited);
            explore(child.idx, current_idx, graph, shortest_bridge, time);
            // printf("explore child end - current: %d, child: %d, visited: %d\n", current_idx, child.idx, e->visited);
        }
        // update root order if child's root order is smaller than current one
        if (current.root_order > child.root_order) {
            current.root_order = child.root_order;
        }

        // update shortest bridge
        if (current.order < child.root_order && shortest_bridge > e->length) {
            shortest_bridge = e->length;
        }
        // } else if (current.order > child.root_order) {
        //     // printf("update root order: current: %d, child: %d, root_order: %d\n", current_idx, child.idx, child.root_order);
        //     current.root_order = child.root_order;
        // }
    }

    // printf("current end - current: %d, parent: %d, root_order: %d\n", current_idx, parent_idx, current.root_order);
}

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);
    
    for(int t = 0; t < testcases; t++) {
        // get the number of vertices and edges
        int n, m;
        scanf("%d %d", &n, &m);

        Node graph[30000];

        for (int i = 0; i < n; i++) {
            graph[i].idx = i;
            graph[i].order = INT_MAX;
            graph[i].root_order = INT_MAX;
            // printf("%d - %lud\n", i, graph[i].edge_list.size());
            for (int j = 0; j < graph[i].edge_list.size(); j++) {
                delete graph[i].edge_list[j];
            }
            graph[i].edge_list.clear();
            graph[i].edge_list.shrink_to_fit();
        }

        int idx = 0;
        Edge* e;
        // create graph as adjacency list
        for (int i = 0; i < m; i++) {
            int u, v, l;
            scanf("%d %d %d", &u, &v, &l);
            e = new Edge();
            e->idx = idx++;
            e->node1 = u;
            e->node2 = v;
            e->length = l;
            e->visited = 0;
            graph[u].edge_list.push_back(e);
            graph[v].edge_list.push_back(e);
        }

        unsigned int shortest_bridge = INT_MAX;
        int time = 0;

        // for (int i = 0; i < n; i++) {
        //     printf("%d-th row: ", i);
        //     vector<Edge*> edges = graph[i].edge_list;
        //     for (int j = 0; j < edges.size(); j++) {
        //         Edge e = *edges[j];
        //         printf("%d-%d(l: %d) ", e.node1, e.node2, e.length);
        //     }
        //     printf("\n");
        // }

        explore(0, -1, graph, shortest_bridge, time);

        if (shortest_bridge == INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", shortest_bridge);
        }
    }
}