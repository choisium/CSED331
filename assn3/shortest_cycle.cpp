#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
using namespace std;

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);
    queue<int> q;
    
    for(int t = 0; t < testcases; t++) {
        // get the number of vertices and edges
        int n, m;
        scanf("%d %d", &n, &m);

        vector<int> graph[1000];

        // create graph as adjacency list
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int shortest_cycle = INT_MAX;

        // do BFS for every vertex
        for (int i = 0; i < n; i++) {
            vector<int> dist(1000, INT_MAX);
            vector<int> prev(1000, -1);

            q.push(i);
            dist[i] = 0;

            // start BFS with root i (like Dijkstra's algorithm)
            while (!q.empty()) {
                int u = q.front();
                q.pop();

                // for all adjacent vertices
                for (int j = 0; j < graph[u].size(); j++) {
                    int v = graph[u][j];

                    // pass already checked cycle
                    if (v < i) continue;

                    // update not visited vertex's distance and prev
                    if (dist[v] == INT_MAX) {
                        dist[v] = dist[u] + 1;
                        prev[v] = u;
                        q.push(v);
                    }
                    // meet a visited vertex, so it has a cycle!
                    else if (prev[v] != u && prev[u] != v) {
                        // note that this cycle length is only valid when this cycle includes i-th vertex.
                        int cycle_length = dist[v] + dist[u] + 1;
                        if (shortest_cycle > cycle_length) {
                            shortest_cycle = cycle_length;
                        }
                    }
                }
            }
        }

        if (shortest_cycle == INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", shortest_cycle);
        }
    }
}


/*
    구현에 옮기진 않았지만, 만약 첫번째 BFS에서 cycle을 찾은 애들에 대해서만 다시 돌리면 되지 않을까?
    그렇게되면 disconnected인지 아닌지 확인하는 걸 또 해야할듯
*/