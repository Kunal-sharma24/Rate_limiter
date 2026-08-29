#include "TokenBucket.h"

using namespace std;

TokenBucket::TokenBucket(double capacity, double refillRate)
    : capacity(capacity),
      refillRate(refillRate),
      tokens(capacity),
      lastRefillTime(chrono::steady_clock::now())
{
}

void TokenBucket::refill()
{
    auto now = chrono::steady_clock::now();

    chrono::duration<double> elapsed = now - lastRefillTime;   //suppose 2 secs

    double tokensToAdd = elapsed.count() * refillRate;   //2sec*2tok/sec = 4token

    tokens += tokensToAdd;

    if (tokens > capacity)
    {
        tokens = capacity;
    }

    lastRefillTime = now;
}

bool TokenBucket::allowRequest()
{
    lock_guard<mutex> lock(bucketmutex);   //lock the mutex
                                           //this protect from simulataneous access

    refill();

    if (tokens >= 1.0)
    {
        tokens -= 1.0;
        return true;
    }

    return false;
}