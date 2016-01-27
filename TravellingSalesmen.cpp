#include "Node.h"
#include "Tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <float.h>
using namespace std;

class AStarSearch {
	int topMostLevel;
	int nodesExpanded;
	vector<Tree> listOfTrees;
	vector<Node> originalTree;

public:
	AStarSearch(string);
	void runSearch();
	int getNodesExpanded();
};

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
	// print out the data points in the order where the optimal solution travelled
	pathSize = finalPath.size();
}

int main() {
	int TSPSize;
	int TSPInstance;
	while(true) {
		cout << "Enter the number of nodes you want for your TSP: ";
		cin >> TSPSize;
		if (TSPSize <= 0) {
			cout << "Invalid TSP size; program will now terminate" << endl;
			break;
		}
		cout << "Which instance of TSP do you want: ";
		cin >> TSPInstance;
		if (TSPInstance < 1 || TSPInstance > 10) {
			cout << "Invalid TSP instance, please enter a number from 1 to 10" << endl;
			break;
		}
		string fileLocation = "./randTSP/" + to_string(TSPSize) + "/instance_" + to_string(TSPInstance) +".txt";
		AStarSearch searchObj(fileLocation);
		searchObj.runSearch();
		cout << searchObj.getNodesExpanded() << endl;
	}
	return 0;
}