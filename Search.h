#ifndef SEARCH_H
#define SEARCH_H
#include <vector>
#include <string>
#include "Tree.h"
#include "Node.h"

class AStarSearch {
	int topMostLevel;
	int nodesExpanded;
	std::vector<Tree> listOfTrees;
	std::vector<Node> originalTree;

public:
	AStarSearch(std::string);
	void runSearch();
	int getNodesExpanded();
};

#endif