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
        // bool state[21] = {0};

        for(int i = 0; i < k; i++) {
            int s[3];
            scanf("%d %d %d", &s[0], &s[1], &s[2]);
            for(int j = 0; j < 3; j++) {
                clause[i].push_back(s[j]);
            }
        }

        bool flag = 0;
        int state = 0;
        int max = (int) pow(2, n);
        while(state < max) {
            // printf("%d\n", state);
            bool in_flag = 0;
            for(int i = 0; i < k; i++) {
                // check if any one condition is satisfied
                bool check = 0;
                for(int j = 0; j < 3; j++) {
                    int key = abs(clause[i][j]);
                    int value = clause[i][j] > 0;
                    if (((state % (int) pow(2, key) - state % (int) pow(2, key - 1)) > 0) == value) {
                        check = 1;
                        break;
                    }
                }
                if (!check) {
                    // for(int j = 0; j < 3; j++) {
                    //     printf("%d ", clause[i][j]);
                    // }
                    // printf("failed \n");
                    in_flag = 1;
                    break;
                }
                // printf("%d ", i);
            }
            // printf("\n");
            if (!in_flag) {
                flag = 1;
                break;
            }
            state++;
        }
        if (flag) printf("YES\n");
        else printf("NO\n");
    }
}