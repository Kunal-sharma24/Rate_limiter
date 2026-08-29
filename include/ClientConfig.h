#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H

#include <string>

using namespace std;

struct ClientConfig
{
    string clientId;

    string algorithm;

    double capacity;
    double refillRate;

    int maxRequests;
    double windowSize;
};

#endif