#include "Statements.h"

using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Constructors
Statements::Statements() {} // default constructor

Statements::Statements(string cond, string type) {
	this->cond = cond;
	if (type.compare("if") == true) {
		this->isIf = true;
	}
	else {
		this->isIf = false;
	}
	this->isClosed = false;
	this->hasElse = false;
}


void Statements::setOperation(Operations op) {
	this->operations.push_back(op);
}

void Statements::setConState(Statements* conState) {
	this->conState = conState;
}

void Statements::setNestState(Statements nestState) {
	this->nestStates.push_back(nestState);
}

void Statements::setClose() {
	this->isClosed = true;
}

void Statements::hasElse() {
	this->hasElse = true;
}

