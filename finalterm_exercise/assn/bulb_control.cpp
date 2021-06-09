/*
    bulb가 1부터 시작하는 것 주의
*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

int main() {
    int tc;
    scanf("%d", &tc);

    for(int t = 0; t < tc; t++) {
        int n, k;
        scanf("%d %d", &n, &k);

        int clauses[1000][3];
        int count = 0;
        for(int i = 0; i < k; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            if (a == -b || b == -c || c == -a) continue;
            clauses[count][0] = a;
            clauses[count][1] = b;
            clauses[count][2] = c;
            count++;
        }

        bool satisfied;
        for(long long int bulbs = 0; bulbs < (int) pow(2, n); bulbs++) {
            // printf("bulb: %lld\n", bulbs);
            satisfied = 1;
            for(int i = 0; i < count; i++) {
                bool clause0 = bulbs & (1 << (abs(clauses[i][0])-1));
                bool clause1 = bulbs & (1 << (abs(clauses[i][1])-1));
                bool clause2 = bulbs & (1 << (abs(clauses[i][2])-1));
                
                // printf("\tcount: %d, clauses: %d %d %d / %d %d %d\n", i, clauses[i][0], clauses[i][1], clauses[i][2], clause0, clause1, clause2);

                if ((clause0 && clauses[i][0] > 0) || (!clause0 && clauses[i][0] < 0))
                    continue;
                
                if ((clause1 && clauses[i][1] > 0) || (!clause1 && clauses[i][1] < 0))
                    continue;
                
                if ((clause2 && clauses[i][2] > 0) || (!clause2 && clauses[i][2] < 0))
                    continue;
                satisfied = 0;
                break;
            }
            if (satisfied) break;
        }
        if (satisfied) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}