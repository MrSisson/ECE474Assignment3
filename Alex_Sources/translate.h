#pragma once
#ifndef TRANSLATE_H
#define TRANSLATE_H

 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "variable.h"


using namespace std;

class translate {

public:

	translate();	//default constructor
	bool readInputFile(ifstream &input, ofstream &output);	//reads the input file
	void checkInitializationVars(string inputLine);
	bool variableExists(string inputLine);
	string handleOperations(int num, string inputLine, vector<variable> outputs, vector<variable> inputs, vector<variable> wires); //also valids line

};

#endif 