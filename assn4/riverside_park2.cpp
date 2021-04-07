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
        int i = 1;
        st.push(seg_list[0]);

        while (!st.empty()) {
            segment current;
            // printf("stack size: %lu\n", st.size());
            if (i < n) {
                // printf("i: %d\n", i);
                current = seg_list[i++];
            } else {
                current = st.top();
                st.pop();
            }
            // printf("current: %d %d %d\n", current.first.first, current.first.second, current.second);

            if (st.empty()) {
                // printf("smallest y!\n");
                size = max(size, (long long) w * current.second);
                continue;
            }

            segment prev = st.top();
            // printf("prev: %d %d %d\n", prev.first.first, prev.first.second, prev.second);

            if (prev.second <= current.second) {
                // current y is bigger or equal to top y. push current to stack.
                if (i < n) {
                    // we're pushing to stack!
                    // printf("push!\n");
                    st.push(current);
                } else {
                    // we're popping from stack!
                    // printf("it's end!\n");
                    int y = current.second;
                    int r = w;
                    int l = current.first.first;
                    while (!st.empty()) {
                        prev = st.top();
                        if (prev.second < current.second) break;
                        l = prev.first.first;
                        st.pop();
                    }
                    size = max(size, (r - l) * (long long) y );
                }
            } else {
                // current y is samller than top y. pop top and calculate size of it.
                // printf("pop! %d %d %d\n", prev.first.first, prev.first.second, prev.second);
                st.pop();
                int y = prev.second;
                int r = prev.first.second;
                int l = prev.first.first;
                // check stack and pop until top.second == prev.second
                // Note that stack is in non-decreasing order.
                // top.second must be smaller or equal to prev.second
                while (!st.empty()) {
                    segment top = st.top();
                    if (top.second < prev.second) break;
                    // printf("pop! %d %d %d\n", top.first.first, top.first.second, top.second);
                    l = top.first.first;
                    st.pop();
                }
                // printf("update size from %lld to %lld(%d %d %d)\n", size, (long long) (r - l) * y, r, l, y);
                size = max(size, (r - l) * (long long) y);
                st.push(current);
            }
            // printf("\n");
        }

        printf("%lld\n", size);
        
    }
}
