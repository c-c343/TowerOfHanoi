/* This file will serve as the driver program to run RBFS or A* Search */

#include "HanoiNodes.h"
#include <iostream>
#include <iomanip>  // library needed for formatting output
#include <chrono>   // library needed for timing algorithm runtimes
#include "chrono"
#include <cmath>    // math functions
#include <vector>
#include <queue> // library needed to implement a priority queue
#include <deque> // library needed for double-ended queue

using namespace std;
using namespace std::chrono;

// prototypes
void generateRootNode(deque<HanoiNode *>& , int);

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

    deque<HanoiNode *> tree;
    priority_queue<int> OPEN;       // collection of all generated nodes (not expanded)
    priority_queue<int> CLOSED;     // collection of all visited nodes (expanded)

    // begin clock
    auto startClock = high_resolution_clock::now();

    // TODO: call a function to initialize disks (nodes) on open queue
    generateRootNode(tree, numOfDisks);
    OPEN.push(tree.front()); // push parent node into OPEN

    // TODO: heuristic function(s)
    		/*  Oswaldo Vielma
			If h(n) is exactly equal to the cost of moving from n to the goal, then 
			A* will only follow the best path and never expand anything else

			| h(n) - h'(n) | = O(log(h'(n)))

			where h'(n) is the optimal heuristic, the exact cost to get from node n to the goal.
			In other words, h(n) will not grow faster than the logarithm of the "perfect heuristic" 
			h'(n) that returns the true distance from x to the goal.
		*/


    // TODO: call RBFS algorithm function


    // TODO: call a display function for results: execution time, memory used, # of nodes generated and expanded
    


    // prioriity queue does not contain a clear() method, will to reset this way for now
    OPEN = priority_queue<int>();   // reset queue
    CLOSED = priority_queue<int>(); // reset queue
    tree.clear();

    // stop clock and display program execution time
    auto stopClock = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopClock - startClock);

    cout << "Execution time: " << duration.count() << endl;

    return 0;
    
}

// generates a parent root node
void generateRootNode(deque<HanoiNode *> &tree, int n) {

    HanoiNode *root = new HanoiNode();
    root->setParent(nullptr);

    // Push n disks to tower A
    for(int i = n; i > 0; --i){
        root->getHanoiTower(A).pushDisk(i);
    }
    tree.push_back(root);

    //cout << endl << "Top disk: " << root->getHanoiTower(A).getTopDisk() << endl;
}
