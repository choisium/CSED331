#include <stdio.h>
#include <array>
#include <set>
#include <queue>
#include <algorithm>
#include <time.h>
using namespace std;

typedef struct Status {
    int dist;
    array<long long int, 3> beaker;

    bool operator< (const struct Status& s) const {
        return this->beaker < s.beaker;
    }

    bool operator== (const struct Status& s) const {
        return this->beaker == s.beaker;
    }
} Status;

struct CompareDist {
    bool operator()(Status const& s1, Status const& s2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return s1.dist > s2.dist;
    }
};

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

void create_adjacent_status(Status const s, set<Status>& A, priority_queue<Status, vector<Status>, CompareDist>& q) {
    Status* new_status;
    for (int i = 0; i < 3; i++) {
        if (s.beaker[i] == 0) continue;

        // check if this beaker is full of right reagent
        // If then, don't move the reagents from this beaker
        // long long int temp = s.beaker[i];
        // bool flag = 1;
        // while (temp) {
        //     int digit = temp % 10;
        //     temp /= 10;
        //     if (digit != i + 1) {
        //         flag = 0;
        //         break;
        //     }
        // }
        // if (flag) continue;
        
        // create new status
        for (int j = 1; j <= 2; j++) {
            new_status = new Status();
            int idx = (i + j) % 3;
            int other_idx = (i + 3 - j) % 3;

            int count = 0;
            int move_number = s.beaker[i] % 10;
            new_status->beaker[i] = s.beaker[i];
            new_status->beaker[idx] = s.beaker[idx];
            new_status->beaker[other_idx] = s.beaker[other_idx];

            // if same numbers are in serial, move all of them at one time.
            while (new_status->beaker[i] % 10 == move_number) {
                count += 1;
                new_status->beaker[i] /= 10;
                new_status->beaker[idx] = new_status->beaker[idx] * 10 + move_number;
            }

            new_status->dist = s.dist + count;

            // pass if there are two empty beaker after moving,
            // or if it remove right agents at all, discard it
            if (new_status->beaker[i] == 0 && (move_number == i + 1 || new_status->beaker[other_idx] == 0)) {
                delete new_status;
                continue;
            }
            
            q.push(*new_status);
            A.insert(*new_status);
        }
    }
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
        priority_queue<Status, vector<Status>, CompareDist> q;            // need for bfs

        q.push(status);
        int final_value = -1;

        clock_t start, end;
        start = clock();
        while(final_value == -1 && !q.empty()) {
            Status u = q.top();
            q.pop();
            
            if (history.find(u) != history.end()) {
                continue;
            }
            history.insert(u);

            // printf("** current while **\n");
            // print_status(u);

            if (u == final_status) {
                printf("we found final status!\n");
                final_value = u.dist;
                break;
            }

            set<Status> A;
            create_adjacent_status(u, A, q);


            // // add new adjacent status for bfs
            // create_adjacent_status(u, A, history, q);

            // for (set<Status>::iterator it = A.begin(); it != A.end(); it++) {
            //     printf("** new adjacent status\n");
            //     print_changed_status(u, *it);

            //     if (*it == final_status) {
            //         printf("we found final status!\n");
            //         final_value = it->dist;
            //         break;
            //     }

            //     printf("we inserted new\n");
            //     q.push(*it);
            // }
        }

        printf("%d\n", final_value);
        end = clock();
        printf("%f elapsed\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
}