#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <math.h>

using namespace std;

typedef struct Edge {
    int start_node;
    int end_node;
    int capacity;
    int flow;
} Edge;

typedef struct Node {
    int capacity;
    int flow;
    bool visited;
    vector<Edge* > forward_edges;
    vector<Edge* > backward_edges;
} Node;

Node graph[500];
int node_count;

int dfs(int idx, int flow) {
    // printf("\t%d visited\n", idx);
    Node& node = graph[idx];
    node.visited = true;

    int total_added_flow = 0;

    for (int i = 0; i < node.forward_edges.size(); i++) {
        Edge* current_edge = node.forward_edges[i];
        Node& next_node = graph[current_edge->end_node];
        // printf("\t%d - current edge: %d %d\n", i, current_edge->start_node, current_edge->end_node);
        // if next node is sink, return flow
        if (current_edge->end_node == node_count - 1) {
            int available_flow = min(flow, min(current_edge->capacity - current_edge->flow, min(node.capacity - node.flow, next_node.capacity - next_node.flow)));
            node.flow += available_flow;
            next_node.flow += available_flow;
            current_edge->flow += available_flow;
            // printf("\tmet sink node! available flow: %d\n", available_flow);
            if (idx == 0) continue;
            return available_flow;
        }
        // already visited node in this time. don't care.
        if (next_node.visited) continue;
        if (current_edge->capacity - current_edge->flow > 0) {
            int available_flow = dfs(current_edge->end_node, min(flow, min(current_edge->capacity - current_edge->flow, node.capacity - node.flow)));
            
            if (available_flow > 0) {
                node.flow += available_flow;
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
            int available_flow = dfs(current_edge->start_node, min(flow, min(current_edge->flow, node.flow)));
            
            if (available_flow > 0) {
                node.flow -= available_flow;
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
        int m;
        scanf("%d %d", &node_count, &m);

        for(int i = 0; i < node_count; i++) {
            int c;
            scanf("%d", &c);
            graph[i].capacity = c;
            graph[i].flow = 0;
            graph[i].visited = 0;
            graph[i].forward_edges.clear();
            graph[i].forward_edges.shrink_to_fit();
            graph[i].backward_edges.clear();
            graph[i].backward_edges.shrink_to_fit();
        }
        for(int j = 0; j < m; j++) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            Edge* edge = new Edge();
            edge->start_node = u;
            edge->end_node = v;
            edge->capacity = c;
            graph[u].forward_edges.push_back(edge);
            graph[v].backward_edges.push_back(edge);
        }

        // for(int i = 0; i < node_count; i++) {
        //     printf("%d-th node(%d/%d): ", i, graph[i].flow, graph[i].capacity);
        //     for(int j = 0; j < graph[i].forward_edges.size(); j++) {
        //         printf("%d(%d/%d) ", graph[i].forward_edges[j]->end_node, graph[i].forward_edges[j]->flow, graph[i].forward_edges[j]->capacity);
        //     }
        //     printf("\n");
        // }

        while(true) {
            // printf("start dfs\n");
            // for(int i = 0; i < node_count; i++) {
            //     printf("%d-th node(%d/%d): ", i, graph[i].flow, graph[i].capacity);
            //     for(int j = 0; j < graph[i].forward_edges.size(); j++) {
            //         printf("%d(%d/%d) ", graph[i].forward_edges[j]->end_node, graph[i].forward_edges[j]->flow, graph[i].forward_edges[j]->capacity);
            //     }
            //     printf("\n");
            // }

            int flow = dfs(0, graph[0].capacity);
            if (flow == 0) break;
            for(int i = 0; i < node_count; i++) {
                graph[i].visited = false;
            }
        }
        // printf("the end\n");
        // for(int i = 0; i < node_count; i++) {
        //     printf("%d-th node(%d/%d): ", i, graph[i].flow, graph[i].capacity);
        //     for(int j = 0; j < graph[i].forward_edges.size(); j++) {
        //         printf("%d(%d/%d) ", graph[i].forward_edges[j]->end_node, graph[i].forward_edges[j]->flow, graph[i].forward_edges[j]->capacity);
        //     }
        //     printf("\n");
        // }
        printf("%d\n", graph[node_count-1].flow);
    }
}