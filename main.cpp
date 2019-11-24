/* This file will serve as the driver program to run RBFS or A* Search */

#include "HanoiNodes.h"
#include <iostream>
#include <iomanip>  // library needed for formatting output
#include <chrono>   // library needed for timing algorithm runtimes
#include <cmath>    // math functions
#include <vector>
#include <queue> // library needed to implement a priority queue
#include <deque> // library needed for double-ended queue

using namespace std;

int main() {

    cout << endl;
    cout << "*************************************\n"
         << "********** Towers of Hanoi **********\n"
         << "**********   |    |    |   **********\n"
         << "**********   |    |    |   **********\n"
         << "**********  ===  ===  ===  **********\n"
         << "*************************************\n\n";

    // begin with 3 disks
    int numOfDisks = 3;
    bool isInOPEN = false;
    bool isInCLOSED = false;

    deque<HanoiNode> tree;
    priority_queue<int> OPEN;       // collection of all generated nodes (not expanded)
    priority_queue<int> CLOSED;     // collection of all visited nodes (expanded)

    auto startClock = chrono::high_resolution_clock::now();
    auto stopClock = chrono::high_resolution_clock::now();

    // TODO: call a function to initialize disks (nodes) on open queue
    generateRootNode(tree, numOfDisks);


    // TODO: call RBFS algorithm function

    // TODO: call a display function for results: execution time, memory used, # of nodes generated and expanded


    // prioriity queue does not contain a clear() method, will to reset this way for now
    OPEN = priority_queue<int>();   // reset queue
    CLOSED = priority_queue<int>(); // reset queue
    tree.clear();

    return 0;
    
}

