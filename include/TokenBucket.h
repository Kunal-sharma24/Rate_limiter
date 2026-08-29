#ifndef TOKEN_BUCKET_H
#define TOKEN_BUCKET_H

#include <chrono>   //for time measurement
#include <mutex>    //for deadlock prevention

using namespace std;

class TokenBucket
{
private:

    double capacity;

    double refillRate;

    double tokens;

    chrono::steady_clock::time_point lastRefillTime;

    mutex bucketmutex;

public:

    // Constructor
    TokenBucket(double capacity, double refillRate);

    bool allowRequest();

    double getAvailableTokens();

private:

    void refill();  

};

#endif