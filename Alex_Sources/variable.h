#pragma once
#ifndef VARIABLE_H
#define VARIABLE_H

#include <fstream> 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class variable {

private:
	std::string name;
	bool isSigned;
	int width;
	std::string typeIO;
	std::string dataType;
	std::string operationType;

public:
	variable();	//default constructor
	variable(std::string name, bool isSigned, int width);
	//Variable(std::string name, bool isSigned, int width, std::string typeIO, std::string dataType, std::string operationType);
	void removeSpaces();

	//setters
	void setName(std::string name);
	void setIsSigned(bool isSigned);
	void setWidth(int width);
	void setTypeIO(std::string typeIO);
	void setDataType(std::string dataType);
	void setOperationType(std::string operationType);


	//getters
	std::string getName();
	bool getIsSigned();
	int getWidth();
	std::string getTypeIO(std::string typeIO);
	std::string getDataType(std::string dataType);
	std::string getOperationType(std::string operationType);
};

#endif