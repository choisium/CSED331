#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

int match_n[1000];
int match_m[1000];

vector<int> edges_n[1000];
vector<int> edges_m[1000];
bool checked[1000];

bool dfs(int idx, int original_idx_m) {
    // printf("%d visited\n", idx);
    checked[idx] = true;
    
    // find match for idx in n
    for(int j = 0; j < edges_n[idx].size(); j++) {
        int idx_m = edges_n[idx][j];
        // if (idx_m == original_idx_m)
        //     continue;
        if (match_m[idx_m] == -1) {
            // the opposite has no match
            match_n[idx] = idx_m;
            match_m[idx_m] = idx;
            return true;
        } else if (!checked[match_n[idx_m]]) {
            bool match = dfs(match_n[idx_m], idx_m);
            if (match) {
                // the opposite can change its match
                match_n[idx] = idx_m;
                match_m[idx_m] = idx;
                return true;
            }
        }
    }
    return false;
}


int main() {
    int testcases;
    scanf("%d", &testcases);

    for(int t = 0; t < testcases; t++) {
        int n, m, l;
        scanf("%d %d %d", &n, &m, &l);

        for (int i = 0; i < n; i++) {
            edges_n[i].clear();
            edges_n[i].shrink_to_fit();
        }

        // add edges
        for(int i = 0; i < l; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            edges_n[u].push_back(v);
            edges_m[v].push_back(u);
        }

        int count = 0;
        fill_n(checked, n, 0);
        for(int i = 0; i < n; i++) {
            fill_n(match_n, n, -1);
            fill_n(match_m, m, -1);
            count += dfs(i, -1);
        }

        printf("%d\n", count);
    }
}