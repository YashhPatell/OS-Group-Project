#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include "guest.h"
using namespace std;

void printResults(vector<Guest>& guests);
void printGantt(vector<pair<string, int>>& timeline);

// SJF: guest with the shortest burst time goes next
void sjf(vector<Guest> guests) {
    cout << "\n========================================\n";
    cout << " SJF - Shortest Job First\n";
    cout << " Shortest ride duration boards first\n";
    cout << "========================================\n";

    int n = guests.size();
    int currentTime = 0, completed = 0;
    vector<bool> done(n, false);
    vector<pair<string, int>> timeline;

    while (completed < n) {
        int shortest = -1;
        int minBurst = INT_MAX;

        // Find arrived guest with shortest burst
        for (int i = 0; i < n; i++) {
            if (!done[i] && guests[i].arrivalTime <= currentTime) {
                if (guests[i].burstTime < minBurst) {
                    minBurst = guests[i].burstTime;
                    shortest = i;
                }
            }
        }

        // No guest ready yet, advance time
        if (shortest == -1) {
            currentTime++;
            continue;
        }

        currentTime += guests[shortest].burstTime;
        guests[shortest].completionTime  = currentTime;
        guests[shortest].turnaroundTime  = currentTime - guests[shortest].arrivalTime;
        guests[shortest].waitingTime     = guests[shortest].turnaroundTime - guests[shortest].burstTime;
        done[shortest] = true;
        completed++;

        timeline.push_back({guests[shortest].name, currentTime});
    }

    printGantt(timeline);
    printResults(guests);
}
