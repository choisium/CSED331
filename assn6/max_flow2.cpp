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

Node graph[1000];
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
        int n, m;
        scanf("%d %d", &n, &m);
        node_count = 2 * n;

        for(int i = 0; i < n; i++) {
            int c;
            scanf("%d", &c);
            // divide a node v to v_in and v_out
            // and there is an edge between them which has the node capacity
            graph[i * 2].visited = 0;
            graph[i * 2].forward_edges.clear();
            graph[i * 2].forward_edges.shrink_to_fit();
            graph[i * 2].backward_edges.clear();
            graph[i * 2].backward_edges.shrink_to_fit();

            graph[i * 2 + 1].visited = 0;
            graph[i * 2 + 1].forward_edges.clear();
            graph[i * 2 + 1].forward_edges.shrink_to_fit();
            graph[i * 2 + 1].backward_edges.clear();
            graph[i * 2 + 1].backward_edges.shrink_to_fit();

            Edge* edge = new Edge();
            edge->start_node = i * 2;
            edge->end_node = i * 2 + 1;
            edge->capacity = c;
            graph[i * 2].forward_edges.push_back(edge);
            graph[i * 2 + 1].backward_edges.push_back(edge);
        }
        for(int j = 0; j < m; j++) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            Edge* edge = new Edge();
            edge->start_node = 2 * u + 1;
            edge->end_node = 2 * v;
            edge->capacity = c;
            graph[2 * u + 1].forward_edges.push_back(edge);
            graph[2 * v].backward_edges.push_back(edge);
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