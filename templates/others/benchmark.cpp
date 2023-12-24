#include <iostream>
#include <chrono>
#include <functional>

using namespace std;
using namespace std::chrono;

void benchmark(function<void()> &f, string desc = "") {
    cout << "Running " << desc << endl;
    auto start = high_resolution_clock::now();
    f();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Done in " << duration.count() << " ms" << endl;
}