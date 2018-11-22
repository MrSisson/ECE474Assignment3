#pragma once
#ifndef WRITEOUTPUTFILE_H
#define WRITEOUTPUTFILE_H

#include "ReadInputFile.h"

using namespace std;
#include <fstream>

class WriteOutputFile {
private:
	// fields
public:
	// constructor
	WriteOutputFile();

	// setters

	// getters

	// methods
	string retrieveDatawidth(int width, string datatype);
	void writeDatatypeInstantiation(ofstream &file, ReadInputFile &read);
	void createHLSMHeader(ofstream & file);
	
};

#endif // !WRITEOUTPUTFILE_H
