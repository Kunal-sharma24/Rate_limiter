#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>

#include "TokenBucket.h"

using namespace std;

int main()
{
    cout << "Running Token Bucket Tests...\n" << endl;

    // ==========================================
    // TEST 1: Initial requests should be allowed
    // ==========================================

    TokenBucket bucket(5, 2);

    for (int i = 0; i < 5; i++)
    {
        assert(bucket.allowRequest());
    }

    cout << "Test 1 PASSED: Initial requests allowed" << endl;


    // ==========================================
    // TEST 2: Bucket should reject when empty
    // ==========================================

    assert(!bucket.allowRequest());

    cout << "Test 2 PASSED: Request rejected when bucket empty" << endl;


    // ==========================================
    // TEST 3: Tokens should refill
    // ==========================================

    this_thread::sleep_for(
        chrono::milliseconds(1100)
    );

    assert(bucket.allowRequest());

    cout << "Test 3 PASSED: Tokens refill over time" << endl;


    // ==========================================
    // TEST 4: Available tokens
    // ==========================================

    double tokens = bucket.getAvailableTokens();

    cout << "Available tokens: "
         << tokens
         << endl;

    assert(tokens >= 0);

    cout << "Test 4 PASSED: Available token count valid" << endl;


    cout << "\nAll Token Bucket tests PASSED!" << endl;

    return 0;
}