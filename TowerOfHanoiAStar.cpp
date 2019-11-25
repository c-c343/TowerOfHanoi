
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <map>
#include <fstream>
#include <sstream>
#include "Header.h"


using namespace std;
using namespace std::chrono;

//function definitions for heuristics

int cynthia();
void alexandra();
void ozy();

/************************************************
 EDIT:	UPDATE NUMBER OF RINGS DESIRED
 ************************************************/
int numrings=8;

int bitmask = (1 << numrings) - 1;

class Tower {
private:
	int peg1, peg2, peg3;

	Tower(int temp1, int temp2, int temp3) {
		peg1 = temp1;
		peg2 = temp2;
		peg3 = temp3;
	}
public:
	//This creates a state with all rings on starting peg.
	Tower() {
		peg1 = bitmask;
		peg2 = 0;
		peg3 = 0;
	}


	//operator functions needed for stl map 
	bool operator<(const Tower& other) const {
		return (peg1 == other.peg1) ? ((peg2 == other.peg2) ? (peg3 < other.peg3) : (peg2 < other.peg2)) : (peg1 < other.peg1);
	}
	bool operator==(const Tower& other) const {
		return (peg1 == other.peg1) and (peg2 == other.peg2) and (peg3 == other.peg3);
	}
	bool operator!=(const Tower& other) const {
		return (peg1 != other.peg1) or (peg2 != other.peg2) or (peg3 != other.peg3);
	}



	bool win()const {
		return peg2 == bitmask or peg3 == bitmask;
	}
	//Validation: If move is invalid, define error.
	bool error() {
		return (peg1 < 0) or (peg2 < 0) or (peg3 < 0);
	}


	/* 

	Possible moves for disks
	Returns true if move is legal, false if otherwise

	*/
	bool move(const int m)const {
		int ring1 = (!peg1) ? 33 : __builtin_ffs(peg1);
		int ring2 = (!peg2) ? 33 : __builtin_ffs(peg2);
		int ring3 = (!peg3) ? 33 : __builtin_ffs(peg3);

		switch (m) {
		case 0:
			return ring1 < ring2;
		case 1:
			return ring2 < ring3;
		case 2:
			return ring3 < ring1;
		case 3:
			return ring1 > ring2;
		case 4:
			return ring2 > ring3;
		case 5:
			return ring3 > ring1;
		default:
			return false;
		}
	}

	Tower currMove(const int m)const {
		Tower value = *this;


		int ring1 = (!peg1) ? 33 : __builtin_ffs(peg1);
		int ring2 = (!peg2) ? 33 : __builtin_ffs(peg2);
		int ring3 = (!peg3) ? 33 : __builtin_ffs(peg3);

		ring1--;
		ring2--;
		ring3--;

		if (!move(m))
			return Tower(-1, -1, -1);

		switch (m) {
		//remove the lowest value ring from peg1 and add to peg 2
		case 0:
			value.peg1 ^= (1 << ring1);
			value.peg2 ^= (1 << ring1);
			return value;
		//peg2 to peg3 and so on
		case 1:
			value.peg2 ^= (1 << ring2);
			value.peg3 ^= (1 << ring2);
			return value;
		case 2:
			value.peg3 ^= (1 << ring3);
			value.peg1 ^= (1 << ring3);
			return value;
		case 3:
			value.peg2 ^= (1 << ring2);
			value.peg1 ^= (1 << ring2);
			return value;
		case 4:
			value.peg3 ^= (1 << ring3);
			value.peg2 ^= (1 << ring3);
			return value;
		case 5:
			value.peg1 ^= (1 << ring1);
			value.peg3 ^= (1 << ring1);
			return value;
		}

		return Tower(-1, -1, -1);
	}

