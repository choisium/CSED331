#include <stdio.h>
#include <utility>

using namespace std;

typedef pair<int, int> point;

int get_cpp(point l[]) {

}

int main() {
    int testcases;
    scanf("%d", &testcases);

    for (int t = 0; t < testcases; t++) {
        int n;
        point l[100];
        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            l[i].first = x;
            l[i].second = y;
        }

        
    }
}