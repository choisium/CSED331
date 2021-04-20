#include <stdio.h>
#include <queue>
#include <vector>
#include <utility>
#include <limits.h>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

string arr[24576];

void add_blank(int n, int from, int to) {
    string s = "";
    for(int j = 0; j < n; j++) {
        s += " ";
    }
    for(int i = from; i < to; i++) {
        arr[i] += s;
    }
}

void print_star(int n, int from, int to) {
    if (n == 3) {
        arr[from] += "  *  ";
        arr[from+1] += " * * ";
        arr[from+2] += "*****";
    } else {
        add_blank(n/2, from, from + (to - from)/2);
        print_star(n/2, from, from + (to - from)/2);
        add_blank(n/2, from, from + (to - from)/2);
        print_star(n/2, from + (to - from)/2, to);
        add_blank(1, from + (to - from)/2, to);
        print_star(n/2, from + (to - from)/2, to);
    }
}


int main() {
    int tc;
    scanf("%d", &tc);
    
    for (int t = 0; t < tc; t++) {
        int n;
        scanf("%d", &n);
        print_star(n, 0, n);
        
        for(int i = 0; i < n; i++) {
            int idx = arr[i].find_last_not_of(' ');
            cout << arr[i].substr(0, idx + 1) << endl;
            arr[i] = "";
        }
    }

}