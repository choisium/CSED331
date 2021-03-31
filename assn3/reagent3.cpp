#include <stdio.h>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <time.h>
#include <string>
#include <iostream>
#include <limits.h>
using namespace std;

typedef struct Status {
    int dist;
    long long int beaker[3];

    bool operator< (const struct Status& s) const {
        if (this->beaker[0] == s.beaker[0]) {
            if (this->beaker[1] == s.beaker[1]) {
                return this->beaker[2] < s.beaker[2];
            }
            return this->beaker[1] < s.beaker[1];
        }
        return this->beaker[0] < s.beaker[0];
    }

    bool operator== (const struct Status& s) const {
        return this->beaker[0] == s.beaker[0] && this->beaker[1] == s.beaker[1] && this->beaker[2] == s.beaker[2];
    }

} Status;

class StatusHashFunction {
public:
    // id is returned as hash function
    size_t operator()(const Status& s) const
    {
        return s.beaker[0]*100+s.beaker[1]*10+s.beaker[2];
    }
};

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);

    for(int t = 0; t < testcases; t++) {
        Status status;
        Status final_status;
        int size[3];
        // get the number of vertices and edges
        scanf("%d %d %d", &size[0], &size[1], &size[2]);
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        // initialize final status
        final_status.dist = 0;
        final_status.beaker[0] = 0;
        final_status.beaker[1] = 0;
        final_status.beaker[2] = 0;

        // get status and calculate final status
        status.dist = 0;
        for (int i = 0; i < 3; i++) {
            string temp_str;
            getline(cin, temp_str);
            if (temp_str.empty()) status.beaker[i] = 0;
            else status.beaker[i] = stoi(temp_str);
            // scanf("%lld", &status.beaker[i]);
            int temp = status.beaker[i];
            while (temp != 0) {
                int digit = temp % 10;
                temp /= 10;
                final_status.beaker[digit - 1] = final_status.beaker[digit - 1] * 10 + digit;
            }
        }

        unordered_set<Status, StatusHashFunction> history;        // check status duplicate
        queue<Status> q;            // need for bfs

        q.push(status);
        bool finish = 0;

        while(!q.empty()) {
            Status u = q.front();
            q.pop();

            // check if this item is same as final status
            if (u == final_status) {
                printf("%d\n", u.dist);
                break;
            }

            // add adjacent status
            for (int i = 0; i < 3; i++) {
                // if beaker is empty, we cannot move any reagent from it.
                if (u.beaker[i] == 0) continue;
                
                // check if this beaker is full of right reagent
                // If then, don't move the reagents from this beaker
                int temp = u.beaker[i];
                bool flag = 1;  // remain 1 when the beaker is full of right reagent
                while (temp) {
                    int digit = temp % 1000;
                    temp /= 1000;
                    if (digit != (i + 1) * 111 || digit != (i + 1) * 11 || digit != i + 1) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) continue;
                
                // create new status
                Status* new_status;
                for (int j = 1; j <= 2; j++) {
                    new_status = new Status();
                    int idx = (i + j) % 3;
                    int other_idx = (i + 3 - j) % 3;

                    new_status->dist = u.dist + 1;

                    // move reagent from i to idx
                    new_status->beaker[i] = u.beaker[i] / 10;
                    new_status->beaker[idx] = u.beaker[idx] * 10 + u.beaker[i] % 10;
                    new_status->beaker[other_idx] = u.beaker[other_idx];

                    // check if this item is same as final status
                    if (*new_status == final_status) {
                        printf("%d\n", new_status->dist);
                        finish = 1;
                        break;
                    }
                    // pass if the new_status are already visited;
                    if (history.find(*new_status) != history.end()) {
                        delete new_status;
                        continue;
                    }
                    
                    history.insert(*new_status);
                    q.push(*new_status);
                }
                if (finish) break;
            }
            if (finish) break;
        }
    }
}