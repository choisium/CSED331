#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    // get the number of testcases
    int t;
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        // get the number of houses
        int n;
        cin >> n;

        int* houses = new int[n];
        int sum = 0;

        // get location of houses
        for (int j = 0; j < n; j++) {
            int house;
            cin >> house;
            if (j < n / 2)
                sum -= house;
            else if (j > n / 2)
                sum += house;
            else if (n % 2 == 0)
                sum += house;
        }
        
        // // find median value and get the sum of distances
        // int median = houses[n / 2];
        // int sum = 0;
        // for (int j = 0; j < n; j++) {
        //     sum += abs(houses[j] - median);
        // }

        cout << sum << endl;;

        delete[] houses;
    }
}