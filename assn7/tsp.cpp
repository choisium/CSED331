#include <stdio.h>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <math.h>
#include <limits.h>

using namespace std;

bool operator==(const pair<int, int>& n, const int v) {
    return n.first == v;
}

int main() {
    int tc;
    scanf("%d", &tc);

    for(int t = 0; t < tc; t++) {
        int n, m;
        scanf("%d %d", &n, &m);

        // cost[size - 1] = {<j__set, path length>}
        unordered_map<string, int> cost[12];

        // graph[u] = <v, c>
        unordered_map<int, int> graph[12];
        // vector<pair<int, int> > graph[12];

        for(int i = 0; i < m; i++) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            if (graph[u].find(v) != graph[u].end()) {
                graph[u][v] = min(graph[u][v], c);
                graph[v][u] = min(graph[v][u], c);
            } else {
                graph[u][v] = c;
                graph[v][u] = c;
            }
        }
        
        cost[0].insert(make_pair("0__0", 0));
        for(int size = 2; size <= n; size++) {
            for(int i = 0; i < n; i++) {
                // for (int j = 0; j < graph[i].size(); j++) {
                //     // cost[size-2]에서 j로 끝나고 i가 set에 없는 element를 찾아야 함
                //     // unordered_map<string, int>::iterator it = cost[size-2]
                // }
                for(unordered_map<string, int>::iterator it = cost[size-2].begin(); it != cost[size-2].end(); it++) {
                    // get last_node and node_set from key
                    string key = it->first;
                    int length = it->second;
                    int last_node;
                    vector<int> node_set;

                    // sscanf(key.c_str(), "%d", &last_node);
                    int key_length = key.length();
                    for (int j = 0; j < key_length; ) {
                        int d;
                        sscanf(key.substr(j, key_length - j).c_str(), "%d", &d);
                        // printf("%d: %s - %d\n", j, key.substr(j, key.length() - j).c_str(), d);
                        if (j == 0) {
                            last_node = d;
                            j += 1;
                        } else {
                            node_set.push_back(d);
                        }

                        if (d >= 10) j += 3;
                        else j += 2;
                    }

                    // printf("last_node: %d, length: %d\n", last_node, length);
                    // for (int j = 0; j < node_set.size(); j++) {
                    //     printf("%d ", node_set[j]);
                    // }
                    // printf("\n");

                    // if already included in set, pass
                    vector<int>::iterator test = find(node_set.begin(), node_set.end(), i);
                    if (test != node_set.end()) continue;

                    // if edge exists between last_node and i, compute cost
                    unordered_map<int, int>::iterator edge = graph[i].find(last_node);
                    if(edge != graph[i].end()) {
                        int new_length = length == INT_MAX? length: length + edge->second;
                        string old_key = to_string(last_node) + "_";
                        for(int ch = 0; ch < node_set.size(); ch++) {
                            string app = "_" + to_string(node_set[ch]);
                            old_key += app;
                        }
                        node_set.push_back(i);
                        string zero_key = "0_";
                        string new_key = to_string(i) + "_";
                        sort(node_set.begin(), node_set.end());

                        for(int ch = 0; ch < node_set.size(); ch++) {
                            string app = "_" + to_string(node_set[ch]);
                            new_key += app;
                            zero_key += app;
                        }

                        unordered_map<string, int>::iterator original_cost = cost[size-1].find(new_key);
                        if (original_cost != cost[size-1].end()) {
                            // printf("%d vs %d\n", cost[size-1][new_key], new_length);
                            cost[size-1][new_key] = min(cost[size-1][new_key], new_length);
                        } else {
                            cost[size-1][new_key] = new_length;
                        }
                        cost[size-1][zero_key] = INT_MAX;
                        
                        // printf("%d-%d(%d) found. length: %d -> %d, key: %s -> %s(%d)\n", i, edge->first, edge->second, length, new_length, old_key.c_str(), new_key.c_str(), cost[size-1][new_key]);
                    }
                }
            }
        }

        int min_length = INT_MAX;
        string postfix;
        // for (unordered_map<string, int>::iterator it = cost[n-1].begin(); it != cost[n-1].end(); it++) {
        //     printf("%s - %d\n", it->first.c_str(), it->second);
        // }
        for (int i = 0; i < n; i++) {
            postfix += "_" + to_string(i);
        }
        for (unordered_map<int, int>::iterator edge = graph[0].begin(); edge != graph[0].end(); edge++) {
            string key = to_string(edge->first) + "_" + postfix;
            unordered_map<string, int>::iterator test = cost[n-1].find(key);
            if (test != cost[n-1].end()) {
                min_length = min(min_length, cost[n-1][key] == INT_MAX? cost[n-1][key]: cost[n-1][key] + edge->second);
            }
        }
        // for(int i = 1; i < n; i++) {
        //     unordered_map<int, int>::iterator edge = graph[i].find(0);
        //     if (edge != graph[i].end()) {
        //         string key = to_string(i) + "_" + postfix;
        //         min_length = min(min_length, cost[n-1][key] == INT_MAX? cost[n-1][key]: cost[n-1][key] + edge->second);
        //     }
        // }
        printf("%d\n", min_length == INT_MAX? -1: min_length);

    }
}