#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>

#include "SlidingWindow.h"

using namespace std;

int main()
{
    cout << "Running SlidingWindow Tests...\n" << endl;


    SlidingWindow window(5, 1);

    for (int i = 0; i < 5; i++)
    {
        assert(window.allowRequest());
    }

    cout << "Test 1 PASSED: Initial requests allowed" << endl;


    assert(!window.allowRequest());

    cout << "Test 2 PASSED: Request rejected when window full" << endl;


    this_thread::sleep_for(
        chrono::milliseconds(1100)
    );

    assert(window.allowRequest());

    cout << "Test 3 PASSED: window should wait for that time" << endl;



    double windowrefill = window.getRequestCount();

    cout << "Available requests: "
         << windowrefill
         << endl;

    assert(windowrefill >= 0);

    cout << "Test 4 PASSED: Available time restore" << endl;


    cout << "\nAll Sliding window tests PASSED!" << endl;

    return 0;
}