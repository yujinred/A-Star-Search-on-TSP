#include "Node.h"
#include "Tree.h"
#include "Search.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	int TSPSize;
	int TSPInstance;
	while(true) {
		cout << "Enter the number of nodes you want for your TSP: ";
		cin >> TSPSize;
		if (TSPSize < 1 || TSPSize > 16) {
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
		cout << "Number of Nodes expanded: " << endl;
		cout << searchObj.getNodesExpanded() << endl;
		cout << "What does the final tree like: " << endl;
		searchObj.printResult();
	}
	return 0;
}