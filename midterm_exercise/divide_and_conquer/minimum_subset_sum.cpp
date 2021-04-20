#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <limits.h>
using namespace std;

int main() {
    int tc;
    scanf("%d", &tc);
    int arr[500000];

    for(int t = 0; t < tc; t++) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        int max_so_far = INT_MIN;
        int max_ending_here = 0;

        for(int i = 0; i < n; i++) {
            max_ending_here += arr[i];
            if (max_so_far < max_ending_here) {
                max_so_far = max_ending_here;
            }
            if (max_ending_here < 0) {
                max_ending_here = 0;
            }
        }
        printf("%d\n", max_ending_here);
    }
}