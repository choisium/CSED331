// baekjoon 1197

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

// weight, u, v
typedef pair<int, pair<int, int> > edge;

int parent[10001];
priority_queue<edge, vector<edge>, greater<edge> > q;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int count = n;
    
    for(int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        q.push(make_pair(w, make_pair(u, v)));
    }

    int sum = 0;

    while(!q.empty()) {
        edge e = q.top();
        q.pop();

        int pn = find(e.second.first);
        int pm = find(e.second.second);

        if (pn == pm) continue;
        parent[pn] = parent[pm];
        sum += e.first;
    }
    printf("%d\n", sum);
}