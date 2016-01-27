#include "Search.h"
#include <float.h>
using namespace std;

AStarSearch::AStarSearch(string filename) {
	topMostLevel = 0;
	
	// intial tree
	listOfTrees.push_back(Tree(filename));
	originalTree = listOfTrees[0].getNodes();
	nodesExpanded = originalTree.size()-1;
}

int AStarSearch::getNodesExpanded() {
	return nodesExpanded;
}

void AStarSearch::runSearch() {
	int pathSize = 0;
	int size = originalTree.size();
	while (pathSize < size) {
		if (size == 1) {
			break;
		}
		topMostLevel++;
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
		
		Tree temp(topMostLevel, nodeToExpand, distanceToNextNode, lastPath, originalTree);
		nodesExpanded += temp.getExpandedNodes();
		listOfTrees.push_back(temp);
	}
	vector<int> finalPath = listOfTrees[topMostLevel].getPath();
	pathSize = finalPath.size();
}