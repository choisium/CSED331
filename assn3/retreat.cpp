#include <stdio.h>
#include <vector>
#include <limits.h>
#include <utility>
using namespace std;

void explore(int current, int parent, vector<pair <int, unsigned int> > graph[], vector<int>& order, vector<int>& root_order, unsigned int& shortest_bridge, int& time) {
    order[current] = ++time;
    root_order[current] = time;
    // printf("current: %d, parent: %d, order: %d\n", current, parent, time);

    // loop for every adjacent vertices
    for (int i = 0; i < graph[current].size(); i++) {
        pair<int, unsigned int> child = graph[current][i];
        // adjacent vertex was never visited
        if (order[child.first] == INT_MAX) {
            // check if children vertex has backedge
            explore(child.first, current, graph, order, root_order, shortest_bridge, time);
            // printf("explore children end. current: %d(%d), child: %d(%d)\n", current, root_order[current], child, root_order[child]);

            // if there was a cycle includes current and child, child's root_order became smaller.
            if (root_order[current] >= root_order[child.first]) {
                root_order[current] = root_order[child.first];
            }
            
            if (order[current] < root_order[child.first] && shortest_bridge > child.second) {
                // printf("update shortest bridge! current: %d, child: %d\n", current, child);
                shortest_bridge = child.second;
            }
        // adjacent vertex was already visited - back edge
        } else if (child.first != parent && root_order[child.first] < order[current]) {
            root_order[current] = root_order[child.first];
        }
    }
    // printf("current: %d, parent: %d end - root_order: %d\n", current, parent, root_order[current]);
}

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);
    
    for(int t = 0; t < testcases; t++) {
        // get the number of vertices and edges
        int n, m;
        scanf("%d %d", &n, &m);

        vector<pair<int, unsigned int> > graph[30000];
        vector<int> order(30000, INT_MAX);
        vector<int> root_order(30000, INT_MAX);

        // create graph as adjacency list
        for (int i = 0; i < m; i++) {
            int u, v, l;
            scanf("%d %d %d", &u, &v, &l);

            graph[u].push_back(make_pair(v, l));
            graph[v].push_back(make_pair(u, l));
        }

        unsigned int shortest_bridge = INT_MAX;
        int time = 0;

        explore(0, -1, graph, order, root_order, shortest_bridge, time);

        if (shortest_bridge == INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", shortest_bridge);
        }
    }
}