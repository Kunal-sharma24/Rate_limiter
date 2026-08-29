#include "RateLimiter.h"

using namespace std;

void RateLimiter::addClient(const ClientConfig& config)
{
    lock_guard<mutex> lock(limiterMutex);

    // Save configuration
    clientConfigs[config.clientId] = config;

    // Create the required rate limiter
    if (config.algorithm == "token_bucket")
    {
        tokenBuckets[config.clientId] =
            make_unique<TokenBucket>(
                config.capacity,
                config.refillRate
            );

        // Remove any old Sliding Window
        slidingWindows.erase(config.clientId);
    }
    else if (config.algorithm == "sliding_window")
    {
        slidingWindows[config.clientId] =
            make_unique<SlidingWindow>(
                config.maxRequests,
                config.windowSize
            );

        // Remove any old Token Bucket
        tokenBuckets.erase(config.clientId);
    }
}


bool RateLimiter::allowRequest(const string& clientId)
{
    lock_guard<mutex> lock(limiterMutex);

    // Check whether client exists
    if (clientConfigs.find(clientId) == clientConfigs.end())
    {
        return false;
    }

    ClientConfig& config = clientConfigs[clientId];

    // Use Token Bucket
    if (config.algorithm == "token_bucket")
    {
        return tokenBuckets[clientId]->allowRequest();
    }

    // Use Sliding Window
    if (config.algorithm == "sliding_window")
    {
        return slidingWindows[clientId]->allowRequest();
    }

    // Unknown algorithm
    return false;
}


double RateLimiter::getAvailableTokens(const string& clientId)
{
    lock_guard<mutex> lock(limiterMutex);

    if (tokenBuckets.find(clientId) == tokenBuckets.end())
    {
        return 0.0;
    }

    return tokenBuckets[clientId]->getAvailableTokens();
}


int RateLimiter::getRequestCount(const string& clientId)
{
    lock_guard<mutex> lock(limiterMutex);

    if (slidingWindows.find(clientId) == slidingWindows.end())
    {
        return 0;
    }

    return slidingWindows[clientId]->getRequestCount();
}