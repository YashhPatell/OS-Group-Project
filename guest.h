#ifndef GUEST_H
#define GUEST_H

#include <string>
using namespace std;

// Represents a guest group waiting in line
struct Guest {
    string name;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

#endif
