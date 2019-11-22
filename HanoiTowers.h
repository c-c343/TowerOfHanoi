#ifndef HANOITOWERS_H
#define HANOITOWERS_H

/*
    A priority queue implementation will be needed for the OPEN and CLOSED states.
    A directed graph combined with the priority queue might be the best way to go,
    but will explore other structures. A seperate header file will most likely be
    needed to define a node structure for the graph.
*/

// macro definitions
#define FROM_PEG = 'A';
#define TEMP_PEG = 'B';
#define TO_PEG   = 'C';

#include <queue> // library needed to implement a priority queue
using namespace std;

class TowersofHanoi {

    private:

        priority_queue<int> init_state;
        priority_queue<int> OPEN;
        priority_queue<int> CLOSED;
        int disks;


    public:
        
        // recursive best-first search method
        void rbfs();

        // structure methods
        void pushDisk(int);
        void popTopDisk(int &);
        bool isEmpty() const;
        bool isFull() const;

        bool goal_reached();



};
#endif