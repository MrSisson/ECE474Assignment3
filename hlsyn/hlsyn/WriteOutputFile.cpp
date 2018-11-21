#include "WriteOutputFile.h"
#include "ReadInputFile.h"
#include "Variables.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

// constructor
WriteOutputFile::WriteOutputFile(){}	// default constructor

void WriteOutputFile::createHLSMHeader(ofstream & file)
{
}

void WriteOutputFile::createDeclarations(ofstream & file, ReadInputFile & read)
{
}

// getters


// methods
//void WriteOutputFile::createHLSMHeader(ofstream &file) {
//	/*file << "moule HLSM (Clk, Rst, Start, Done);" << endl;
//	file << "\tinput Clk, Rst, Start;" << endl;
//	file << "\toutput reg Done;" << endl << endl;*/
//}