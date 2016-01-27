#include "Node.h"
#include <math.h>
#include <iostream>
using namespace std;

Node::Node(string name, int x, int y) {
	this->name = name;
	this->x = x;
	this->y = y;
}

double Node::distanceToNode(Node& node) {
	int diffx = x - node.getX();
	int diffy = y - node.getY();

	if ((diffx == 0) && (diffy == 0)) {
		return 0;
	}

	return sqrt(diffx * diffx + diffy * diffy);
}

string Node::getName() {return name; } 
int Node::getX() {return x; }
int Node::getY() {return y; }

double Node::getAdjustedDistance() {
	return adjustedDistance;
}
void Node::setAdjustedDistance(double newDistance) {
	adjustedDistance = newDistance;
}

void Node::printNode() {
	cout << x << " " << y << endl;
}
