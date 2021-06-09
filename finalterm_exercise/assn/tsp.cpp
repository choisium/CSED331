/*
    지금까지 방문한 도시(bitmasking), 마지막으로 방문한 도시, 그때까지의 cost
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

// (visited cities, (last city, cost))
typedef pair<long long int, pair<int, long long int> > Path;

int main() {
    int tc;
    scanf("%d", &tc);

    for(int t = 0; t < tc; t++) {
        int n, m;
        scanf("%d %d", &n, &m);

        int graph[12][12];
        for(int i = 0; i < 12; i++) {
            for(int j = 0; j < 12; j++) {
                graph[i][j] = -1;
            }
        }
        for(int i = 0; i < m; i++) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            graph[u][v] = c;
            graph[v][u] = c;
        }

        queue<Path> que;
        long long int last = (int) pow(2, n) - 1;
        long long int mincost = LLONG_MAX;
        que.push(make_pair(1, make_pair(0, 0)));
        while(!que.empty()) {
            Path p = que.front();
            que.pop();
            // printf("%d %d %d\n", p.first, p.second.first, p.second.second);
            if (p.first == last) {
                int c = graph[p.second.first][0];
                if (c == -1) continue;
                mincost = min(p.second.second + c, mincost);
                continue;
            }
            for(int i = 0; i < n; i++) {
                if (p.first & (1 << i)) continue;
                int c = graph[p.second.first][i];
                if (c == -1) continue;
                que.push(make_pair(p.first | (1 << i), make_pair(i, p.second.second + c)));
            }
        }
        printf("%lld\n", mincost == LLONG_MAX? -1: mincost);
    }
}