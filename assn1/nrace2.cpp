#include <iostream>
#include <ios>
#include <limits>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

int main() {
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    // get the number of testcases
    int t;
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        // get the number of laps(n) and number of cars(c)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int n, c;
        cin >> n >> c;
        
        // create racer map
        map<int, int> racer_map;
        int* ranking = new int[c];
        int total = 0;
        
        bool changedFlag = 0;

        for (int j = 0; j < n * c; j++) {
            int num;
            cin >> num;
            bool findFlag = 0;
            // find the racer number already exists in the array
            // if exists, increase racer's lap count and check if the ranking changed
            // if not exists, update racer id and count
            int* p = find(ranking, ranking + total, num);
            if (p != ranking + total) {
                racer_map[*p] += 1;
                int count = racer_map[*p];
                if (p != ranking) {
                    p--;
                    if (count > racer_map[*p]) {
                        changedFlag = 1;
                        break;
                    }
                }
            } else {
                racer_map[num] = 1;
                ranking[total++] = num;
            }
        }
        
        // if ranking changed, print "YES"
        // else print "NO"
        if (changedFlag) 
            cout << "YES\n";
        else
            cout << "NO\n";
    }


    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}