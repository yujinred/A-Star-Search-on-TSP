#include "Node.h"
#include "Tree.h"
#include "Search.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	// maximum size of TSP problem to run
	int TSPSize = 10;
	// total number of instances to run
	int TSPInstance = 10;
	// go through each TSP with i number of nodes
	// and generate the average node expanded for each i
	for (int i = 1; i <= TSPSize; ++i) {
		int average = 0;
		for (int j = 1; j <= TSPInstance; ++j) {
			string fileLocation = "./randTSP/" + to_string(i) + "/instance_" + to_string(j) +".txt";
			AStarSearch searchObj(fileLocation);
			searchObj.runSearch();
			average += searchObj.getNodesExpanded();
		}
		cout << i << " " << average/TSPInstance << endl;
	}
	return 0;
}