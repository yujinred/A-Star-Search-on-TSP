#include "Heuristics.h"
using namespace std;

void HeuristicsGenerator::generateDistances() {
	// only store unique distances from i to j
	for (int i = 0; i < listOfNodes.size(); ++i) {
		for (int j = i+1; j < listOfNodes.size(); ++j) {
			double distance = listOfNodes[i].distanceToNode(listOfNodes[j]);
			listOfDistance.push_back(distance);
			startPos.push_back(i);
			endPos.push_back(j);
		}
	}
}

HeuristicsGenerator::HeuristicsGenerator(vector<Node> allNodes) {
	listOfNodes = allNodes;
	generateDistances();
	sortList();
	minimumSpammingTree();
}

void HeuristicsGenerator::sortList() {
	for (int i = 0; i <listOfDistance.size(); ++i) {
		for (int j = i+1; j < listOfDistance.size(); ++j) {
			if (listOfDistance[i] > listOfDistance[j]) {
				double temp = listOfDistance[i];
				listOfDistance[i] = listOfDistance[j];
				listOfDistance[j] = temp;
				int startTemp = startPos[i];
				startPos[i] = startPos[j];
				startPos[j] = startTemp;
				int endTemp = endPos[i];
				endPos[i] = endPos[j];
				endPos[j] = endTemp;

			}
		}
	}
}

double HeuristicsGenerator::getHeuristics() { return heuristics; }

void HeuristicsGenerator::minimumSpammingTree() {
	// choose the cheapest distance
	// if the coordinate of both distances have been chosen already
	// don't choose that
	int nodesNeeded = listOfNodes.size() - 1;
	if (nodesNeeded <= 0) {
		heuristics = 0;
		return;
	}
	vector<int> nodesConsumed;
	for (int i = 0; i < listOfDistance.size(); ++i) {
		if (nodesNeeded == 0) {
			break;
		}
		bool sameStart = false;
		for (int j = 0; j < nodesConsumed.size(); ++j) {
			if (nodesConsumed[j] == startPos[i]) {
				sameStart = true;
				break;
			}
		}	
		if (!sameStart) {
			nodesConsumed.push_back(startPos[i]);
			nodesConsumed.push_back(endPos[i]);
			heuristics += listOfDistance[i];
			nodesNeeded--;
		} else {
			bool sameEnd = false;
			for (int j = 0; j < nodesConsumed.size(); ++j) {
				if (nodesConsumed[j] == endPos[i]) {
					sameEnd = true;
					break;
				}
			}
			if (!sameEnd) {
				nodesConsumed.push_back(startPos[i]);
				nodesConsumed.push_back(endPos[i]);
				heuristics += listOfDistance[i];
				nodesNeeded--;
			}
		}
	}
}