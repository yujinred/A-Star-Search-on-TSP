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
	heuristics = 0;
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

bool HeuristicsGenerator::findSet(int index, int index2) {
	int set1 = -1;
	int set2 = -1;
	for (int i = 0; i < set.size(); ++i) {
		for (int j = 0; j < set[i].size(); ++j) {
			if (index == set[i][j]) {
				set1 = i;
			}
			if (index2 == set[i][j]) {
				set2 = i;
			}
		}
	}

	if ((set1 == -1)|| (set2 == -1)) {
		return false;
	}

	return set1 == set2;
}

void HeuristicsGenerator::joinSet(int index, int index2) {
	int set1 = -1;
	int set2 = -1;
	for (int i = 0; i < set.size(); ++i) {
		for (int j = 0; j < set[i].size(); ++j) {
			if (index == set[i][j]) {
				set1 = i;
			}
			if (index2 == set[i][j]) {
				set2 = i;
			}
		}
	}
	if (set1 == -1 && set2 == -1) {
		vector<int> temp;
		temp.push_back(index);
		temp.push_back(index2);
		set.push_back(temp);
		return;
	} else if (set1 == -1) {
		set[set2].push_back(index);
		return;
	} else if (set2 == -1) {
		set[set1].push_back(index2);
		return;
	}

	for (int i = 0; i < set[set2].size(); ++i) {
		set[set1].push_back(set[set2][i]);
		set.erase(set.begin()+set2);
	}
}


void HeuristicsGenerator::minimumSpammingTree() {
	for (int i = 0; i < listOfDistance.size(); ++i) {
		if (!findSet(startPos[i],endPos[i])) {
			heuristics += listOfDistance[i];
			joinSet(startPos[i], endPos[i]);
		}
	}
}