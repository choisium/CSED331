#include <stdio.h>
#include <queue>
#include <vector>
#include <utility>
#include <limits.h>
#include <algorithm>
using namespace std;

// weight, n, m
typedef pair<long long int, pair<int, int> > edge;
// dist, prev
typedef pair<long long int, int> vertex;

edge edges[5000];
vertex vertices[1000];

int main() {
    // printf("main\n");
    int tc;
    scanf("%d", &tc);
    
    for (int t = 0; t < tc; t++) {
        int n, m;
        scanf("%d %d", &n, &m);


        for (int i = 0; i < m; i++) {
            // printf("%d input\n", i);
            // unsigned int w;
            // int u, v;
            // scanf("%d %d %d", &u, &v, &w);
            // edges.push_back(make_pair(w, make_pair(u, v)));

            edge& e = edges[i];
            // e.first = w;
            // e.second.first = u;
            // e.second.second = v;
            scanf("%d %d %lld", &e.second.first, &e.second.second, &e.first);
        }

        for (int i = 0; i < n; i++) {
            // vertices.push_back(make_pair(INT_MAX, -1));
            vertices[i].first = INT_MAX;
            vertices[i].second = -1;
        }
        vertices[0].first = 0;
        long long int shortest_path = INT_MAX;

        for(int i = 0; i < n; i++) {
                // printf("%d iteration\n", i);
            for(int j = 0; j < m; j++) {
                edge&e = edges[j];
                // printf("%d %d\n", edges[j].second.first, edges[j].second.second);
                vertex&v = vertices[e.second.first];
                vertex&u = vertices[e.second.second];
                // printf("%lld %lld, %d\n", v.first, u.first, v.first != INT_MAX);

                if (v.first != INT_MAX && u.first > v.first + e.first) {
                    u.first = v.first + e.first;
                    u.second = e.second.first;
                    // printf("%d updated: %d - %lld\n", i, edges[j].second.second, u.first);
                    // if (shortest_path > u.first) {
                    //     shortest_path = u.first;
                    // }
                }
            }
        }

        printf("%lld\n", vertices[n-1].first == INT_MAX? -1 : vertices[n-1].first);
    }

}