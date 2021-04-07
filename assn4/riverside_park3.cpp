#include <iostream>
#include <vector>
#include <limits.h>
#include <set>
#include <algorithm>
#include <tuple>
#include <stack>
using namespace std;

// (l, r), y
typedef pair<pair<int,int>, int> segment;

// l, r, y
stack<segment> st;
segment seg_list[500000];  // increasing order or l

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);

    
    for(int t = 0; t < testcases; t++) {
        int n, w;
        scanf("%d %d", &n, &w);


        for (int i = 0; i < n; i++) {
            int l, r, y;
            scanf("%d %d %d", &l, &r, &y);
            seg_list[i].first.first = l;
            seg_list[i].first.second = r;
            seg_list[i].second = y;
        }

        long long int size = 0;

        for (int i = 0; i < n; i++) {
            segment current = seg_list[i];
            // printf("%d-th segment: %d %d %d\n", i, current.first.first, current.first.second, current.second);

            if (st.empty() || st.top().second <= current.second) {
                // printf("push!\n");
                st.push(current);
                continue;
            }
            int y, r, l;
            r = current.first.first;
            // printf("previous segment: %d %d %d\n", prev.first.first, prev.first.second, prev.second);
            while(!st.empty()) {
                segment prev = st.top();
                if (prev.second <= current.second) break;
                st.pop();
                y = prev.second;
                l = st.empty()? 0 : st.top().first.second;
                // printf("update size! %lld to %lld(%d %d %d)\n", size,(r - l) * (long long) y, r, l, y);
                size = max(size, (r - l) * (long long) y);
            }
            st.push(current);
        }

        while (!st.empty()) {
            segment current = st.top();
            // printf("stack is not empty: %d %d %d\n", current.first.first, current.first.second, current.second);
            st.pop();
            int y = current.second;
            int r = w;
            int l = st.empty() ? 0 : st.top().first.second;
            // while (!st.empty()) {
            //     current = st.top();
            //     l = current.first.second;
            //     if (current.second < y) break;
            //     st.pop();
            // }
            // if (st.empty()) {
            //     // printf("smallest!");
            //     l = 0;
            // }
            // printf("update size! %lld to %lld(%d %d %d)\n", size,(r - l) * (long long) y, r, l, y);
            size = max(size, (r-l) * (long long) y);
        }

        printf("%lld\n", size);
        
    }
}