	/*heuristic function for all items to reach a goal peg
		Heuristic by Cynthia
	*/
	int cynthia()const{
		
		int newVal = 1 << numrings;
		
		/*
		calculates the number of rings previously moved from first peg.
		Need number of leading ones before 1st 0 on peg 1 so __builtin_clz is 
		used to return number of leading zero bits. Here, this is still undefined
		*/
		int ring1 = (peg1 == bitmask) ? 0 : (32 - __builtin_clz(~(~bitmask | peg1)));
		int ring2 = (peg2 == 0) ? 0 : (32 - __builtin_clz(peg2));
		int ring3 = (peg3 == 0) ? 0 : (32 - __builtin_clz(peg3));

		newVal = newVal - 1 << ring1;

		if (ring2 > ring3) {
			newVal = newVal + (ring1 - __builtin_popcount(peg2));
		}
		else if (ring3 > ring2) {
			newVal = newVal + (ring1 - __builtin_popcount(peg3));
		}
		

		return newVal;
	}
	void alexandra() {

	}
	void ozy() {
		/*  Oswaldo Vielma
			If h(n) is exactly equal to the cost of moving from n to the goal, then 
			A* will only follow the best path and never expand anything else

			| h(n) - h'(n) | = O(log(h'(n)))

			where h'(n) is the optimal heuristic, the exact cost to get from node n to the goal.
			In other words, h(n) will not grow faster than the logarithm of the "perfect heuristic" 
			h'(n) that returns the true distance from x to the goal.
		*/

	}

	vector <Tower> nextStates()const {
		vector <Tower> n;
		for (int i = 0; i < 6; ++i) {
			if (move(i))
				n.push_back(currMove(i));
		}
		return n;
	}
	string toString()const {
		//ostringstream used as a shortcut to access char vals directly as string object.
		ostringstream sbuilder;
		//string arr[100];
		int i = 0;
		sbuilder << "\t peg 1: ";
		for (i = 0; i < 31; ++i) {
			if ((1 << i) & peg1)
				sbuilder << i + 1 << "->";
		}
		
		sbuilder << "\tpeg 2:  ";
		for (i = 0; i < 31; ++i) {
			if ((1 << i) & peg2)
				sbuilder << i + 1 << "->";
		}
		sbuilder << "\tpeg 3: ";

		for (i = 0; i < 31; ++i) {
			if ((1 << i) & peg3)
				sbuilder << i + 1 << "->";
		}

		return sbuilder.str();
	}
};

struct Node {
	Tower gameState;
	Node* parent;
	int cost;
	int estimatedCost;
	vector <Node*> childNode;


	Node(Tower newstate, Node* next) {
		gameState = newstate;
		parent = next;
		if (NULL == next)
			cost = 0;
		else
			cost = next->cost + 1;
		estimatedCost = gameState.cynthia();
	}

	//if new cost is better, update...
	bool costUpdate(int newcost, Node* newparent, multimap<int, Node*>& front) {
		if (newcost < cost) {
			for (multimap<int,Node*>::iterator ct = front.lower_bound(cost); ct != front.upper_bound(cost); ct++) {
				if (ct->second == this) {
					front.erase(ct);
					front.insert(pair<int, Node*>(newcost + estimatedCost, this));
					break;
				}
			}

			cost = newcost;
			parent = newparent;

			//update any children
			for (int i = 0; i < childNode.size(); ++i) {
				childNode[i]->costUpdate(newcost + 1, this, front);
			}
			return true;
		}
		return false;
	}
};

typedef pair<int, Node*> frontPair;
typedef pair<Tower, Node*> newPair;

