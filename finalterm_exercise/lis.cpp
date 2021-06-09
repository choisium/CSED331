#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <vector>

using namespace std;

int main() {
    int tc;
    scanf("%d", &tc);

    for(int t = 0; t < tc; t++) {
        int n;
        scanf("%d", &n);

        vector<int> seq;
        for(int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);

            if (seq.size() == 0) seq.push_back(a);
            else {
                for (int j = 0; j < seq.size(); j++) {
                    if (seq[j] >= a) {
                        seq[j] = a;
                        break;
                    } else if (j == seq.size() - 1 && seq[j] < a) {
                        seq.push_back(a);
                        break;
                    }
                }
                // for(int j = seq.size() - 1; j > 0; j--) {
                //     if (seq[j] > a && seq[j-1] < a) {
                //         seq[j] = a;
                //     }
                // }
                // if (seq[0] > a) seq[0] = a;
                // else if (seq[seq.size() - 1] < a) seq.push_back(a);
            }
        }
        printf("%d\n", seq.size());
    }
}