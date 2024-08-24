#include <chrono>
#include <iostream>

using namespace std;

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100; i++) {
        cout << i << endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << "ns" << std::endl;
}