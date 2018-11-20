#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "Edges.h"
#include "Nodes.h"

#include <string>
#include <vector>

using namespace std;

class Graph {

private:
	vector<Nodes> nodes;
	vector<Edges> edges;
	int weight;

public:
	// constructors
	Graph();
	Graph(Nodes newNodes, Edges newEdges, int newWeight);

	//setters
	void setNodes(Nodes newNodes);
	void setEdges(Edges newEdges);
	void setWeight(int newWeight);

	//getters
	vector<Nodes> getNodes();
	vector<Edges> getEdges();
	int getWeight();

	//methods
	// void generateALAPTimeTable(); // unsure where to place this yet
	// void generateList_RSchedule(); // unsure where to plae this yet
};

#endif // !GRAPH_H