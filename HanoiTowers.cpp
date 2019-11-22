/* Tower of Hanoi */
// Recursive Best-First Search Implementation

/* General implementation of RBFS */
// RBFS is called with 2 arguments: a node to expand and an upper bound.
// RBFS works by keeping track of an upper bound, which allows the algorithm
// to choose better paths rather than continue indefinitely down a current path.

// An evaluation function, f(n), is used to evaluate nodes: a cost estimate, so the node 
// with the lowest evaluation is expanded first.
// We also use a heuristic function, h(n), to estimate the cost of the least/cheapest path
// from the state at node n to a goal node.
// Because we want to expand the node that is closest to the goal, we only use the heuristic function
// f(n) = h(n)
// Finally, RBFS uses the variable f_limit to keep track of the f-value of the best alternative path
// available from any ancestor of the current node. If the current node exceeds the f_value, the 
// recursion unwinds back to the alternative path. As the recursion unwinds, RBFS replaces the f_value
// of each node along the path with the best f_value of its children. In this way, RBFS determines if it's
// worth reexpanding the subtree at a later time.


#include "HanoiTowers.h"
#include <iostream>
#include <queue>

using namespace std;


void TowersofHanoi::pushDisk(int n) {

    if(isFull()){
        cout << "'A' stack is full.\n";
    }
    else{

    }
}

void TowersofHanoi::popTopDisk(int &n){

    if(isEmpty()){
        cout << "The disk stack is empty.\n";
    }
    else{

    }
}

bool TowersofHanoi::isFull() const{

    bool status;

    
}

bool TowersofHanoi::isEmpty() const {

    bool status;

    
}

// Towers of Hanoi implementation
void TowersofHanoi::rbfs(){


}


