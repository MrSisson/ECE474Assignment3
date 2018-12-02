#pragma once
#ifndef GRAPH_H
#define GRAPH_H

class Edges;
class Nodes;

#include "Edges.h"
#include "Nodes.h"
#include "Operations.h"

#include <string>
#include <vector>

using namespace std;

class Graph {

private:
	vector<Nodes> nodes;
	vector<Edges> edges;
	int weight;
	vector<int> unscheduledList;
	vector<int> alapSchedule;
	vector<int> listRSchedule;

public:
	// constructors
	Graph();
	Graph(Nodes newNodes, Edges newEdges, int newWeight);

	//setters
	void setNodes(Nodes newNodes);
	void setEdges(Edges newEdges);
	void setWeight(int newWeight);
	void setUnscheduledList(int num);
	void setAlapSchedule(int num);
	void setListRSchedule(int num);

	//getters
	vector<Nodes> getNodes();
	vector<Edges> getEdges();
	int getWeight();
	vector<int> getUnscheduleList();
	vector<int> getAlapSchedule();
	vector<int> getListRSchedule();

	//methods
	// void generateALAPTimeTable(); // unsure where to place this yet
	// void generateList_RSchedule(); // unsure where to plae this yet
	//void calculateWeights(Operations &op);
	void createUnscheduledList();
	void createALAPSchedule();
	void createListRSchedule();

	//methods
	void addNode(Nodes newNode);
};

#endif // !GRAPH_H