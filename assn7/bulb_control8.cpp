#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <limits.h>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <math.h>

using namespace std;


int main(){
    int tc;
    scanf("%d", &tc);

    for (int t = 0; t < tc; t++) {
        int n, k;
        scanf("%d %d", &n, &k);

        vector<int> clause[1000];

        for(register int i = 0; i < k; i++) {
            int s[3];
            scanf("%d %d %d", &s[0], &s[1], &s[2]);
            for(int j = 0; j < 3; j++) {
                clause[i].push_back(s[j]);
            }
        }

        bool flag = 0;
        for(register int state = 0; state < (int) pow(2, n); state++) {
            // printf("%d\n", state);
            bool total_satisfy = 1;
            for(int i = 0; i < k; i++) {
                // printf("check %dth clause\n", i);
                // check if any one condition is satisfied
                bool clause_satisfy = 0;
                for(register int j = 0; j < 3; j++) {
                    int key = abs(clause[i][j]);
                    int value = clause[i][j] > 0;
                    // printf("%d - %d %d %d %d\n", clause[i][j], state, 1 << (key - 1), state & (1 << (key - 1)), value << (key - 1));
                    if ((state & (1 << (key - 1))) == value << (key - 1)) {
                        clause_satisfy = 1;
                        break;
                    }
                }
                if (!clause_satisfy) {
                    // for(int j = 0; j < 3; j++) {
                    //     printf("%d ", clause[i][j]);
                    // }
                    // printf("failed \n");
                    total_satisfy = 0;
                    break;
                }
                // printf("%d ", i);
            }
            // printf("\n");
            if (total_satisfy) {
                // find satisfied state
                flag = 1;
                break;
            }
        }
        if (flag) printf("YES\n");
        else printf("NO\n");
    }
}