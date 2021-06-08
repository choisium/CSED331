#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <limits.h>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

typedef pair<int, pair<int, int> > Clause;

unordered_set<string> cases[2];
// unordered_map<string, unordered_map<int, int> > cases[2];


int main(){
    int tc;
    scanf("%d", &tc);

    for (int t = 0; t < tc; t++) {
        int n, k;
        scanf("%d %d", &n, &k);
        vector<Clause> clauses;

        for(int i = 0; i < k; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            clauses.push_back(make_pair(a, make_pair(b, c)));
        }

        for (int i = 0; i < clauses.size(); i++) {
            unordered_set<string>& old_states = cases[i%2];
            unordered_set<string>& new_states = cases[(i + 1)%2];

            int s[3];
            s[0] = clauses[i].first;
            s[1] = clauses[i].second.first;
            s[2] = clauses[i].second.second;

            // this clause is always true. pass
            if (s[0] == -s[1] || s[0] == -s[2] || s[1] == -s[2]) {
                // printf("%d - always true clause\n", i);
                new_states = old_states;
                old_states.clear();
                continue;
            }

            if (old_states.size() == 0) {
                printf("%d - this is first clause\n", i);
                for (int j = 0; j < 3; j++) {
                    new_states.insert(to_string(s[j]));

                    // for (unordered_map<int, int>::iterator it = new_state.begin(); it != new_state.end(); it++) {
                    //     printf("%d(%d) ", it->first, it->second);
                    // }
                    // printf("\n");
                }
            } else {
                printf("%d - this is new clause\n", i);
                for(unordered_set<string>::iterator old_state = old_states.begin(); old_state != old_states.end(); old_state++) {
                    for (int j = 0; j < 3; j++) {
                        vector<int> state;
                        for(int p = 0; p < old_state->size();) {
                            int a;
                            sscanf(old_state->substr(p, old_state->size() - p).c_str(), "%d", &a);
                            state.push_back(a);
                            // printf("%s(%d) / ", old_state->substr(p, old_state->size() - p).c_str(), p);
                            if (a <= -10) p += 4;
                            else if (a >= 10 || a < 0) p += 3;
                            else p += 2;
                        }
                        for(int p = 0; p < state.size(); p++) {
                            printf("%d ", state[p]);
                        }
                        printf("(%d) -> ", old_state->size());
                        vector<int>::iterator it;
                        it = find(state.begin(), state.end(), s[j]);
                        
                        if (it != state.end())  {
                            // state has s[j]. compatible
                            string key;
                            for(int p = 0; p < state.size(); p++) {
                                key += "_" + to_string(state[p]);
                            }
                            new_states.insert(key.substr(1, key.size() - 1));
                            printf("%s", key.c_str());
                        } else {
                            it = find(state.begin(), state.end(), -s[j]);
                            if (it == state.end()) {
                                // state does not have s[j] and -s[j]. compatible
                                state.push_back(s[j]);
                                sort(state.begin(), state.end());

                                string key;
                                for(int p = 0; p < state.size(); p++) {
                                    key += "_" + to_string(state[p]);
                                }
                                new_states.insert(key.substr(1, key.size() - 1));
                                printf("%s", key.c_str());
                            }
                        }
                        printf("\n");
                    }
                }
            }

            old_states.clear();
            // old_states.shrink_to_fit();

            // for (unordered_set<string>::iterator it = new_states.begin(); it != new_states.end(); it++) {
            //     printf("%s\n", it->c_str());
            // }
        }

        if (cases[clauses.size() % 2].size() == 0) {
            printf("NO\n");
        } else {
            printf("YES\n");
            cases[clauses.size() % 2].clear();
        }

    }
}