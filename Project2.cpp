
#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif
#  define psnip_builtin_ffs(x)   __builtin_ffs(x)
#  define psnip_builtin_clz(x)   __builtin_clz(x)
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include "Header.h"

//#include "Tower.h"
#include "Header.h"

using namespace std;
int cynthia();
void alexandra();
void ozy();

int numrings=3;

int bitmask = (1 << numrings) - 1;

class Tower {
private:
	int peg1, peg2, peg3;

	Tower(int p1, int p2, int p3) {
		peg1 = p1;
		peg2 = p2;
		peg3 = p3;
	}
public:
	//This creates a state with all rings on starting peg.
	Tower() {
		peg1 = bitmask;
		peg2 = 0;
		peg3 = 0;
	}

	bool operator<(const Tower& other) const {
		return (peg1 == other.peg1) ? ((peg2 == other.peg2) ? (peg3 < other.peg3) : (peg2 < other.peg2)) : (peg1 < other.peg1);
	}

	bool operator==(const Tower& other) const {
		return (peg1 == other.peg1) and (peg2 == other.peg2) and (peg3 == other.peg3);
	}

	bool operator!=(const Tower& other) const {
		return (peg1 != other.peg1) or (peg2 != other.peg2) or (peg3 != other.peg3);
	}

	bool isWinning()const {//all rings are on a goal peg
		return peg2 == bitmask or peg3 == bitmask;
	}

	bool isError() const {
		return (peg1 < 0) or (peg2 < 0) or (peg3 < 0);
	}

	bool move(const int m)const {
		int a = (!peg1) ? 33 : __builtin_ffs(peg1);
		int b = (!peg2) ? 33 : __builtin_ffs(peg2);
		int c = (!peg3) ? 33 : __builtin_ffs(peg3);

		switch (m) {
		case 0:
			return a < b;
		case 1:
			return b < c;
		case 2:
			return c < a;
		case 3:
			return a > b;
		case 4:
			return b > c;
		case 5:
			return c > a;
		default:
			return false;
		}
	}

	Tower currMove(const int m)const {
		Tower value = *this;


		int a = (!peg1) ? 33 : __builtin_ffs(peg1);
		int b = (!peg2) ? 33 : __builtin_ffs(peg2);
		int c = (!peg3) ? 33 : __builtin_ffs(peg3);

		a--;
		b--;
		c--;

		if (!move(m))
			return Tower(-1, -1, -1);

		switch (m) {
		//remove the lowest value ring from peg1 and add to peg 2
		case 0:
			value.peg1 ^= (1 << a);
			value.peg2 ^= (1 << a);
			return value;
		//peg2 to peg3 and so on
		case 1:
			value.peg2 ^= (1 << b);
			value.peg3 ^= (1 << b);
			return value;
		case 2:
			value.peg3 ^= (1 << c);
			value.peg1 ^= (1 << c);
			return value;
		case 3:
			value.peg2 ^= (1 << b);
			value.peg1 ^= (1 << b);
			return value;
		case 4:
			value.peg3 ^= (1 << c);
			value.peg2 ^= (1 << c);
			return value;
		case 5:
			value.peg1 ^= (1 << a);
			value.peg3 ^= (1 << a);
			return value;
		}

		return Tower(-1, -1, -1);
	}

	//heuristic function for all items to reach a goal peg
	int h()const{

		int newVal = 1 << numrings;
		int a = (peg1 == bitmask) ? 0 : (32 - __builtin_clz(~(~bitmask | peg1)));


		int b = (peg2 == 0) ? 0 : (32 - __builtin_clz(peg2));
		int c = (peg3 == 0) ? 0 : (32 - __builtin_clz(peg3));

		newVal -= 1 << a;

		if (b > c) {
			newVal += (a - __builtin_popcount(peg2));
		}
		else if (c > b) {
			newVal += (a - __builtin_popcount(peg3));
		}

		return newVal;
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
		std::ostringstream sbuilder;
		string arr[100];

		sbuilder << " peg 1: ";
		for (int i = 0; i < 31; ++i) {
			if ((1 << i) & peg1)
				sbuilder << i + 1 << "->";
		}
		
		sbuilder << "\tpeg 2:  ";
		for (int i = 0; i < 31; ++i) {
			if ((1 << i) & peg2)
				sbuilder << i + 1 << "->";
		}
		sbuilder << "\tpeg 3: ";

		for (int i = 0; i < 31; ++i) {
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
		estimatedCost = gameState.h();
	}


	bool updateCostCond(int newcost, Node* newparent, multimap<int, Node*>& front) {
		if (newcost < cost) {
			for (multimap<int,Node*>::iterator ct = front.lower_bound(cost); ct != front.upper_bound(cost); ct++) {
				if (ct->second == this) {
					front.erase(ct);
					front.insert(std::pair<int, Node*>(newcost + estimatedCost, this));
					break;
				}
			}

			cost = newcost;
			parent = newparent;

			//update any children
			for (unsigned int i = 0; i < childNode.size(); ++i) {
				childNode[i]->updateCostCond(newcost + 1, this, front);
			}
			return true;
		}
		return false;
	}
};

typedef std::pair<int, Node*> frontPair;
typedef std::pair<Tower, Node*> newPair;

int main(int argc, char** argv) {


/*	int choice;
	cout << "Hi, welcome to our game of 'Towers of Hanoi' ! \n";
	cout << "Please select from our menu which heuristic you would like to try: \n";
	cout << "\t 1) Cynthia Cordova \n\t 2) Alexandra Hayes \n\t 3) Ozy Vielma";
	cin >> choice;

	switch (choice) {
	case 1:
		cynthia();

	}*/

	cout << "\t\tWelcome to or game of 'Towers of Hanoi'! \n";
	cout << "\t\tStarting with " << numrings << " rings\n\n";



	Node* winningNode = NULL;
	map <Tower, Node*> generated;

	//maps all nodes to f() cost
	multimap <int, Node*> front;

	if (argc == 2) {
		std::istringstream argument(argv[1]);
		int tempnumrings = -1;
		argument >> tempnumrings;

		if (tempnumrings > 1) {
			numrings = tempnumrings;
			bitmask = (1 << numrings) - 1;
		}
	}

	//current node
	Node* tempNode = new Node(Tower(), NULL);

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
		cout << "\nExpand:\t" << tempNode->gameState.toString() << endl;

		front.erase(front.begin());
		vector<Tower> tempChildren = tempNode->gameState.nextStates();
		for (unsigned int i = 0; winningNode == NULL and i < tempChildren.size(); ++i) {

			if (tempChildren[i] != tempNode->gameState) {
				cout << "\nGenerated:\t" << tempChildren[i].toString() << '\t';

				if (generated.count(tempChildren[i]) > 0) {
					cout << "\nRegenerated\t";
					if (generated[tempChildren[i]]->updateCostCond(tempNode->cost + 1, tempNode, front))
						cout << "\nUpdated F\t";
					else
						cout << "\nNo update\t";
				}
				else {
					cout << "New node\t  \t";
					workNode = new Node(tempChildren[i], tempNode);
					generated.insert(newPair(workNode->gameState, workNode));
					front.insert(frontPair(workNode->cost + workNode->estimatedCost, workNode));
					if (workNode->gameState.isWinning()) {
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

		//remove all nodes 
		for (map <Tower, Node*>::iterator ct = generated.begin(); ct != generated.end(); ++ct) {
			delete ct->second;
		}
		return 0;
	}