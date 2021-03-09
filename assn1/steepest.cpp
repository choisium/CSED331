#include <iostream>
#include <cmath>
using namespace std;

typedef struct {
    int x;
    int y;
} POINT;

int compare (const void* p1, const void* p2) {
    return ((POINT*)p1)->x - ((POINT*)p2)->x;
}

int main() {
    int t;
    std::cin >> t;
    POINT points[100000];
    for(int i = 0; i < t; i++) {
        int n;
        std::cin >> n;
        for (int j = 0; j < n; j++) {
            std::cin >> points[j].x >> points[j].y;
        }

        qsort(points, n, sizeof(POINT), compare);

        POINT* steepest = points;
        double steepness = abs((double) (points[1].y - points[0].y) / (points[1].x - points[0].x));

        for (int j = 1; j < n - 1; j++) {
            double compare = abs((double) (points[j+1].y - points[j].y) / (points[j+1].x - points[j].x));
            if (compare > steepness) {
                steepness = compare;
                steepest = &points[j];
            }
        }

        cout << steepest->x << " " << steepest->y << " " << (steepest + 1)->x << " " << (steepest + 1)->y <<endl;
    }
}