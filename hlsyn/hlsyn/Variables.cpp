#include "Variables.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// Constructors
Variables::Variables() {} // default constructor

Variables::Variables(string newName, int newWidth, bool newSign) {
	this->name = newName;
	this->width = newWidth;
	this->isSigned = newSign;
}

// setters
void Variables::setName(string newName) {
	this->name = newName;
}

void Variables::setWidth(int newWidth) {
	this->width = newWidth;
}

void Variables::setIsSigned(bool newSign) {
	this->isSigned = newSign;
}

// getters
string Variables::getName() {
	return this->name;
}

int Variables::getWidth() {
	return this->width;
}

bool Variables::getIsSigned() {
	return this->isSigned;
}

// methods
void Variables::fetchVariables(ifstream &inputFile, vector<Variables> inputList, vector<Variables> outputList, vector<Variables> registerList) {
	string word;
	string token;

	while (inputFile >> word) {
		//cout << word << endl;
		if (word.compare("input") == 0) {	// find inputs
			getline(inputFile, token);
			this->checkSign(token);
		}
		else if (word.compare("output") == 0) {	//	find outputs

		}
		else if (word.compare("variable") == 0) {	// find registers

		}
	}
}

void Variables::checkSign(string token) {
	if (token.find("UInt") != string::npos) {
		this->isSigned = false;
	}
	else if (token.find("Int") != string::npos) {
		this->isSigned = true;
	}
}