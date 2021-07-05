#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <math.h>
#include <vector>

using namespace std;

int main() {
    int tc;
    scanf("%d", &tc);
    for(int t = 0; t < tc; t++) {
        int n, m;
        scanf("%d %d", &n, &m);

        int point[3][2000] = {0};
        for(int i = 0; i < n; i++) {
            int cell[2000];
            for(int j = 0; j < m; j++) {
                scanf("%d", &cell[j]);
            }
            for(int j = 0; j < m; j++) {
                if(i == 0 && j == 0) {
                    point[2][j] = cell[j];
                } else if (i == 0) {
                    point[2][j] = point[2][j-1] + cell[j];
                } else if (j == 0) {
                    point[2][j] = point[1][j] + cell[j];
                } else if (i == 1 || j == 1) {
                    point[2][j] = max(point[1][j-1], max(point[1][j], point[2][j-1])) + cell[j];
                } else {
                    point[2][j] = max(point[0][j-2], max(point[1][j-1], max(point[1][j], point[2][j-1]))) + cell[j];
                }
            }
            for(int j = 0; j < m; j++) {
                point[0][j] = point[1][j];
                point[1][j] = point[2][j];
            }
        }

        printf("%d\n", point[2][m-1]); 
    }
}