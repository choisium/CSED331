#include <iostream>
#include <vector>
#include <limits.h>
#include <set>
#include <algorithm>
#include <tuple>
using namespace std;

typedef pair<pair<int,int>, int> segment;

bool compareY(const segment &a, const segment &b)
{
    return (a.second < b.second);
}

typedef struct compareL2 {
    bool operator() (const segment &a, const segment &b) const
    {
        return (a.first.first < b.first.first);
    }
} compareL2;

bool compareL (const segment &a, const segment &b)
{
    return (a.first.first < b.first.first);
}

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);

    
    for(int t = 0; t < testcases; t++) {
        int n, w;
        scanf("%d %d", &n, &w);

        // l, r, y
        segment seg_list[500000];
        set<segment, compareL2> S;

        for (int i = 0; i < n; i++) {
            int l, r, y;
            scanf("%d %d %d", &l, &r, &y);
            seg_list[i].first.first = l;
            seg_list[i].first.second = r;
            seg_list[i].second = y;
        }

        sort(seg_list, seg_list + n, compareY);
        // printf("sort done\n");

        long long int size = 0;

        for (int i = 0; i < n; i++) {
            segment seg = seg_list[i];
            // printf("%d-th segment, %d, %d, %d\n", i, seg.first.first, seg.first.second, seg.second);

            if (S.empty()) {
                size = seg.second * w;
                S.insert(seg);
            } else {
                pair<set<segment>::iterator, bool> res = S.insert(seg);
                set<segment>::iterator pos, left, right;

                pos = res.first;
                left = pos;
                right = next(pos, 1);
                int left_pos = 0;
                while (left != S.begin()) {
                    left = prev(left, 1);
                    if (left->second < seg.second) {
                        left_pos = left->first.second;
                        break;
                    }
                }
                int right_pos = w;
                while(right != S.end()) {
                    if (right->second < seg.second) {
                        right_pos = right->first.first;
                        break;
                    }
                    right = next(right, 1);
                }

                long long int temp_size = (right_pos - left_pos) * seg.second;
                if (temp_size > size) {
                    size = temp_size;
                }

            }
        }

        printf("%lld\n", size);
        
    }
}
