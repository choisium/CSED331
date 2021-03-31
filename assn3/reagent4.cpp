#include <stdio.h>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <time.h>
#include <string>
#include <iostream>
#include <limits.h>
using namespace std;

int main() {
    // get the number of testcases
    int testcases;
    scanf("%d", &testcases);

    for(int t = 0; t < testcases; t++) {
        pair<string[3], int> status;
        string final_status[3];
        int size[3];
        // get the number of vertices and edges
        scanf("%d %d %d", &size[0], &size[1], &size[2]);
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        // initialize final status
        final_status[0] = "";
        final_status[1] = "";
        final_status[2] = "";

        // get status and calculate final status
        status.second = 0;
        for (int i = 0; i < 3; i++) {
            getline(cin, status.first[i]);
            string temp = status.first[i];
            while (!temp.empty()) {
                char last_element = temp[temp.size() - 1];
                temp.pop_back();
                final_status[last_element - 49] += last_element;
            }
        }
        // cout << "status: " << status.first[0] << " / " << status.first[1] << " / " << status.first[2] << endl;
        // cout << "fianl : " << final_status[0] << " / " << final_status[1] << " / " << final_status[2] << endl;

        unordered_set<string> history;        // check status duplicate
        queue<pair<string[3], int> > q;            // need for bfs

        q.push(status);
        bool finish = 0;

        while(!q.empty()) {
            pair<string[3], int> u = q.front();
            q.pop();

            // check if this item is same as final status
            if (u.first[0] == final_status[0] && u.first[1] == final_status[1] && u.first[2] == final_status[2]) {
                printf("%d\n", u.second);
                break;
            }

            // add adjacent status
            for (int i = 0; i < 3; i++) {
                // if beaker is empty, we cannot move any reagent from it.
                if (u.first[i].empty()) continue;
                
                // check if this beaker is full of right reagent
                // If then, don't move the reagents from this beaker
                string temp = u.first[i];
                char last_element;
                bool flag = 1;  // remain 1 when the beaker is full of right reagent
                while (temp.size() != 0) {
                    last_element = temp[temp.size() - 1];
                    temp.pop_back();
                    if (last_element != i + 49) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) continue;
                
                // create new status
                for (int j = 1; j <= 2; j++) {
                    pair<string[3], int> new_status;
                    int idx = (i + j) % 3;
                    int other_idx = (i + 3 - j) % 3;

                    new_status.second = u.second + 1;

                    // move reagent from i to idx
                    int bsize = u.first[i].size();
                    char last_char = u.first[i][bsize-1];
                    new_status.first[i] = u.first[i].substr(0, bsize-1);
                    new_status.first[idx] = u.first[idx] + last_char;
                    new_status.first[other_idx] = u.first[other_idx];

                    // pass if the new_status are already visited;
                    string key = new_status.first[0] + "_" + new_status.first[1] + "_" + new_status.first[2];
                    if (history.find(key) != history.end()) {
                        continue;
                    }
                    
                    history.insert(key);
                    q.push(new_status);
                }
                if (finish) break;
            }
            if (finish) break;
        }
    }
}