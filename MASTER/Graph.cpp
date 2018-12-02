#include "Graph.h"

using namespace std;

// constructors
Graph::Graph() {} // default constructor

Graph::Graph(Nodes newNodes, Edges newEdges, int newWeight) {
	this->nodes.push_back(newNodes);
	this->edges.push_back(newEdges);
	this->weight = newWeight;
}

// setters
void Graph::setNodes(Nodes newNodes) {
	this->nodes.push_back(newNodes);
}

void Graph::setEdges(Edges newEdges) {
	this->edges.push_back(newEdges);
}

void Graph::setWeight(int newWeight) {
	this->weight = newWeight;
}

void Graph::setUnscheduledList(int num)
{
	this->unscheduledList.push_back(num);
}

void Graph::setAlapSchedule(int num)
{
	this->alapSchedule.push_back(num);
}

void Graph::setListRSchedule(int num)
{
	this->listRSchedule.push_back(num);
}

// getters
vector<Nodes> Graph::getNodes() {
	return this->nodes;
}

vector<Edges> Graph::getEdges() {
	return this->edges;
}

int Graph::getWeight() {
	return this->weight;
}

vector<int> Graph::getUnscheduleList()
{
	return this->unscheduledList;
}

vector<int> Graph::getAlapSchedule()
{
	return this->alapSchedule;
}

vector<int> Graph::getListRSchedule()
{
	return this->listRSchedule;
}

//Methods

void Graph::createUnscheduledList()
{
}

void Graph::createALAPSchedule()
{
}

void Graph::createListRSchedule()
{
}

void Graph::addNode(Nodes newNode) {
	nodes.push_back(newNode);
}

//void Graph::calculateWeights(Operations &op)
//{
//	int tempWeight = -1;
//
//	// Calculate weight by determining type of operation
//
//	this->weight = tempWeight;
//}
