// backjoon 1931

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;
// finished time / start time
typedef pair<unsigned int, unsigned int> interval;

interval meetings[100000];

int main() {
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        unsigned int s, f;
        scanf("%d %d", &s, &f);
        meetings[i].first = f;
        meetings[i].second = s;
    }

    sort(meetings, meetings+n);
    int count = 0;
    unsigned int last_finish = 0;
    for(int i = 0; i < n; i++) {
        interval meeting = meetings[i];
        if (meeting.second >= last_finish) {
            count += 1;
            last_finish = meeting.first;
        }
    }

    printf("%d\n", count);
}