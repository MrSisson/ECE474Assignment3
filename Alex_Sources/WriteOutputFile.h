#pragma once
#ifndef WRITEOUTPUTFILE_H
#define WRITEOUTPUTFILE_H
  
#include "ReadInputFile.h"
#include "Graph.h" 

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
	void writeOperations(ofstream &file, ReadInputFile &read);
	void createHLSMHeader(ofstream & file);
	void writeGraph(ofstream & file, Graph graph);
	

	// test
	vector<Edges> edges;
	vector<Nodes> nodes;
	int weight;

};

#endif // !WRITEOUTPUTFILE_H
