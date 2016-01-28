#include "Tree.h"
#include <fstream>
#include <iostream>
#include <float.h>
#include "heuristics.h"
using namespace std;

// generate the location name, x coordinations, and y coordinations
void Tree::generateTree(string fileLocation) {
	ifstream myFile(fileLocation);

	if (myFile.is_open()) {
		string name;
		int x, y;
		myFile >> size;
		while (myFile >> name >> x >> y) {
			listOfNodes.push_back(Node(name, x, y));
		}
	}
	myFile.close();
}

Tree::Tree(string fileLocation) {
	level = 0;
	currentNode = 0;
	initialDistance = 0;
	loopBack = false;
	generateTree(fileLocation);
	path.push_back(0);
	updateDistance();

}

Tree::Tree(int level, int currentNode, double initialDistance, vector<int> path, vector<Node> listOfNodes) {
	expandedNodes = 0;
	this->level = level;
	this->currentNode = currentNode;
	this->initialDistance = initialDistance;
	this->path = path;
	addToPath(currentNode);
	this->listOfNodes = listOfNodes;

	size = listOfNodes.size();

	loopBack = false;;
	if (this->path.size() == size) {
		loopBack = true;
	}
	
	updateDistance();
}

Tree::Tree() {}

bool Tree::isInPath(int node) {
	for (int i = 0; i < path.size(); ++i) {
		if (node == path[i]) {
			return true;
		}
	}
	return false;
}

void Tree::addToPath(int node) {
	path.push_back(node);
}

void Tree::removeDistance(int index) {
	adjustedDistance[index] = 0;
}


double Tree::getInitialDistance() { return initialDistance; }
int Tree::getCurrentNode() { return currentNode; }
vector<double> Tree::getAdjustedDistance() { return adjustedDistance; }
vector<int> Tree::getPath() { return path; }
vector<Node> Tree::getNodes() { return listOfNodes; }
int Tree::getExpandedNodes() { return expandedNodes; }


double Tree::generateHeuristics(int index) {
	vector<Node> truncatedNodeList;
	for (int i = 0; i < listOfNodes.size(); ++i) {
		if (isInPath(i) || i == index) {			
		} else {
			truncatedNodeList.push_back(listOfNodes[i]);
		}
	}
	HeuristicsGenerator h(truncatedNodeList);
	return h.getHeuristics();
}

void Tree::updateDistance() {

	for (int i = 0; i < size; ++i) {
		if (!isInPath(i) || (loopBack && i == 0)) {
			// our cost so far plus the extra distance to get to the new node
			expandedNodes++;
			double newDistance = initialDistance + listOfNodes[currentNode].distanceToNode(listOfNodes[i]);
			double heuristics = generateHeuristics(i);
			adjustedDistance.push_back(newDistance + heuristics);		
		} else {
			adjustedDistance.push_back(0);
		}

	}
}

int Tree::findSmallestDistance() {
	int result = -1;
	double minDistance = DBL_MAX;
	for (int i = 0; i < adjustedDistance.size(); ++i) {
		if (adjustedDistance[i] != 0) {
			if (adjustedDistance[i] < minDistance) {
				result = i;
				minDistance = adjustedDistance[i];
			}
		}
	}
	return result;
}

void Tree::printTree() {
	for (int i = 0; i < size; ++i) {
		cout << listOfNodes[i].getX() << " " << listOfNodes[i].getY() << endl;
	}
}