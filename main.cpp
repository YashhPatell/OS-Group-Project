  #include <iostream>
#include <vector>
#include "guest.h"
using namespace std;

// Forward declarations
void fcfs(vector<Guest> guests);
void sjf(vector<Guest> guests);
void roundRobin(vector<Guest> guests, int quantum);

int main() {
    cout << "============================================================\n";
    cout << "  Disneyland Ride Queue - CPU Scheduling Simulation\n";
    cout << "  CPSC 351-08 | Spring 2026\n";
    cout << "============================================================\n";

    // Guest groups: name, arrivalTime, burstTime, priority, (rest start at 0)
    vector<Guest> guests = {
        {"G1", 0, 6, 2, 0, 0, 0, 0},
        {"G2", 1, 3, 1, 0, 0, 0, 0},
        {"G3", 2, 8, 3, 0, 0, 0, 0},
        {"G4", 3, 4, 2, 0, 0, 0, 0},
        {"G5", 4, 2, 1, 0, 0, 0, 0}
    };

    int quantum = 3;

    fcfs(guests);
    sjf(guests);
    roundRobin(guests, quantum);

    cout << "\n============================================================\n";
    cout << "  Simulation Complete\n";
    cout << "============================================================\n";

    return 0;
}
