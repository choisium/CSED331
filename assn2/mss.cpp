#include <iostream>
#include <algorithm>
using namespace std;

long long int find_crossing_sum (int arr[], int from, int middle, int to) {
    long long int sum = arr[middle];
    long long int sum_l = sum;
    for (int i = middle - 1; i >= from; i--) {
        sum += arr[i];
        sum_l = max(sum_l, sum);
    }
    sum = arr[middle + 1];
    long long int sum_r = sum;
    for (int i = middle + 2; i <= to; i++) {
        sum += arr[i];
        if (sum > sum_r)
            sum_r = sum;
    }

    return max(max(sum_l, sum_r), sum_l + sum_r);
}

long long int find_mss(int arr[], int from, int to) {
    if (from == to) {  // only one
        return arr[from];
    }

    int middle = (from + to) / 2;

    return max(max(find_mss(arr, from, middle), find_mss(arr, middle + 1, to)), find_crossing_sum(arr, from, middle, to));
}

int main() {
    // get the number of testcases
    int t;
    scanf("%d", &t);

    int arr[500000] = {0};
    
    for(int i = 0; i < t; i++) {
        // get the array size
        int n;
        scanf("%d", &n);

        // get each element of the array
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[j]);
        }

        printf("%lld\n", find_mss(arr, 0, n - 1));
    }
}