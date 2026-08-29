#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <cassert>

#include "TokenBucket.h"

using namespace std;

int main()
{
    cout << "Running Concurrency Test...\n" << endl;

    // ==========================================
    // CREATE TOKEN BUCKET
    // ==========================================

    // Capacity = 5
    // Refill rate = 0
    //
    // This means exactly 5 requests
    // should be allowed.
    
    TokenBucket bucket(5, 0);


    // ==========================================
    // CREATE 20 THREADS
    // ==========================================

    const int numberOfThreads = 20;

    atomic<int> allowedRequests(0);
    atomic<int> rejectedRequests(0);

    vector<thread> threads;


    // ==========================================
    // START THREADS
    // ==========================================

    for (int i = 0; i < numberOfThreads; i++)
    {
        threads.emplace_back([&]()
        {
            if (bucket.allowRequest())
            {
                allowedRequests++;
            }
            else
            {
                rejectedRequests++;
            }
        });
    }


    // ==========================================
    // WAIT FOR ALL THREADS
    // ==========================================

    for (auto& thread : threads)
    {
        thread.join();
    }


    // ==========================================
    // DISPLAY RESULTS
    // ==========================================

    cout << "Total threads: "
         << numberOfThreads
         << endl;

    cout << "Allowed requests: "
         << allowedRequests
         << endl;

    cout << "Rejected requests: "
         << rejectedRequests
         << endl;


    // ==========================================
    // VERIFY RESULT
    // ==========================================

    assert(allowedRequests == 5);

    assert(rejectedRequests == 15);


    cout << "\nConcurrency Test PASSED!" << endl;

    return 0;
}