#ifndef TOKEN_BUCKET_H
#define TOKEN_BUCKET_H

#include <chrono>   //for time measurement
#include <mutex>    //for deadlock prevention

using namespace std;

class TokenBucket
{
private:

    // Maximum number of tokens the bucket can hold like max token it can handle is 10
    double capacity;

    // How many tokens are added every second  eg like 5tocken/sec
    double refillRate;

    // Current number of available tokens   like if 5 token/sec and 1 sec passed then tokens=5
    double tokens;

    // Time when the bucket was last updated
    chrono::steady_clock::time_point lastRefillTime;

    // Protects the bucket when multiple threads use it
    mutex bucketmutex;
    /*
    eg lets suppose if token are 1 and Thread 1 and Thread 2 are trying to access
    the bucket at the same time then mutex will prevent deadlock
    if both takes the token consume then token will be -1 which is not error
    thats why we are using mutex
    */

public:

    // Constructor
    TokenBucket(double capacity, double refillRate);//(10,2) mean 10max token and 2 token/s

    // Returns true if the request is allowed
    // Returns false if the request is rejected
    bool allowRequest();

    double getAvailableTokens();   //to get the available token count

private:

    // Adds tokens according to the time that has passed
    void refill();  
    //we are using double not int bcz the rate can be in 2.5token/sec type
};

#endif