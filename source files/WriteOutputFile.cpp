#include "WriteOutputFile.h"
#include "ReadInputFile.h"
#include "Variables.h"

using namespace std;
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

// constructor
WriteOutputFile::WriteOutputFile() {} // default constructor

// methods

string WriteOutputFile::retrieveDatawidth(int width, string datatype) {
	string str;
	if (datatype.compare("input") == 0) {
		if (width == 1) {
			str = "\tinput ";
		}
		else {
			str += "\tinput [" + to_string(width) + ":0] ";
		}
	}
	else if (datatype.compare("output") == 0) {
		if (width == 1) {
			str = "\toutput ";
		}
		else {
			str += "\toutput [" + to_string(width) + ":0] ";
		}
	}
	else if (datatype.compare("register") == 0) {
		if (width == 1) {
			str = "\tregister ";
		}
		else {
			str += "\tregister [" + to_string(width) + ":0] ";
		}
	}
	else {
		cout << "Error retrieving data type information!!" << endl;
	}
	
	return str;
}

// Circuit inputs and outputs can be declared on a line using the formats:
//	# input dataType inputName1, inputName2
//	# output dataType outputName1, outputName2
//	# variable dataType regName1, regName2
void WriteOutputFile::writeDatatypeInstantiation(ofstream & file, ReadInputFile &read)
{
	unsigned int size;
	string str;
	string str2;
	int width = 0;
	unsigned int index = 0;

	// inputs instantiation
	width = read.inputList.at(0).getWidth(); // retrive datawidth
	str += this->retrieveDatawidth(width, "input");
	size = read.inputList.size();

	while (index != size) {
		while (index < size) {
			if (read.inputList.at(index).getWidth() == width) {
				string vars = read.inputList.at(index).getName();
				str += vars;
				index++;
			}
			if ((index != size) && (read.inputList.at(index).getWidth() == width)) {
				str += ", ";
			}
			else {
				str += ";\n";
				file << str;									// string is complete, write to file
				if (index != size) {
					width = read.inputList.at(index).getWidth();	// get new datawidth
					str = this->retrieveDatawidth(width, "input");
				}
				break;
			}
		}
	}

	index = 0;	  // reset index
	str = "";	  // reset string
	file << "\n"; // insert new line for next instantiation
	// outputs instantiation
	width = read.outputList.at(0).getWidth(); // retrive datawidth
	str += this->retrieveDatawidth(width, "output");
	size = read.outputList.size();

	while (index != size) {
		while (index < size) {
			if (read.outputList.at(index).getWidth() == width) {
				string vars = read.outputList.at(index).getName();
				str += vars;
				index++;
			}
			if ((index != size) && (read.outputList.at(index).getWidth() == width)) {
				str += ", ";
			}
			else {
				str += ";\n";
				file << str;									// string is complete, write to file
				if (index != size) {
					width = read.outputList.at(index).getWidth();	// get new datawidth
					str = this->retrieveDatawidth(width, "output");			// reset string
				}
				break;
			}
		}
	}

	index = 0;	  // reset index
	str = "";	  // reset string
	file << "\n"; // insert new line for next instantiation
	// registers instantiation
	width = read.registerList.at(0).getWidth(); // retrive datawidth
	str += this->retrieveDatawidth(width, "register");
	size = read.registerList.size();

	while (index != size) {
		while (index < size) {
			if (read.registerList.at(index).getWidth() == width) {
				string vars = read.registerList.at(index).getName();
				str += vars;
				index++;
			}
			if ((index != size) && (read.registerList.at(index).getWidth() == width)) {
				str += ", ";
			}
			else {
				str += ";\n";
				file << str;									// string is complete, write to file
				if (index != size) {
					width = read.registerList.at(index).getWidth();	// get new datawidth
					str = this->retrieveDatawidth(width, "register");			// reset string
				}
				break;
			}
		}
	}
	file << "\n\n";
}

void WriteOutputFile::createHLSMHeader(ofstream & file)
{
	file << "module HLSM (Clk, Rst, Start, Done);" << endl << endl;
	file << "\tinput Clk, Rst, Start;" << endl;
	file << "\toutput reg Done;" << endl << endl;
}

void WriteOutputFile::writeGraph(ofstream & file, Graph graph) {
	edges = graph.getEdges();
	nodes = graph.getNodes();
	weight = graph.getWeight();
	
	// Testing --------------------------------------------
	file << "Graph: \n" << "\tWeight: " << weight << "\n";
	for (int temp = 0; temp < 10; temp++) {
		file << "\tNode " << temp << ": " << nodes.at(temp).getOperation() << endl;
		file << "\tEdge " << temp << ": " << edges.at(temp).getConditionalOperation() << endl;
	}
	file << "\n\n";
	// ----------------------------------------------------
}