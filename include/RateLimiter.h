#ifndef RATE_LIMITER_H
#define RATE_LIMITER_H

#include <string>
#include <unordered_map>
#include <memory>
#include <mutex>

#include "ClientConfig.h"
#include "TokenBucket.h"
#include "SlidingWindow.h"

using namespace std;

class RateLimiter
{
private:

    unordered_map<string, ClientConfig> clientConfigs;

    unordered_map<string, unique_ptr<TokenBucket>> tokenBuckets;

    unordered_map<string, unique_ptr<SlidingWindow>> slidingWindows;

    mutex limiterMutex;

public:

    void addClient(const ClientConfig& config);

    bool allowRequest(const string& clientId);

    double getAvailableTokens(const string& clientId);

    int getRequestCount(const string& clientId);
};

#endif