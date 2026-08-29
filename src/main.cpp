#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

#include "TokenBucket.h"
#include "SlidingWindow.h"

using namespace std;

int main()
{
    cout << "Rate Limiter Server Starting..." << endl;

    // Create a token bucket
    // Capacity = 5 tokens
    // Refill rate = 2 tokens per second
    TokenBucket bucket(5, 2);

    cout << "\nTesting Token Bucket...\n" << endl;

    // Send 7 requests immediately
    for (int i = 1; i <= 7; i++)
    {
        cout << "Availabel tokens" << fixed << setprecision(2) << bucket.getAvailableTokens() <<endl;
        if (bucket.allowRequest())
        {
            cout << "Request " << i << " -> ALLOW" << endl;
        }
        else
        {
            cout << "Request " << i << " -> REJECT" << endl;
        }

        
    }

    // Wait for 1 second
    cout << "\nWaiting for 1 second...\n" << endl;

    this_thread::sleep_for(chrono::seconds(1));   

    // Try another request
    for(int i=0; i<3; i++)
    {
        cout << "Availabel tokens" << fixed << setprecision(2) << bucket.getAvailableTokens() <<endl;
        if (bucket.allowRequest())
        {
            cout << "Request " << (i + 8) << " -> ALLOW" << endl;
        }
        else
        {
            cout << "Request " << (i + 8) << " -> REJECT" << endl;
        }
        
    }

    // ==========================================
// SLIDING WINDOW TEST
// ==========================================

cout << "\nTesting Sliding Window...\n" << endl;

// Maximum 5 requests in 1 second
    SlidingWindow window(5, 1);

// Send 7 requests
for (int i = 1; i <= 7; i++)
{
    cout << "Available requests: "
         << window.getRequestCount()
         << endl;

    cout << "Request " << i << " -> ";

    if (window.allowRequest())
    {
        cout << "ALLOW" << endl;
    }
    else
    {
        cout << "REJECT" << endl;
    }
}

// Wait for 1.1 seconds
cout << "\nWaiting for 1.1 seconds...\n" << endl;

this_thread::sleep_for(chrono::milliseconds(1100));

cout << "Requests after waiting: "
     << window.getRequestCount()
     << endl;

// Send 3 more requests
for (int i = 1; i <= 3; i++)
{
    int requestNumber = i + 7;

    cout << "Available requests: "
         << window.getRequestCount()
         << endl;

    cout << "Request " << requestNumber << " -> ";

    if (window.allowRequest())
    {
        cout << "ALLOW" << endl;
    }
    else
    {
        cout << "REJECT" << endl;
    }
}


    return 0;
}