#pragma once
#ifndef READINPUTFILE_H
#define READINPUTFILE_H

#include "Variables.h" 
#include "Operations.h"
#include "Graph.h"

class ReadInputFile {
public:
	// fields
	vector<Variables> inputList;
	vector<Variables> outputList;
	vector<Variables> registerList;
	vector <Operations> operationList;

	// constructor
	ReadInputFile();

	//methods
	void fetchVariables(ifstream &file, Variables &var);
	void fetchOperations(ifstream &file, Operations &op);
	//void fetchStatements(ifstream &file, Statements &state);
	void setWidthAndSign(Variables &var, string token);
	bool checkOperationLine(string line);
	bool checkStatementLine(string line);
    void checkDuplicatedVariables();
	bool checksIfVariableInstantiated(string line);
	int handleOperations(ifstream &file, Graph* graph);
};

#endif // !READINPUTFILE_H