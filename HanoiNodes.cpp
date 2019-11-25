#include "HanoiNodes.h"
#include <iostream>
using namespace std;

// constructor: initialize all variables and pointer
HanoiNode::HanoiNode() {

    rootParentNode = nullptr;
    goalNodeReached = false;
    f = 0;
    g = 0;
    h = 0;
}

// destructor
HanoiNode::~HanoiNode() {
    delete this;
}
// set each tower of hanoi (A, B, C)
void HanoiNode::setHanoiTower(HanoiTower char_name, deque<int>& hanoiDisks) {

    htowers[char_name].setHanoiDisks(hanoiDisks);
}
// make parent root node to the node passed to function to begin search
void HanoiNode::setParent(HanoiNode *node) {

    rootParentNode = node;
}

// will be used to compare nodes (or element values) to see if they are in OPEN or CLOSED
bool HanoiNode::isEqual(HanoiNode *node) {

    bool isEqual = false;

    if(this->getHanoiTower(A).getTowerDisks() == node->getHanoiTower(A).getTowerDisks()) {
        if(this->getHanoiTower(B).getTowerDisks() == node->getHanoiTower(B).getTowerDisks()) {
            if(this->getHanoiTower(C).getTowerDisks() == node->getHanoiTower(C).getTowerDisks()) {
                isEqual = true;
            }
        }
    }
    return isEqual;
}

void HanoiNode::setF() {
    f = g + h;
}

void HanoiNode::setG(int g) {
    this->g = g;
}

void HanoiNode::setH(int h) {
    this->h = h;
}

// TODO: implement whether goal has been found
bool HanoiNode::isGoal() {

    return false;
}


// Recursive Best-First Search implementation
void HanoiNode::rbfs(deque<int> &node, int f_limit){

/*
    1. Start with OPEN, containing just the initial state
    2. Until a goal is found or there are no nodes on OPEN do:
        a. pick the best node on OPEN
        b. generate its successors
        c. for each successor do:
            i. if it has not been generated before, evaluate it, add it to OPEN, and record its parent
            ii. if it has been generated before, change the parents if this new path is better than the
                previous one. In that case, update the cost of getting to this node and to any successors
                that this node may already have.
*/
}