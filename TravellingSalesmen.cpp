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
	listOfTrees[0].printTree();

	bool loopBackToRoot = false;
	while (true) {
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
		for (int i = 0; i < lastPath.size(); ++i) {
			cout << originalTree[lastPath[i]].getName() << " ";
		}
		cout << originalTree[nodeToExpand].getName() << endl;
		// all nodes visited, we need to go back
		if (lastPath.size() + 1 == 4) {
			break;
		} else if (lastPath.size() == 4) {
			// the loop is complete
			break;
		}
		
		Tree temp(nodeExpanded, nodeToExpand, distanceToNextNode, lastPath, originalTree);
		cout << "TREE #" << nodeExpanded << endl;
		temp.printTree();
		listOfTrees.push_back(temp);
	}
}

// void AStarSearch::runSearch() {
// 	vector< vector<double> > adjustedDistance;
// 	vector< vector<int> > pathSoFar;
// 	int size = tree.size();

// 	int currentLevel = -1;
// 	int finalNodeToGoTo = 0;

// 	int nodeExpanded = 0;
	
// 	vector<double> totalDistanceTravelled;
// 	totalDistanceTravelled.push_back(0);
//  	while (true) {
 		
//  		bool unlockFirstNode = false;
// 		vector<int> psf; 
// 		if (currentLevel != -1) {
// 			psf = pathSoFar[currentLevel];
// 		} else {
// 			currentLevel = 0;
// 		}
// 		psf.push_back(finalNodeToGoTo);

// 		if (psf.size() == size) {
// 			unlockFirstNode = true;
// 		}
// 		// finish when we visited every node plus itself again
// 		if (psf.size() == size + 1) {
// 			break;
// 		}

// 		for (int i = 0; i < psf.size(); ++i) {
// 			cout << tree[psf[i]].getName() << " ";
// 		}
// 		cout << totalDistanceTravelled[pathSoFar.size()];
// 		cout << endl;
// 		pathSoFar.push_back(psf);

// 		currentLevel = pathSoFar.size() - 1;

// 		vector<double> dist;
// 		// distance to get to every node plus itself after
// 		for (int i = 0; i < size + 1; ++i) {
// 			if (i == size) {
// 				if (unlockFirstNode) {
// 					double g_i = totalDistanceTravelled[currentLevel] + tree[finalNodeToGoTo].distanceToNode(tree[0]);
// 					dist.push_back(g_i);
// 				} else {
// 					dist.push_back(0);
// 				}
// 				break;
// 			}
// 			bool seenNode = false;
// 			for (int j = 0; j < pathSoFar[currentLevel].size(); ++j) {
// 				if (i == pathSoFar[currentLevel][j]) {
// 					seenNode = true;
// 				}
// 			}
// 			if (seenNode) {
// 				dist.push_back(0);
// 			} else {
// 				double g_i = totalDistanceTravelled[currentLevel] + tree[finalNodeToGoTo].distanceToNode(tree[i]);
// 				double h_i = generateHeuristics(i);
// 				dist.push_back(g_i + h_i);
// 			}
// 		}
// 		adjustedDistance.push_back(dist);

// 		double overallMinDistance = -1;
// 		finalNodeToGoTo = findCheapestRoute(adjustedDistance, currentLevel, overallMinDistance);
// 		totalDistanceTravelled.push_back(overallMinDistance);
// 		// remove expanded node
// 		adjustedDistance[currentLevel][finalNodeToGoTo] = 0;
// 		nodeExpanded++;
// 	}

// 	return nodeExpanded;
// }

int main() {
	AStarSearch searchObj("./randTSP/4/instance_1.txt");
	searchObj.runSearch();
	return 0;
}