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
	bool checkFirstLine(string line);
};

#endif // !READINPUTFILE_H