#include <iostream>
#include <chrono>
#include <iomanip>

#include "TokenBucket.h"

using namespace std;
using namespace chrono;

int main()
{
    cout << "======================================" << endl;
    cout << "      RATE LIMITER BENCHMARK" << endl;
    cout << "======================================" << endl;

    // Create a bucket with a large capacity
    // so that requests are not rejected during
    // the benchmark.
    const int totalRequests = 1000000;

    TokenBucket bucket(totalRequests, 0);

    // Start timer
    auto start = high_resolution_clock::now();

    int allowedRequests = 0;

    // Send requests
    for (int i = 0; i < totalRequests; i++)
    {
        if (bucket.allowRequest())
        {
            allowedRequests++;
        }
    }

    // Stop timer
    auto end = high_resolution_clock::now();

    // Calculate elapsed time
    auto duration =
        duration_cast<microseconds>(end - start);

    double seconds =
        duration.count() / 1'000'000.0;

    double requestsPerSecond =
        allowedRequests / seconds;

    // Display results
    cout << fixed << setprecision(2);

    cout << "\nTotal requests: "
         << totalRequests
         << endl;

    cout << "Allowed requests: "
         << allowedRequests
         << endl;

    cout << "Time taken: "
         << seconds
         << " seconds"
         << endl;

    cout << "Throughput: "
         << requestsPerSecond
         << " requests/sec"
         << endl;

    cout << "\n======================================" << endl;

    return 0;
}


// 6.53 million requests/sec in a single-threaded benchmark