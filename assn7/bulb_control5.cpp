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


int main(){
    int tc;
    scanf("%d", &tc);

    for (int t = 0; t < tc; t++) {
        int n, k;
        scanf("%d %d", &n, &k);

        unordered_set<int> bulb_on_set[21];
        unordered_set<int> bulb_off_set[21];
        bool state[21] = {0};

        for(int i = 0; i < k; i++) {
            int s[3];
            scanf("%d %d %d", &s[0], &s[1], &s[2]);
            for(int j = 0; j < 3; j++) {
                if (s[j] > 0) bulb_on_set[s[j]].insert(i);
                else bulb_off_set[-s[j]].insert(i);
            }
        }

        // for(int i = 1; i <= n; i++) {
        //     printf("bulb %d\n", i);
        //     printf("\ton(%d) - ", bulb_on_set[i].size());
        //     for(unordered_set<int>::iterator it = bulb_on_set[i].begin(); it != bulb_on_set[i].end(); it++) {
        //         printf("%d ", *it);
        //     }
        //     printf("\n\toff(%d) - ", bulb_off_set[i].size());
        //     for(unordered_set<int>::iterator it = bulb_off_set[i].begin(); it != bulb_off_set[i].end(); it++) {
        //         printf("%d ", *it);
        //     }
        //     printf("\n");
        // }

        bool flag = 0;
        while(state[20-n] == 0) {
            // for(int i = 20-n; i <= 20; i++) {
            //     printf("%d", state[i]);
            // }
            // printf("\n");

            unordered_set<int> test_set;
            for(int i = 0; i < n; i++) {
                unordered_set<int> tmp;
                if (state[20-i]) {
                    set_union(test_set.begin(), test_set.end(), bulb_on_set[i].begin(), bulb_on_set[i].end(), inserter(tmp, tmp.begin()));
                } else {
                    set_union(test_set.begin(), test_set.end(), bulb_off_set[i].begin(), bulb_off_set[i].end(), inserter(tmp, tmp.begin()));
                }
                test_set = tmp;
            }
            // printf("\t%d\n", test_set.size());
            if (test_set.size() == n) {
                flag = 1;
                break;
            }

            int bit = 20;
            bool in_carry = 1, out_carry = 0;
            while(in_carry) {
                out_carry = state[bit] & in_carry;
                state[bit] = state[bit] ^ in_carry;
                in_carry = out_carry;
                bit--;
            }
        }
        if (flag) printf("YES\n");
        else printf("NO\n");
    }
}