#pragma once
#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "Operations.h"
#include "Variables.h"

#include "Graph.h"

#include <string>
#include <vector>

using namespace std;

class Statements {

private:
	string cond;
	vector <Operations> operations;		// Holds nested Operations.
	vector <Statements> nestStates;		// Contains locations of nested if-statements.
	Statements* conState;				// If (this is an if) {conState == connecting else} else if (this is an else) {conState = connecting if}.
	bool isIf;							// True: is an if-statement, False: is an else-statement.
	bool isClosed;						// Is true if we found the closing }.  
	bool hasElse;						// Only true if it has an else statement.

public:
	// constructors
	Statements();
	Statements(string cond, string type);
	   
	// Set Functions:
	void setOperation(Operations op);
	void setConState(Statements* conState);
	void setNestState(Statements nestState);
	void setClose();
	void hasElse();

	// Get Functions:


};
#endif	// !STATEMENTS_H