#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>

#include "SlidingWindow.h"

using namespace std;

int main()
{
    cout << "Running SlidingWindow Tests...\n" << endl;

    // ==========================================
    // TEST 1: Initial requests should be allowed
    // ==========================================

    SlidingWindow window(5, 1);

    for (int i = 0; i < 5; i++)
    {
        assert(window.allowRequest());
    }

    cout << "Test 1 PASSED: Initial requests allowed" << endl;


    // ==========================================
    // TEST 2: WIndow should reject when Full
    // ==========================================

    assert(!window.allowRequest());

    cout << "Test 2 PASSED: Request rejected when window full" << endl;


    // ==========================================
    // TEST 3: Tokens should refill
    // ==========================================

    this_thread::sleep_for(
        chrono::milliseconds(1100)
    );

    assert(window.allowRequest());

    cout << "Test 3 PASSED: window should wait for that time" << endl;


    // ==========================================
    // TEST 4: Available time
    // ==========================================

    double windowrefill = window.getRequestCount();

    cout << "Available requests: "
         << windowrefill
         << endl;

    assert(windowrefill >= 0);

    cout << "Test 4 PASSED: Available time restore" << endl;


    cout << "\nAll Sliding window tests PASSED!" << endl;

    return 0;
}