/*void process_mem_usage(double& vm_usage, double& resident_set)
{
	vm_usage = 0.0;
	resident_set = 0.0;

	// the two fields we want
	unsigned long vsize;
	long rss;
	{
		std::string ignore;
		std::ifstream ifs("/proc/self/stat", std::ios_base::in);
		ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
			>> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
			>> ignore >> ignore >> vsize >> rss;
	}

	long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; 
	vm_usage = vsize / 1024.0;
	resident_set = rss * page_size_kb;
}*/
int main(int argc, char** argv) {

/*	int choice;
	cout << "Hi, welcome to our game of 'Towers of Hanoi' ! \n";
	cout << "Please select from our menu which heuristic you would like to try: \n";
	cout << "\t 1) Cynthia Cordova \n\t 2) Alexandra Hayes \n\t 3) Ozy Vielma";
	cin >> choice;

	switch (choice) {
	case 1:
		cynthia();
		break;
	case 2:
		alexandra();
		break;
	case 3:
		ozy();
		break

	}*/

	Node* winningNode = NULL;
	map <Tower, Node*> generated;


	cout << "\t\tWelcome to or game of 'Towers of Hanoi'! \n\n\n";
	cout << "\t\tStarting with " << numrings << " rings...\n\n";
	cout << "**************************************************\n";
	//maps all nodes to f() cost
	multimap <int, Node*> front;

	if (argc == 2) {
		istringstream argument(argv[1]);
		//sscanf(argument, argv[1]);
		int temp = -1;
		argument >> temp;

		if (temp > 1) {
			numrings = temp;
			bitmask = (1 << numrings) - 1;
		}
	}

	//current node

	auto start = high_resolution_clock::now();
	Node* tempNode = new Node(Tower(), NULL);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);


	//temporary nodes to format output of winning path
	Node* workNode = NULL;
	string outpath, tempstring;


	generated.insert(newPair(tempNode->gameState, tempNode));
	front.insert(frontPair(tempNode->estimatedCost, tempNode));
	

	while (winningNode == NULL and !front.empty()) {

		cout << "\Front Nodes:\n";
		for (multimap<int, Node*>::iterator ct = front.begin();
			ct != front.end(); ++ct) {
			cout << "\t"<< ct->second->gameState.toString()
				<< " h=" << ct->second->estimatedCost
				<< " g=" << ct->second->cost
				<< " f=" << ct->first << endl;
		}
		//node w/ lowest cost
		tempNode = front.begin()->second;
		cout << "\nExpand:\n" << tempNode->gameState.toString() << endl;




		front.erase(front.begin());
		 vector<Tower> tempChildren = tempNode->gameState.nextStates();


		for (unsigned int i = 0; winningNode == NULL and i < tempChildren.size(); ++i) {

			if (tempChildren[i] != tempNode->gameState) {
				cout << "\nGenerated:\n" << tempChildren[i].toString() << '\t';

				if (generated.count(tempChildren[i]) > 0) {
					cout << "\nRegenerated\n";
					if (generated[tempChildren[i]]->costUpdate(tempNode->cost + 1, tempNode, front))
						cout << "\nUpdated \n";
					else
						cout << "\nNo update\n";
				}
				else {
					cout << "New node\t  \t";
					workNode = new Node(tempChildren[i], tempNode);
					generated.insert(newPair(workNode->gameState, workNode));
					front.insert(frontPair(workNode->cost + workNode->estimatedCost, workNode));
					if (workNode->gameState.win()) {
						winningNode = workNode;
					}
				}
				tempNode->childNode.push_back(generated[tempChildren[i]]);

				cout << "g=" << generated[tempChildren[i]]->cost
					<< " h=" << generated[tempChildren[i]]->estimatedCost
					<< " f=" << generated[tempChildren[i]]->cost + generated[tempChildren[i]]->estimatedCost
					<< endl;
				cout << "\n\n*****************************************************\n\n";
			}

		}

		
	}
	

		
		if (winningNode != NULL) {
			cout << "Winning state reached." << endl;
			for (workNode = winningNode; workNode != NULL; workNode = workNode->parent) {
				outpath = workNode->gameState.toString() + outpath;
				if (workNode->parent != NULL)
					outpath = " -> " + outpath;
			}
			cout << outpath << endl;
		}
		else {
			cout << "No path to goal!" << endl;
		}
		cout << "\nTotal number of nodes generated: " << outpath.length() << endl;
		cout << "\nTotal execution tiime for heuristic: " << duration.count() <<  " microseconds" <<endl;
		//remove all nodes 
		for (map <Tower, Node*>::iterator ct = generated.begin(); ct != generated.end(); ++ct) {
			delete ct->second;
		}
		double vm, rss;
		//process_mem_usage(vm, rss);
		//cout << "VM: " << vm << "; RSS: " << rss << endl;

	
		return 0;
	}