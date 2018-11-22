#pragma once
#ifndef READINPUTFILE_H
#define READINPUTFILE_H

#include "Variables.h"

class ReadInputFile {
public:
	// fields
	vector<Variables> inputList;
	vector<Variables> outputList;
	vector<Variables> registerList;

	// constructor
	ReadInputFile();

	//methods
	void fetchVariables(ifstream &file, Variables &var);
	void setWidthAndSign(Variables &var, string token);
	bool checkOperationLine(string line);
    void checkDuplicatedVariables();
};

#endif // !READINPUTFILE_H