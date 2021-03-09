#include <iostream>

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        long long a, b;
        std::cin >> a >> b;
        std::cout << a + b << std::endl;
    }
}