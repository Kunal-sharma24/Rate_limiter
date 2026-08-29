#include <SlidingWindow.h>
using namespace std;

SlidingWindow::SlidingWindow(int maxreq , double windowsize):
    maxRequests(maxreq),
    windowSize(windowsize)
{
}

void SlidingWindow::removeExpiredRequests(){
    auto now = chrono::steady_clock::now();
    auto windowStart = now - chrono::duration<double>(windowSize);
    while(!requests.empty() && requests.front() < windowStart){
        requests.pop_front();
    }
}

bool SlidingWindow::allowRequest(){
    lock_guard<mutex> lock(windowMutex);
    removeExpiredRequests();
    if(requests.size() < maxRequests){
        requests.push_back(chrono::steady_clock::now());
        return true;
    }
    return false;
}

int SlidingWindow::getRequestCount(){
    lock_guard<mutex> lock(windowMutex);
    removeExpiredRequests();
    return requests.size();
}