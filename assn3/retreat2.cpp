#include <stdio.h>
#include <vector>
#include <limits.h>
#include <utility>
using namespace std;

typedef struct Bridge {
    int dest;
    unsigned int length;
    bool visited;
    struct Bridge* coupled;
} Bridge;

void explore(int current, int parent, vector<Bridge> graph[], vector<int>& order, vector<int>& root_order, unsigned int& shortest_bridge, int& time) {
    root_order[current] = order[current] = ++time;
    printf("current: %d, parent: %d, order: %d\n", current, parent, time);

    // loop for every adjacent vertices
    for (int i = 0; i < graph[current].size(); i++) {
        Bridge child = graph[current][i];
        Bridge coupled = *(child.coupled);
        printf("loop1 - current: %d, child: %d, visited: %d, length: %d, coupled visited: %d\n", current, child.dest, child.visited, child.length, child.coupled->visited);
        printf("loop2 - coupled: %d, child: %d, visited: %d, length: %d, coupled visited: %d\n", child.dest, coupled.dest, coupled.visited, coupled.length, coupled.coupled->visited);
        // if this edge is already visited(it means from parents), pass it
        if (child.visited) continue;
        // adjacent vertex was never visited
        if (order[child.dest] == INT_MAX) {
            graph[current][i].visited = 1;
            child.visited = 1;
            graph[current][i].coupled->visited = 1;
            coupled.visited = 1;
            printf("explore child - current: %d, child: %d, visited: %d(%d) %d(%d)\n", current, child.dest, child.visited, graph[current][i].visited, coupled.visited, graph[current][i].coupled->visited);
            explore(child.dest, current, graph, order, root_order, shortest_bridge, time);
            printf("explore child end - current: %d(%d), child: %d(%d), visited: %d\n", current, root_order[current], child.dest, root_order[child.dest], child.visited);

            // update root order if child's root order is smaller (it means there was a cycle includes current and child)
            if (root_order[current] >= root_order[child.dest]) {
                root_order[current] = root_order[child.dest];
            }

            // update shortest_bridge
            if (order[current] < root_order[child.dest] && shortest_bridge > child.length) {
                printf("update shortest bridge! current: %d, child: %d\n", current, child.dest);
                shortest_bridge = child.length;
            }
            // Note that there could be multiple edge between current and child
        } else if (root_order[child.dest] < order[current]) {
            printf("update root order: current: %d, child: %d, root_order: %d\n", current, child.dest, root_order[child.dest]);
            root_order[current] = root_order[child.dest];
        }

        // if (order[child.first] == INT_MAX) {
        //     // check if children vertex has backedge
        //     explore(child.first, current, graph, order, root_order, shortest_bridge, time);
        //     // printf("explore children end. current: %d(%d), child: %d(%d)\n", current, root_order[current], child, root_order[child]);

        //     // if there was a cycle includes current and child, child's root_order became smaller.
        //     if (root_order[current] >= root_order[child.first]) {
        //         root_order[current] = root_order[child.first];
        //     }
            
        //     if (order[current] < root_order[child.first] && shortest_bridge > child.second) {
        //         // printf("update shortest bridge! current: %d, child: %d\n", current, child);
        //         shortest_bridge = child.second.length;
        //     }
        // // adjacent vertex was already visited - back edge
        // } else if (child.first != parent && root_order[child.first] < order[current]) {
        //     root_order[current] = root_order[child.first];
        // }
    }
    printf("current: %d, parent: %d end - root_order: %d\n", current, parent, root_order[current]);
}

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);
    
    for(int t = 0; t < testcases; t++) {
        // get the number of vertices and edges
        int n, m;
        scanf("%d %d", &n, &m);

        vector<Bridge> graph[30000];
        vector<int> order(30000, INT_MAX);
        vector<int> root_order(30000, INT_MAX);

        // create graph as adjacency list
        for (int i = 0; i < m; i++) {
            int u, v, l;
            scanf("%d %d %d", &u, &v, &l);
            Bridge b1;
            b1.dest = v;
            b1.length = l;
            b1.visited = 0;
            Bridge b2;
            b2.dest = u;
            b2.length = l;
            b2.visited = 0;
            graph[u].push_back(b1);
            graph[v].push_back(b2);
        }

        unsigned int shortest_bridge = INT_MAX;
        int time = 0;

        for (int i = 0; i < n; i++) {
            printf("%d-th row: ", i);
            for (int j = 0; j < graph[i].size(); j++) {
                Bridge element = graph[i][j];
                printf("%d(l: %d, coupled dest: %d) ", element.dest, element.length, (element.coupled)->dest);
            }
            printf("\n");
        }

        explore(0, -1, graph, order, root_order, shortest_bridge, time);

        if (shortest_bridge == INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", shortest_bridge);
        }
    }
}