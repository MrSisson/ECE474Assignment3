#pragma once
#ifndef EDGES_H
#define EDGES_H

#include "Nodes.h"

#include <string>

using namespace std;

class Nodes;

class Edges {

private:
	string conditionalOperation;
	Nodes* prevNode;
	Nodes* nextNode;

public:
	// constructors
	Edges();
	Edges(string condOp, Nodes* newPrevNode, Nodes* newNextNode);

	//setters
	void setCondtionalOperation(string condOp);
	void setPrevNode(Nodes* newPrevNode);
	void setNextNode(Nodes* newNextNode);

	//getters
	string getConditionalOperation();
	Nodes* getPrevNode();
	Nodes* getNextNode();
};

#endif // !EDGES_H
