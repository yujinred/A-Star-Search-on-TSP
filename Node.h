#ifndef NODE_H
#define NODE_H
#include <string>

// node class
class Node {
	std::string name;
	int x;
	int y;
	// cost so far plus the heuristics cost
	double adjustedDistance;

public:
	Node(std::string, int, int);
	double distanceToNode(Node&);
	// get functions
	std::string getName();
	int getX();
	int getY();
	
	void printNode();

	double getAdjustedDistance();
	void setAdjustedDistance(double);
};

#endif