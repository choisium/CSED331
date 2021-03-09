#include <iostream>
#include <ios>
#include <limits>
#include <map>
#include <algorithm>
using namespace std;

typedef struct {
    int id;
    int count;
} RACER;

int main() {
    // get the number of testcases
    int t;
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        // get the number of laps(n) and number of cars(c)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int n, c;
        cin >> n >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // create driver array
        map<int, int> drivers;
        int* lapcount = new int[c];
        int total = 0;
        bool changedFlag = 0;
        for (int j = 0; j < n * c; j++) {
            int num;
            cin >> num;
            map<int,int>::iterator itr = drivers.find(num);
            if (itr != drivers.end()) {
                int idx = itr->second;
                lapcount[idx] += 1;
                if (idx != 0) {
                    if (lapcount[idx - 1] < lapcount[idx]) {
                        changedFlag = 1;
                    }
                }
            } else {
                drivers[num] = total;
                lapcount[total] = 1;
                total++;
            }
        }
        
        // if ranking changed, print "YES"
        // else print "NO"
        if (changedFlag) 
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}