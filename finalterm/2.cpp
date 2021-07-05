#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <math.h>
#include <vector>
#include <limits.h>

using namespace std;

int main() {
    int tc;
    scanf("%d", &tc);
    for(int t = 0; t < tc; t++) {
        int n, m;
        scanf("%d %d", &n, &m);

        long long int right[2][3000] = {0};
        long long int left[2][3000] = {0};
        for(int i = 0; i < n; i++) {
            long long int cell[3000];
            for(int j = 0; j < m; j++) {
                scanf("%lld", &cell[j]);
                // printf("scanf cell %d %d %lld\n", i, j, cell[j]);
            }
            for(int j = 0; j < m; j++) {
                // printf("right %d\n", j);
                if(i == 0 && j == 0) {
                    right[1][j] = cell[j];
                } else if (i == 0) {
                    right[1][j] = right[1][j-1] + cell[j];
                } else if (j == 0) {
                    right[1][j] = max(right[0][j], left[0][j]) + cell[j];
                } else {
                    right[1][j] = max(right[0][j], max(left[0][j], right[1][j-1])) + cell[j];
                }
            }
            for(int j = m-1; j >= 0; j--) {
                // printf("left %d\n", j);
                if (i == 0) {
                    left[1][j] = LLONG_MIN;
                } else if (j == m-1) {
                    left[1][j] = max(right[0][j], left[0][j]) + cell[j];
                } else {
                    left[1][j] = max(right[0][j], max(left[0][j], left[1][j+1])) + cell[j];
                }
            }
            for(int j = 0; j < m; j++) {
                // printf("move %d\n", j);
                right[0][j] = right[1][j];
                left[0][j] = left[1][j];
            }
        }
        // printf("final\n");
        printf("%lld\n", max(right[1][m-1], left[1][m-1])); 
    }
}