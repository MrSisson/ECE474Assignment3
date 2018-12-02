#include "Nodes.h"
<<<<<<< HEAD:Alex_Sources/Nodes.cpp
 
using namespace std; 
 
=======

using namespace std;

>>>>>>> e5b349f0ccb7050e3c7a7269de31a802433ce09d:MASTER/Nodes.cpp
// constructors
Nodes::Nodes() {} // default constructor

Nodes::Nodes(int newStateNum, Edges newEdges, int newNumCycles, string op) {
	this->stateNum = newStateNum;
	this->edges.push_back(newEdges);
	this->numCycles = newNumCycles;
	this->operation = op;
}

// setters
void Nodes::setStateNum(int newStateNum) {
	this->stateNum = newStateNum;
}

void Nodes::setEdges(Edges newEdges) {
	this->edges.push_back(newEdges);
}

void Nodes::setNumCycles(int newNumCycles) {
	this->numCycles = newNumCycles;
}

void Nodes::setOperation(string op) {
	this->operation = op;
}

// getters
int Nodes::getStateNum() {
	return this->stateNum;
}

vector<Edges> Nodes::getEdges() {
	return this->edges;
}

int Nodes::getNumCycles() {
	return this->numCycles;
}

string Nodes::getOperation() {
	return this->operation;
}

//Methods

void Nodes::addEdge(Edges newEdge) {
	edges.push_back(newEdge);
}
