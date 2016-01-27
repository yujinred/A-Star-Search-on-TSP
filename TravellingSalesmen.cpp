#include "Node.h"
#include "Tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <float.h>
using namespace std;

class AStarSearch {
	int nodeExpanded;
	vector<Tree> listOfTrees;
	vector<Node> originalTree;

public:
	AStarSearch(string);
	void runSearch();
	int getNodeExpanded();
};

AStarSearch::AStarSearch(string filename) {
	nodeExpanded = 0;
	// intial tree
	listOfTrees.push_back(Tree(filename));
	originalTree = listOfTrees[0].getNodes();
}

int AStarSearch::getNodeExpanded() {
	return nodeExpanded;
}

void AStarSearch::runSearch() {
	int pathSize = 0;
	while (pathSize < 4) {
		nodeExpanded++;
		int nodeToExpand;
		int prevLevel;
		double distanceToNextNode;
		
		double minDistance = DBL_MAX;
		for (int i = 0; i < listOfTrees.size(); ++i) {
			int prevIndex = listOfTrees[i].getCurrentNode();
			int newIndex = listOfTrees[i].findSmallestDistance();
			if (newIndex != -1) {
				double newDistance = originalTree[newIndex].distanceToNode(originalTree[prevIndex])
						+ listOfTrees[i].getInitialDistance();
				if (newDistance < minDistance) {
					prevLevel = i;
					nodeToExpand = newIndex;
					distanceToNextNode = newDistance;
					minDistance = newDistance;
				}
			}
		}
		listOfTrees[prevLevel].removeDistance(nodeToExpand);

		vector<int> lastPath = listOfTrees[prevLevel].getPath();
		pathSize = lastPath.size();
		
		Tree temp(nodeExpanded, nodeToExpand, distanceToNextNode, lastPath, originalTree);
		listOfTrees.push_back(temp);
	}
	vector<int> finalPath = listOfTrees[nodeExpanded].getPath();
	// print out the data points in the order where the optimal solution travelled
	pathSize = finalPath.size();
	for (int i = 0; i < pathSize; ++i) {
		originalTree[finalPath[i]].printNode();
	}
}

int main() {
	AStarSearch searchObj("./randTSP/4/instance_1.txt");
	searchObj.runSearch();
	cout << searchObj.getNodeExpanded() << endl;
	return 0;
}