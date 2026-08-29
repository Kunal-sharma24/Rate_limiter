#ifndef SLIDING_WINDOW_H
#define SLIDING_WINDOW_H

#include <chrono>
#include <deque>
#include <mutex>

using namespace std;

class SlidingWindow
{
private:

    int maxRequests;

    double windowSize;

    deque<chrono::steady_clock::time_point> requests;

    mutex windowMutex;

public:

    // Constructor
    SlidingWindow(int maxRequests, double windowSize);

    bool allowRequest();

    int getRequestCount();

private:

    void removeExpiredRequests();
};

#endif