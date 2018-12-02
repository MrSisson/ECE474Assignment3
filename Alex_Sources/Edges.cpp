#include "Edges.h"
  
#include <string>
 
using namespace std;

Edges::Edges() {} // default constructor

Edges::Edges(string condOp, Nodes* newPrevNode, Nodes* newNextNode) {
	this->conditionalOperation = condOp;
	this->prevNode = newPrevNode;
	this->nextNode = newNextNode;
}

// setters
void Edges::setCondtionalOperation(string condOp) {
	this->conditionalOperation = condOp;
}

void Edges::setPrevNode(Nodes* newPrevNode) {
	this->prevNode = newPrevNode;
}

void Edges::setNextNode(Nodes* newNextNode) {
	this->nextNode = newNextNode;
}

// getters
string Edges::getConditionalOperation() {
	return this->conditionalOperation;
}

Nodes* Edges::getPrevNode() {
	return this->prevNode;
}

Nodes* Edges::getNextNode() {
	return this->nextNode;
}

//Methods
void Edges::printEdge() {
	//cout << "\tPrevious: Node-" << prevNode->getStateNum() << endl;
	cout << "\tNext Node:     Node-" << nextNode->getStateNum() << endl;
}
