#pragma once
#ifndef OPERATIONS_H
#define OPERATIONS_H

class Variables;
 
#include "Variable.h"

#include <string>
#include <vector>

using namespace std;

class Operations {
private:
	/*	Actually going to comment this out cause im pretty sure we dont actually need this much info to print properly.
	Variables input1;
	Variables input2;
	Variables sel;
	Variables output;
	*/
	string operation; // full operation.

public:
	// constructors
	Operations();
	Operations(string newOperation);

	//setter
	void setOperation(string newOperation);
	/*
	void setInput1(Variables newIn1);
	void setInput2(Variables newIn2);
	void setSel(Variables newSel);
	void setOutput(Variables newOut);
	*/

	//getters
	string getOperation();
	/*
	Variables getIn1();
	Variables getIn2();
	Variables getSel();
	Variables getOut();
	*/

};

#endif