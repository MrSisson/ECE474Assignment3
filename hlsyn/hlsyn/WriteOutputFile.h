#pragma once
#ifndef WRITEOUTPUTFILE_H
#define WRITEOUTPUTFILE_H

class WriteOutputFile {
public:
	// fields

	// constructor
	WriteOutputFile();

	// setters

	// getters

	// methods
	void createHLSMHeader(std::ofstream &file);
	void createDeclarations(std::ofstream &file, ReadInputFile &read);
};

#endif // !WRITEOUTPUTFILE_H
