#include <iostream>
#include <ios>
#include <limits>
#include <chrono>
#include <algorithm>
using namespace std;

typedef struct {
    int id;
    int count;
} RACER;

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // create racer array
        RACER* racers = new RACER[c];
        int racer_total = 0;

        bool changedFlag = 0;
        for (int j = 0; j < n * c; j++) {
            int num;
            cin >> num;
            bool findFlag = 0;
            // find the racer number already exists in the array
            // if exists, increase racer's lap count and check if the ranking changed
            // if not exists, update racer id and count
            for (int k = 0; k < racer_total; k++) {
                if (racers[k].id == num) {
                    findFlag = 1;
                    racers[k].count += 1;
                    if (k-1 >= 0 && racers[k-1].count < racers[k].count) {
                        changedFlag = 1;
                    }
                    break;
                }
            }
            if (changedFlag) break;
            if (findFlag == 0) {
                racers[racer_total].id = num;
                racers[racer_total].count = 1;
                racer_total++;
            }
        }
        
        // if ranking changed, print "YES"
        // else print "NO"
        if (changedFlag) 
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        
        delete[] racers;
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}