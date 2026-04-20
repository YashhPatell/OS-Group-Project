#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include "guest.h"
using namespace std;

void printResults(vector<Guest>& guests);
void printGantt(vector<pair<string, int>>& timeline);

// Round Robin: each guest gets a fixed time slice before moving to the next
void roundRobin(vector<Guest> guests, int quantum) {
    cout << "\n========================================\n";
    cout << " Round Robin (Quantum = " << quantum << ")\n";
    cout << " Each guest group gets equal time slots\n";
    cout << "========================================\n";

    int n = guests.size();
    for (auto& g : guests)
        g.remainingTime = g.burstTime;

    queue<int> readyQueue;
    vector<bool> inQueue(n, false);
    vector<pair<string, int>> timeline;

    int currentTime = 0, completed = 0, contextSwitches = 0;

    // Add guests that are already here at time 0
    for (int i = 0; i < n; i++) {
        if (guests[i].arrivalTime == 0) {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }

    while (completed < n) {
        // If no one is ready, jump to next arrival
        if (readyQueue.empty()) {
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && guests[i].remainingTime > 0) {
                    currentTime = guests[i].arrivalTime;
                    readyQueue.push(i);
                    inQueue[i] = true;
                    break;
                }
            }
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        // Run for quantum or remaining time, whichever is less
        int timeSlice = min(quantum, guests[idx].remainingTime);
        guests[idx].remainingTime -= timeSlice;
        currentTime += timeSlice;
        contextSwitches++;

        timeline.push_back({guests[idx].name, currentTime});

        // Add any guests that arrived during this slice
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && guests[i].arrivalTime <= currentTime && guests[i].remainingTime > 0) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        if (guests[idx].remainingTime > 0) {
            readyQueue.push(idx); // put back in queue
        } else {
            guests[idx].completionTime  = currentTime;
            guests[idx].turnaroundTime  = currentTime - guests[idx].arrivalTime;
            guests[idx].waitingTime     = guests[idx].turnaroundTime - guests[idx].burstTime;
            completed++;
        }
    }

    printGantt(timeline);
    printResults(guests);
    cout << "Total Context Switches: " << contextSwitches << "\n";
}
