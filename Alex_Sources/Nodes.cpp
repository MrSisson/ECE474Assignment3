#include "Nodes.h"
 
using namespace std; 
#define underline "\033[4m"
 
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

void Nodes::setAsapTime(int newTime) {
	this->asapTime = newTime;
}

void Nodes::setAlapTime(int newTime) {
	this->alapTime = newTime;
}

void Nodes::setIfStatementLevel(int level) {
	this->ifStatementLevel = level;
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

void Nodes::setVariablesInvolved(vector<string> vbs) {
	variablesInvolved = vbs;
}

// getters
int Nodes::getStateNum() {
	return this->stateNum;
}

int Nodes::getAsapTime() {
	return asapTime;
}

int Nodes::getAlapTime() {
	return alapTime;
}

int Nodes::getIfStatementLevel() {
	return ifStatementLevel;
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

vector<string> Nodes::getVariablesInvolved() {
	return variablesInvolved;
}

string Nodes::getOutputVariable() {
	return variablesInvolved.at(0);
}

//Methods

void Nodes::addEdge(Edges newEdge) {
	edges.push_back(newEdge);
}

void Nodes::printNode() {
	int i = 1;
	cout << "****************************************" << endl;
	cout << "Node: " << stateNum << endl;
	cout << "Operation: " << operation << endl;
	cout << "ASAP: " << asapTime << endl;
	cout << "\tEdges\t" << endl;
	cout << "----------------------------------------" << endl;
	for (Edges edge : edges) {
		cout << i << "." << endl;
		edge.printEdge();
		i++;
	}
}
