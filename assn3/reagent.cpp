#include <stdio.h>
#include <array>
#include <set>
#include <queue>
#include <algorithm>
#include <time.h>
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

void print_status(Status s) {
    printf("---status---\n");
    printf("dist: %d\n", s.dist);
    printf("beakers:\n");
    for(int i = 0; i < 3; i++) {
        printf("  %d: %lld\n", i, s.beaker[i]);
    }
}

void print_changed_status(Status f, Status t) {
    printf("---status---\n");
    printf("dist: %d\t --> dist: %d\n", f.dist, t.dist);
    printf("beakers:\n");
    for(int i = 0; i < 3; i++) {
        printf("  %d: %12lld --> %12lld\n", i, f.beaker[i], t.beaker[i]);
    }

}

int create_adjacent_status(Status const s, set<Status>& history, queue<Status>& q, Status final) {
    Status* new_status;
    for (int i = 0; i < 3; i++) {
        if (s.beaker[i] == 0) continue;

        // check if this beaker is full of right reagent
        // If then, don't move the reagents from this beaker
        int temp = s.beaker[i];
        bool flag = 1;
        while (temp) {
            int digit = temp % 10;
            temp /= 10;
            if (digit != i + 1) {
                flag = 0;
                break;
            }
        }
        if (flag) continue;
        
        // create new status
        for (int j = 1; j <= 2; j++) {
            new_status = new Status();
            int idx = (i + j) % 3;
            int other_idx = (i + 3 - j) % 3;

            new_status->dist = s.dist + 1;

            new_status->beaker[i] = s.beaker[i] / 10;
            new_status->beaker[idx] = s.beaker[idx] * 10 + s.beaker[i] % 10;
            new_status->beaker[other_idx] = s.beaker[other_idx];

            // pass if the new_status are already visited;
            if (*new_status == final) {
                printf("%d\n", new_status->dist);
                return 1;
            }
            if (history.find(*new_status) != history.end())
                continue;
            
            history.insert(*new_status);
            q.push(*new_status);
        }
    }
    return -1;
}

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

        // initialize final status
        final_status.dist = 0;
        final_status.beaker[0] = 0;
        final_status.beaker[1] = 0;
        final_status.beaker[2] = 0;

        // get status and calculate final status
        status.dist = 0;
        for (int i = 0; i < 3; i++) {
            scanf("%lld", &status.beaker[i]);
            int temp = status.beaker[i];
            while (temp != 0) {
                int digit = temp % 10;
                temp /= 10;
                final_status.beaker[digit - 1] = final_status.beaker[digit - 1] * 10 + digit;
            }
        }

        set<Status> history;        // check status duplicate
        queue<Status> q;            // need for bfs

        q.push(status);
        history.insert(status);
        int final_value = -1;

        // clock_t start, end;
        // start = clock();

        while(final_value == -1 && !q.empty()) {
            Status u = q.front();
            q.pop();

            set<Status> A;
            // add new adjacent status for bfs
            int res = create_adjacent_status(u, history, q, final_status);
            if (res == 1) break;

            // for (set<Status>::iterator it = A.begin(); it != A.end(); it++) {
            //     printf("** new adjacent status\n");
            //     print_changed_status(u, *it);

            //     if (*it == final_status) {
            //         // printf("we found final status!\n");
            //         final_value = it->dist;
            //         break;
            //     }

            //     // printf("we inserted new\n");
            //     history.insert(*it);
            //     q.push(*it);
            // }
        }

        // printf("%d\n", final_value);
        // end = clock();
        // printf("%f elapsed\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
}