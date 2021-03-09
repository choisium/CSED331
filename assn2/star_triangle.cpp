#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

void add_blank(string res[], int from, int to, int count) {
    for (int i = from; i < to; i++) {
        res[i].append(string(count, ' '));
    }
}

void make_triangle(string res[], int from, int to) {
    if ((to - from) <= 3) {
        res[from].append("*****");
        res[from + 1].append(" * * ");
        res[from + 2].append("  *  ");
    } else {
        int middle = (to + from) / 2;
        // draw top half
        add_blank(res, from, middle, (to - from) / 2);
        make_triangle(res, from, middle);
        // draw bottom half
        make_triangle(res, middle, to);
        add_blank(res, middle, to, 1);
        make_triangle(res, middle, to);
        add_blank(res, from, middle, (to - from) / 2);
    }
}

string trim(string s) {
    return s.erase(s.find_last_not_of(" ") + 1);
}

void print_result(string res[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", trim(res[i]).c_str());
        res[i] = "";
    }
}


int main() {
    // get the number of testcases
    int t;
    scanf("%d", &t);

    string res[12288];
    
    for(int i = 0; i < t; i++) {
        // get the line number
        int n;
        scanf("%d", &n);

        make_triangle(res, 0, n);
        print_result(res, n);
    }
}