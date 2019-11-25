#ifndef HANOITOWERS_H
#define HANOITOWERS_H

/*
    Defines a class structure for each tower of hanoi that will be used in the program.
    Creates a double-ended queue for a tower and its size will be defined by number of disks.
    Additional functions will be used to setup initial towers and performs operations on them.

    Deque is used as it is more efficient to insert or delete elements on both the beginning
    and end of a queue. Note: contiguous storage may not be guaranteed.
*/
#include <deque> // library needed for double-ended queue
using namespace std;

// will be used to name towers
enum HanoiTower {A, B, C};

class TowerofHanoi {

    private:

        deque<int> hanoiDisks;    // creates a deque for each object of TowerofHanoi
        int diskSize;             // defines total disks for a tower


    public:

        // constructor
        TowerofHanoi();

        // getter functions
        deque<int>& getTowerDisks();
        int getTopDisk();

        // setter function to initialize towers
        void setHanoiDisks(deque<int> &hanoiDisks);

        // helper functions
        void pushDisk(int );
        int popTopDisk();
        // Note: will use methods provided by deque to check for empty deque, clear, etc


};
#endif