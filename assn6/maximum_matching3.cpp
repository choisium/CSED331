#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <math.h>
#include <limits.h>

using namespace std;

typedef struct Edge {
    int start_node;
    int end_node;
    int capacity;
    int flow;
} Edge;

typedef struct Node {
    bool visited;
    vector<Edge* > forward_edges;
    vector<Edge* > backward_edges;
} Node;

Node graph[2002];
int node_count;

int dfs(int idx, int flow) {
    // printf("\t%d visited\n", idx);
    if (idx == node_count - 1) {
        return flow;
    }
    Node& node = graph[idx];
    node.visited = true;

    for (int i = 0; i < node.forward_edges.size(); i++) {
        Edge* current_edge = node.forward_edges[i];
        Node& next_node = graph[current_edge->end_node];
        // printf("\t%d - current edge: %d %d\n", i, current_edge->start_node, current_edge->end_node);
        // if next node is sink, return flow
        // if (current_edge->end_node == node_count - 1) {
        //     int available_flow = min(flow, current_edge->capacity - current_edge->flow);
        //     current_edge->flow += available_flow;
        //     // printf("\tmet sink node! available flow: %d\n", available_flow);
        //     if (idx == 0) continue;
        //     return available_flow;
        // }
        // already visited node in this time. don't care.
        if (next_node.visited) continue;
        if (current_edge->capacity - current_edge->flow > 0) {
            int available_flow = dfs(current_edge->end_node, min(flow, current_edge->capacity - current_edge->flow));
            
            if (available_flow > 0) {
                current_edge->flow += available_flow;
                return available_flow;
            }
        }
    }
    for (int i = 0; i < node.backward_edges.size(); i++) {
        Edge* current_edge = node.backward_edges[i];
        // already visited node in this time. don't care.
        if (graph[current_edge->start_node].visited) continue;
        if (current_edge->flow > 0) {
            int available_flow = dfs(current_edge->start_node, min(flow, current_edge->flow));
            
            if (available_flow > 0) {
                current_edge->flow -= available_flow;
                return available_flow;
            }
        }
    }
    return 0;
}

int main() {
    int testcases;
    scanf("%d", &testcases);

    for(int t = 0; t < testcases; t++) {
        int n, m, l;
        scanf("%d %d %d", &n, &m, &l);

        node_count = n + m + 2;

        graph[0].visited = 0;
        graph[0].forward_edges.clear();
        graph[0].forward_edges.shrink_to_fit();
        graph[0].backward_edges.clear();
        graph[0].backward_edges.shrink_to_fit();

        graph[n + m + 1].visited = 0;
        graph[n + m + 1].forward_edges.clear();
        graph[n + m + 1].forward_edges.shrink_to_fit();
        graph[n + m + 1].backward_edges.clear();
        graph[n + m + 1].backward_edges.shrink_to_fit();

        for (int i = 0; i < n; i++) {
            graph[i + 1].visited = 0;
            graph[i + 1].forward_edges.clear();
            graph[i + 1].forward_edges.shrink_to_fit();
            graph[i + 1].backward_edges.clear();
            graph[i + 1].backward_edges.shrink_to_fit();

            Edge* edge = new Edge();
            edge->start_node = 0;
            edge->end_node = i + 1;
            edge->capacity = 1;
            graph[0].forward_edges.push_back(edge);
            graph[i + 1].backward_edges.push_back(edge);
        }

        for (int i = 0; i < m; i++) {
            graph[n + i + 1].visited = 0;
            graph[n + i + 1].forward_edges.clear();
            graph[n + i + 1].forward_edges.shrink_to_fit();
            graph[n + i + 1].backward_edges.clear();
            graph[n + i + 1].backward_edges.shrink_to_fit();

            Edge* edge = new Edge();
            edge->start_node = n + i + 1;
            edge->end_node = n + m + 1;
            edge->capacity = 1;
            graph[n + i + 1].forward_edges.push_back(edge);
            graph[n + m + 1].backward_edges.push_back(edge);
        }

        for (int i = 0; i < l; i++) {
            int u, v;
            scanf("%d %d", &u, &v);

            Edge* edge = new Edge();
            edge->start_node = u + 1;
            edge->end_node = n + v + 1;
            edge->capacity = 1;
            graph[u + 1].forward_edges.push_back(edge);
            graph[n + v + 1].backward_edges.push_back(edge);
        }

        while(true) {
            // printf("start dfs\n");
            // for(int i = 0; i < node_count; i++) {
            //     printf("%d-th node: ", i);
            //     for(int j = 0; j < graph[i].forward_edges.size(); j++) {
            //         printf("%d(%d/%d) ", graph[i].forward_edges[j]->end_node, graph[i].forward_edges[j]->flow, graph[i].forward_edges[j]->capacity);
            //     }
            //     printf("\n");
            // }

            int flow = dfs(0, INT_MAX);
            if (flow == 0) break;
            for(int i = 0; i < node_count; i++) {
                graph[i].visited = false;
            }
        }

        // printf("the end\n");
        // for(int i = 0; i < node_count; i++) {
        //     printf("%d-th node: ", i);
        //     for(int j = 0; j < graph[i].forward_edges.size(); j++) {
        //         printf("%d(%d/%d) ", graph[i].forward_edges[j]->end_node, graph[i].forward_edges[j]->flow, graph[i].forward_edges[j]->capacity);
        //     }
        //     printf("\n");
        // }
        
        int max_flow = 0;
        for(int i = 0; i < graph[node_count-1].backward_edges.size(); i++) {
            max_flow += graph[node_count-1].backward_edges[i]->flow;
        }

        printf("%d\n", max_flow);
    }
}
