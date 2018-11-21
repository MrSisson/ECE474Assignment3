//#include "Edges.h"
//#include "Nodes.h"
//#include "Graph.h"

#include "Variables.h"
#include "ReadInputFile.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//////// F U N C T I O N   M A I N ////////////////////////////
int main(int argc, char* argv[]) {
	
	// check command line arguments
	if (argc != 4) {
		cout << "ERROR: Incorrect arguments." << endl;
		cout << "Correct argumets:\thlsyn cFile latency verilogFile" << endl;
	}

	ifstream inputFilename;
	ofstream outputFilename;

	// Class objects
	Variables var;
	ReadInputFile read;


	inputFilename.open(argv[1]);
	/*cout << "argv0:\t" << argv[0] << endl;
	cout << "argv1:\t" << argv[1] << endl;
	cout << "argv2:\t" << argv[2] << endl;
	cout << "argv3:\t" << argv[3] << endl;*/

	// Get data from input file
	if (inputFilename.is_open()) {

		// fetching variables from input file
		read.fetchVariables(inputFilename, var);

		// Do stuffs....

		// close input file
		inputFilename.close();
	}
	else {	// Error!!
		cout << "Error: Input file doesn't exists." << endl;
		return -1;
	}


	// Generate output file
	outputFilename.open(argv[3]);
	if (outputFilename.is_open()) {

		// writing to output file
		outputFilename << "testing....\n";

		// close output file
		outputFilename.close();
	}
	else {	// Error!!
		cout << "Error: Output file doesn't exists." << endl;
		return -1;
	}
	

	return 0;
}// end of main function