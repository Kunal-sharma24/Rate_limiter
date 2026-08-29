#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

#include "RateLimiter.h"

using namespace std;

int main()
{
    cout << "Rate Limiter Server Starting..." << endl;


    // ==========================================
    // CREATE RATE LIMITER
    // ==========================================

    RateLimiter limiter;


    // ==========================================
    // CLIENT 1 - TOKEN BUCKET
    // ==========================================

    ClientConfig client1;

    client1.clientId = "user123";
    client1.algorithm = "token_bucket";

    client1.capacity = 5;
    client1.refillRate = 2;

    client1.maxRequests = 0;
    client1.windowSize = 0;

    limiter.addClient(client1);


    // ==========================================
    // CLIENT 2 - SLIDING WINDOW
    // ==========================================

    ClientConfig client2;

    client2.clientId = "user456";
    client2.algorithm = "sliding_window";

    client2.capacity = 0;
    client2.refillRate = 0;

    client2.maxRequests = 5;
    client2.windowSize = 1;

    limiter.addClient(client2);


    // ==========================================
    // TEST USER 123
    // ==========================================

    cout << "\n==============================" << endl;
    cout << "       USER123 TEST" << endl;
    cout << "==============================\n" << endl;

    cout << "Algorithm: Token Bucket\n" << endl;

    for (int i = 1; i <= 7; i++)
    {
        cout << "Available tokens: "
             << fixed << setprecision(2)
             << limiter.getAvailableTokens("user123")
             << endl;

        if (limiter.allowRequest("user123"))
        {
            cout << "Request " << i << " -> ALLOW" << endl;
        }
        else
        {
            cout << "Request " << i << " -> REJECT" << endl;
        }
    }


    // ==========================================
    // TEST USER 456
    // ==========================================

    cout << "\n==============================" << endl;
    cout << "       USER456 TEST" << endl;
    cout << "==============================\n" << endl;

    cout << "Algorithm: Sliding Window\n" << endl;

    for (int i = 1; i <= 7; i++)
    {
        cout << "Requests in window: "
             << limiter.getRequestCount("user456")
             << endl;

        if (limiter.allowRequest("user456"))
        {
            cout << "Request " << i << " -> ALLOW" << endl;
        }
        else
        {
            cout << "Request " << i << " -> REJECT" << endl;
        }
    }


    // ==========================================
    // WAIT
    // ==========================================

    cout << "\nWaiting for 1.1 seconds...\n" << endl;

    this_thread::sleep_for(
        chrono::milliseconds(1100)
    );


    // ==========================================
    // TEST USER456 AFTER WINDOW
    // ==========================================

    cout << "\nRequests in window after waiting: "
         << limiter.getRequestCount("user456")
         << endl;

    if (limiter.allowRequest("user456"))
    {
        cout << "New request -> ALLOW" << endl;
    }
    else
    {
        cout << "New request -> REJECT" << endl;
    }


    return 0;
}