#ifndef HANOINODES_H
#define HANOINODES_H

/*
    This file will be used to implement a graph/tree structure to be used alongside
    the queue structure as the algorithm is running.
*/

#include "HanoiTowers.h"

class HanoiNode {

private:

    // create the three towers (for FROM, TEMP, TO pegs)
    TowerofHanoi htowers[3];
    
    HanoiNode *rootParentNode; // pointer to parent node
    bool goalNodeReached;      // flag to determine whether goal node has been reached
    int f;
    int g;
    int h;

public:
    // constructor
    HanoiNode();

    // destructor
    ~HanoiNode();

    void setHanoiTower(HanoiTower, deque <int> &);
    TowerofHanoi& getHanoiTower(HanoiTower char_name) {return htowers[char_name];}
    HanoiNode * getParent(){ return rootParentNode; }

    bool isEqual(HanoiNode *); // compares nodes
    void setParent(HanoiNode *);
    bool isGoal(); // returns true if an element is goal node

    // heuristic variables
    void setF();
    void setG(int);
    void setH(int);
    int getF(){ return f; }
    int getG(){ return g; }
    int getH(){ return h; }

    // recursive best-first search method (args: node to expand, upper-bound cost limit)
    void rbfs(deque<int> &, int);

    void displayResults();
};
#endif