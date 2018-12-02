#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>
#include <vector>

using namespace std;

class Variables {

private:
	string name;
	int width;
	bool isSigned;

public:
	// constructors
	Variables();
	Variables(string newName, int newWidth, bool newSign);

	//setters
	void setName(string newName);
	void setWidth(int newWidth);
	void setIsSigned(bool newSign);

	//getters
	string getName();
	int getWidth();
	bool getIsSigned();

	
};
#endif	// !VARIABLES_H