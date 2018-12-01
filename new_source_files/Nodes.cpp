#include "Nodes.h"

using namespace std;

// constructors
Nodes::Nodes() {} // default constructor

Nodes::Nodes(int newStateNum, Edges* newEdges, int newNumCycles, string op) {
	this->stateNum = newStateNum;
	this->edges.push_back(newEdges);
	this->numCycles = newNumCycles;
	this->operation = op;
}

// setters
void Nodes::setStateNum(int newStateNum) {
	this->stateNum = newStateNum;
}	

void Nodes::setEdges(Edges* newEdges) {
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

vector<Edges*> Nodes::getEdges() {
	return this->edges;
}

int Nodes::getNumCycles() {
	return this->numCycles;
}

string Nodes::getOperation() {
	return this->operation;
}
