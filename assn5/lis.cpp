#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <math.h>

using namespace std;

long long int arr[1000000];

int main() {
    int tc;
    scanf("%d", &tc);

    for(int t = 0; t < tc; t++) {
        int n;
        scanf("%d", &n);

        int max = 0;
        for(int i = 0; i < n; i++) {
            long long int num;
            scanf("%lld", &num);
            // printf("num: %d\n", num);

            if (max == 0) {
                arr[max++] = num;
            }
            else {
                for(int j = max; j >= 0; j--) {
                    if (j != 0 && arr[j - 1] >= num) {
                        continue;
                    }
                    arr[j] = num;
                    max = j == max? j+1: max;
                    break;
                }
            }

            // for(int j = 0; j < max; j++) {
            //     printf("%d ", arr[j]);
            // }
            // printf("\n");
        }
        printf("%d\n", max);
    }
}