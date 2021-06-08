#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <limits.h>
#include <unordered_map>

using namespace std;

typedef pair<int, pair<int, int> > Clause;

vector<unordered_map<int, int> > cases[2];


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
            vector<unordered_map<int, int> >& old_states = cases[i%2];
            vector<unordered_map<int, int> >& new_states = cases[(i + 1)%2];

            int s[3];
            s[0] = clauses[i].first;
            s[1] = clauses[i].second.first;
            s[2] = clauses[i].second.second;

            // this clause is always true. pass
            if (s[0] == -s[1] || s[0] == -s[2] || s[1] == -s[2]) {
                // printf("%d - always true clause\n", i);
                new_states = old_states;
                old_states.clear();
                old_states.shrink_to_fit();
                continue;
            }

            if (old_states.size() == 0) {
                // printf("%d - this is first clause\n", i);
                // it is first valid cluase. Make first cases.
                for (int j = 0; j < 3; j++) {
                    unordered_map<int, int> new_state;
                    if (s[j] > 0) new_state[s[j]] = 1;
                    else new_state[-s[j]] = -1;
                    new_states.push_back(new_state);

                    // for (unordered_map<int, int>::iterator it = new_state.begin(); it != new_state.end(); it++) {
                    //     printf("%d(%d) ", it->first, it->second);
                    // }
                    // printf("\n");
                }
            } else {
                // printf("%d - this is new clause\n", i);
                for (int p = 0; p < old_states.size(); p++) {
                    for (int j = 0; j < 3; j++) {
                        unordered_map<int, int> new_state = old_states[p];
                        unordered_map<int, int>::iterator it;
                        it = new_state.find(abs(s[j]));
                        if (it == new_state.end()) {
                            // printf("%d was not in state\n", s[j]);
                            // for (unordered_map<int, int>::iterator it = new_state.begin(); it != new_state.end(); it++) {
                            //     printf("%d(%d) ", it->first, it->second);
                            // }
                            // printf("-> ");

                            if (s[j] > 0) new_state[s[j]] = 1;
                            else new_state[-s[j]] = -1;
                            new_states.push_back(new_state);

                            // for (unordered_map<int, int>::iterator it = new_state.begin(); it != new_state.end(); it++) {
                            //     printf("%d(%d) ", it->first, it->second);
                            // }
                            // printf("\n");
                        } else {
                            // printf("%d was in state, %d(%d)\n", s[j], it->first, it->second);
                            if ((s[j] * it->second) > 0) {
                                // for (unordered_map<int, int>::iterator it = new_state.begin(); it != new_state.end(); it++) {
                                //     printf("%d(%d) ", it->first, it->second);
                                // }
                                // printf("-> ");
                                
                                new_states.push_back(new_state);

                                // for (unordered_map<int, int>::iterator it = new_state.begin(); it != new_state.end(); it++) {
                                //     printf("%d(%d) ", it->first, it->second);
                                // }
                                // printf("\n");
                            }
                        }
                    }
                }

            }

            old_states.clear();
            old_states.shrink_to_fit();

            for (int j = 0; j < new_states.size(); j++) {
                for (unordered_map<int, int>::iterator it = new_states[j].begin(); it != new_states[j].end(); it++) {
                    printf("%d(%d) ", it->first, it->second);
                }
                printf("\n");
            }
        }

        if (cases[clauses.size() % 2].size() == 0) {
            printf("NO\n");
        } else {
            printf("YES\n");

            cases[clauses.size() % 2].clear();
            cases[clauses.size() % 2].shrink_to_fit();
        }

    }
}