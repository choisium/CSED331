#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct Edge {
    int start;
    int end;
    bool flow;
} Edge;

typedef struct Node {
    bool visited;
    vector<Edge* > forward_edges;
    vector<Edge* > backward_edges;
} Node;


vector<Node> graph;
int sink;

bool dfs(int idx, int flow) {
    if (idx == sink) return true;
    Node& node = graph[idx];
    node.visited = 1;

    // printf("%d visited\n", idx);
    for(int i = 0; i < node.forward_edges.size(); i++) {
        Edge* edge = node.forward_edges[i];
        if (!edge->flow && !graph[edge->end].visited) {
            bool result = dfs(edge->end, 1);
            if (result) {
                edge->flow = true;
                return true;
            }
        }
    }
    for(int i = 0; i < node.backward_edges.size(); i++) {
        Edge* edge = node.backward_edges[i];
        if (edge->flow && !graph[edge->start].visited) {
            bool result = dfs(edge->start, 1);
            if (result) {
                edge->flow = false;
                return true;
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
        
        sink = n + m + 1;

        // create node
        for(int i = 0; i < n + m + 2; i++) {
            Node node;
            graph.push_back(node);
        }
        
        // add source node
        for(int i = 0; i < n; i++) {
            Edge* edge = new Edge();
            edge->start = 0;
            edge->end = i + 1;
            edge->flow = 0;
            graph[0].forward_edges.push_back(edge);
            graph[i+1].backward_edges.push_back(edge);
        }

        // add sink node
        for(int i = 0; i < m; i++) {
            Edge* edge = new Edge();
            edge->start = n + i + 1;
            edge->end = sink;
            edge->flow = 0;
            graph[n + i + 1].forward_edges.push_back(edge);
            graph[sink].backward_edges.push_back(edge);
        }

        // add edges
        for(int i = 0; i < l; i++) {
            int u, v;
            Edge* edge = new Edge();
            scanf("%d %d", &u, &v);
            edge->start = u + 1;
            edge->end = n + v + 1;
            edge->flow = 0;
            graph[u+1].forward_edges.push_back(edge);
            graph[n+1+v].backward_edges.push_back(edge);
        }

        // printf("%d\n", graph.size());
        // for(int i = 0; i < n + m + 2; i++) {
        //     printf("%d-th vertex: ", i);
        //     for(int j = 0; j < graph[i].forward_edges.size(); j++) {
        //         printf("%d ", graph[i].forward_edges[j]->end);
        //     }
        //     printf("\n");
        // }

        bool flow = true;
        int count = 0;
        while (flow) {
            // printf("start dfs\n");
            flow = dfs(0, 0);
            for(int i = 0; i < n + m + 2; i++) {
                graph[i].visited = false;
            }
            count += 1;

            // for(int i = 0; i < n + m + 2; i++) {
            //     printf("%d-th vertex: ", i);
            //     for(int j = 0; j < graph[i].forward_edges.size(); j++) {
            //         printf("%d(%d) ", graph[i].forward_edges[j]->end, graph[i].forward_edges[j]->flow);
            //     }
            //     printf("\n");
            // }
        }

        Node& sink_node = graph[sink];

        // int count = 0;
        // for(int i = 0; i < sink_node.backward_edges.size(); i++) {
        //     count += sink_node.backward_edges[i]->flow;
        // }
        printf("%d\n", count - 1);

        graph.clear();
        graph.shrink_to_fit();
    }
}