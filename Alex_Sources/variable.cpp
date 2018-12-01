#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// Headers 
#include "variable.h"
#include "translate.h"

using namespace std;

// Constructors:
variable::variable() {

}

variable::variable(std::string name, bool isSigned, int width) {
	this->name = name;
	this->isSigned = isSigned;
	this->width = width;
}

//Variable(std::string name, bool isSigned, int width, std::string typeIO, string dataType, string operationType) {
//	this->name = name;
//	this->isSigned = isSigned;
//	this->width = width;
//	this->typeIO = typeIO;
//	this->dataType = dataType;
//	this->operationType = operationType;
//}

//setters
void variable::setName(string name)
{
	this->name = name;
}

void variable::setIsSigned(bool isSigned)
{
	this->isSigned = isSigned;
}

void variable::setWidth(int width)
{
	this->width = width;
}

void variable::setTypeIO(string typeIO) {
	this->typeIO = typeIO;
}

void variable::setDataType(string dataType) {
	this->dataType = dataType;
}

void variable::setOperationType(string operationType) {
	this->operationType = operationType;
}


//getters
string variable::getName()
{
	return this->name;
}

bool variable::getIsSigned()
{
	return this->isSigned;
}

int variable::getWidth()
{
	return this->width;
}

string variable::getTypeIO(string typeIO) {
	return this->typeIO;
}

string variable::getDataType(string dataType) {
	return this->dataType;
}

string variable::getOperationType(string operationType) {
	return this->operationType;
}

void variable::removeSpaces() {
	for (int i = 0; i < this->name.size(); i++) {
		if (this->name[i] == ' ') {
			//this->name[i] = '\0';
			//this->name.erase(0,1);
			this->name.erase(0, this->name.find(' ') + 1);


		}
	}
}
