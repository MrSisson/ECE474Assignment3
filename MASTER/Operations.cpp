#include "Operations.h"

using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Constructors
Operations::Operations() {} // default constructor

Operations::Operations(string newOperation) {
	this->operation = newOperation;
	/*
	this->input1 = newIn1;
	this->input2 = newIn2;
	this->sel = newSel;
	this->output = newOut;
	*/
}

// setters
void Operations::setOperation(string newOperation) {
	this->operation = newOperation;
}
/*
void Operations::setInput1(Variables newIn1) {
	this->input1 = newIn1;
}

void Operations::setInput2(Variables newIn2) {
	this->input2 = newIn2;
}

void Operations::setSel(Variables newSel) {
	this->sel = newSel;
}

void Operations::setOutput(Variables newOut) {
	this->output = newOut;
}
*/

// getters
string Operations::getOperation() {
	return this->operation;
}
/*
Variables Operations::getIn1() {
	return this->input1;
}

Variables Operations::getIn2() {
	return this->input2;
}

Variables Operations::getSel () {
	return this->sel;
}

Variables Operations::getOut() {
	return this->output;
}
*/

// methods
