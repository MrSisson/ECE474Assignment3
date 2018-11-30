#include "ReadInputFile.h"

using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>

// constructor
ReadInputFile::ReadInputFile(){} // default constructor

//methods

// All empty lines should be ignored
// The netlist file can be assumed to be fully space/tab delimited, i.e. one or more space or tab characters should appear between each token 
// that needs to be parsed, including colons.
// Circuit inputs and outputs can be declared on a line using the formats:
//	# input dataType inputName1, inputName2
//	# output dataType outputName1, outputName2
//	# variable dataType regName1, regName2
// Perform following error checks while fetching variables from input file:
// 1. All names for inputs, outputs, and internal variables should be unique
// 2. All names for inputs, outputs, and internal variables are case sensitive and can consists of any number of
//    letters or digits.
// 3. Input, output, variable declarations should come before component instantiations.
void ReadInputFile::fetchVariables(ifstream &file, Variables &var) {
	string line;	// store single input string
	string token;	// string temp or word temp
	string token2;
	char lastChar;	// use for checking last character of a line or word

	while (!file.eof()) {
		getline(file, line);
		istringstream streamLine(line);
		// cout << line << endl;	// Remove this; debugging only

		if (this->checkOperationLine(line) == true) {	// checks if line is an operation
			
			break;
		}
		else {
			if (line.find("input") != string::npos) {	// found inputs
				streamLine >> token;			// skip first word
				streamLine >> token;			// get data type
				streamLine >> token2;			// get first variable

				// remove any unnecessary ',' in a variable
				lastChar = token2.back();		// get last char of word
				while (lastChar == ',') {
					token2.pop_back();
					var.setName(token2);
					setWidthAndSign(var, token);
					this->inputList.push_back(var);
					streamLine >> token2;		// get subsequent or last variable
					lastChar = token2.back();
				}
				// last variable
				var.setName(token2);
				setWidthAndSign(var, token);
				this->inputList.push_back(var);
			}
			else if (line.find("output") != string::npos) {	// found inputs
				streamLine >> token;			// skip first word
				streamLine >> token;			// get data type
				streamLine >> token2;			// get first variable

				// remove any unnecessary ',' in a variable
				lastChar = token2.back();		// get last char of word
				while (lastChar == ',') {
					token2.pop_back();
					var.setName(token2);
					setWidthAndSign(var, token);
					this->outputList.push_back(var);
					streamLine >> token2;		// get subsequent or last variable
					lastChar = token2.back();
				}
				// last variable
				var.setName(token2);
				setWidthAndSign(var, token);
				this->outputList.push_back(var);
			}
			else if (line.find("variable") != string::npos) {	// found inputs
				streamLine >> token;			// skip first word
				streamLine >> token;			// get data type
				streamLine >> token2;			// get first variable

				// remove any unnecessary ',' in a variable
				lastChar = token2.back();		// get last char of word
				while (lastChar == ',') {
					token2.pop_back();
					var.setName(token2);
					setWidthAndSign(var, token);
					this->registerList.push_back(var);
					streamLine >> token2;		// get subsequent or last variable
					lastChar = token2.back();
				}
				// last variable
				var.setName(token2);
				setWidthAndSign(var, token);
				this->registerList.push_back(var);
			}
		}
	}
	this->checkDuplicatedVariables();
}

// Valid data types include:
//	# Signed integers: Int1, Int2, Int8, Int16, Int32, and Int64
//	# Unsigned integers: UInt1, UInt2, UInt8, UInt16, UInt32, and UInt64
void ReadInputFile::setWidthAndSign(Variables &var, string token) {
	
	// Datawidth 16 (Needs to check 16 bits first before checking 1 bit datawidth)
	if (token.find("UInt16") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(16);
	}
	else if (token.find("Int16") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(16);
	}
	// Datawidth 2
	else if (token.find("UInt2") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(2);
	}
	else if (token.find("Int2") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(2);
	}
	// Datawidth 8
	else if (token.find("UInt8") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(8);
	}
	else if (token.find("Int8") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(8);
	}
	// Datawidth 1
	else if (token.find("UInt1") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(1);
	}
	else if (token.find("Int1") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(1);
	}
	// Datawidth 32
	else if (token.find("UInt32") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(32);
	}
	else if (token.find("Int32") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(32);
	}
	// Datawidth 64
	else if (token.find("UInt64") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(64);
	}
	else if (token.find("Int64") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(64);
	}
	// Datawidth Unknown
	else {
		cout << "Error: Datawidth not specified." << endl;
	}
}

bool ReadInputFile::checkOperationLine(string line) {
	bool flag = false;
	size_t found = line.find_first_of("=+-*/><:?%");
	if (found != string::npos) {
		flag = true;	// flag high: found error!!
	}
	return flag;
}

void ReadInputFile::checkDuplicatedVariables(){
	int exit = -1;
	unsigned int size;
	unsigned int size2;
	vector<Variables> tempList; // temporary list for comparison
	string currName;	// current variable name assigned
	string compName;	// compare current variable name to this

	while (exit == -1) {
		// checking for duplicated variables in inputList
		tempList = inputList;
		size = inputList.size();
		for (int i = 0; i < size; i++) {
			currName = inputList.at(i).getName();
			tempList.erase(tempList.begin());
			size2 = tempList.size();
			for (int j = 0; j < size2; j++) {
				compName = tempList.at(j).getName();
				if (compName.compare(currName) == 0) {
					inputList.erase(inputList.begin() + i); // found duplicate, remove from list
					i = size;
					exit = 1;
					break;
				}
			}
		}

		// checking for duplicated variables in outputList
		tempList = outputList;
		size = outputList.size();
		for (int i = 0; i < size; i++) {
			currName = outputList.at(i).getName();
			tempList.erase(tempList.begin());
			size2 = tempList.size();
			for (int j = 0; j < size2; j++) {
				compName = tempList.at(j).getName();
				if (compName.compare(currName) == 0) {
					outputList.erase(outputList.begin() + i); // found duplicate, remove from list
					i = size;
					exit = 1;
					break;
				}
			}
		}

		// checking for duplicated variables in registerList
		tempList = registerList;
		size = registerList.size();
		for (int i = 0; i < size; i++) {
			currName = registerList.at(i).getName();
			tempList.erase(tempList.begin());
			size2 = tempList.size();
			for (int j = 0; j < size2; j++) {
				compName = tempList.at(j).getName();
				if (compName.compare(currName) == 0) {
					registerList.erase(registerList.begin() + i); // found duplicate, remove from list
					i = size;
					exit = 1;
					break;
				}
			}
		}
		exit = 1;
	}
}