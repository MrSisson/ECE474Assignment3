#pragma once
#ifndef NODES_H
#define NODES_H
 
#include "Edges.h" 

#include <string> 
#include <vector>
#include <iostream>

using namespace std;

class Edges;

class Nodes {

private:
	int stateNum;
	int asapTime;
	int alapTime;
	int numCycles;
	int ifStatementLevel;
	vector<Edges> edges;
	string operation;
	vector<string> variablesInvolved; //First variable is always the output

public:
	// constructor
	Nodes();
	Nodes(int newStateNum, Edges newEdges, int newNumCycles, string op);

	//setters
	void setStateNum(int newStateNum);
	void setAsapTime(int newTime);
	void setAlapTime(int newTime);
	void setNumCycles(int newNumCycles);
	void setIfStatementLevel(int level);
	void setEdges(Edges newEdges);
	void setOperation(string op);
	void setVariablesInvolved(vector<string> vbs);

	//getters
	int getStateNum();
	int getAsapTime();
	int getAlapTime();
	int getNumCycles();
	int getIfStatementLevel();
	vector<Edges> getEdges();
	string getOperation();
	vector<string> getVariablesInvolved();
	string getOutputVariable();

	//Methods
	void addEdge(Edges newEdge);
	void printNode();

};

#endif	// !NODES_H