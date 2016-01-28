#ifndef TREE_H
#define TREE_H
#include <vector>
#include <string>
#include "Node.h"

class Tree {
	int size;
	int level;
	int currentNode;
	bool loopBack;
	double initialDistance;
	int expandedNodes;
	std::vector<double> adjustedDistance;
	std::vector<int> path;
	std::vector<Node> listOfNodes;

	void generateTree(std::string);
public:
	Tree(std::string);
	Tree(int, int, double, std::vector<int>, std::vector<Node>);
	Tree();

	bool isInPath(int);
	void addToPath(int);
	double generateHeuristics(int);
	void updateDistance();

	// return the index of the node of the smallest travel distance
	int findSmallestDistance();

	void printTree();

	void removeDistance(int);

	int getCurrentNode();
	double getInitialDistance();
	int getExpandedNodes();
	std::vector<double> getAdjustedDistance();
	std::vector<int> getPath();
	std::vector<Node> getNodes();
};

#endif