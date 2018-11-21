#include "ReadInputFile.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;


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
	char temp;
	char lastChar;	// use for checking last character of a line or word

	while (!file.eof()) {
		getline(file, line);
		istringstream streamLine(line);
		// cout << line << endl;	// Remove this; debugging only

		if (this->checkFirstLine(line) == true) {	// check error in first line
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

bool ReadInputFile::checkFirstLine(string line) {
	bool flag = false;
	size_t found = line.find_first_of("=+-*/><:?%");
	if (found != string::npos) {
		flag = true;	// flag high: found error!!
		cout << "Error: Input, output, variable declarations should come before component instantiations." << endl;
	}
	return flag;
}