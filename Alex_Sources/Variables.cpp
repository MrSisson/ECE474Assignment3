#include "Variables.h"

using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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