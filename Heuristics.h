#ifndef HEURISTICS_H
#define HEURISTICS_H
#include "Node.h"
#include <vector>

// this class creates the heuristics value for a node by using 
// a minimum spanning tree with the given nodes
class HeuristicsGenerator {
	double heuristics;
	std::vector<Node> listOfNodes;
	std::vector<double> listOfDistance;
	std::vector<int> startPos;
	std::vector<int> endPos;
	std::vector< std::vector<int> > set;

	void generateDistances();
	void sortList();
	void minimumSpammingTree();
	bool findSet(int, int);
	void joinSet(int, int);
public:
	HeuristicsGenerator(std::vector<Node>);
	double getHeuristics();
};


#endif