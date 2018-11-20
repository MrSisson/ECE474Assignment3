//#include "Edges.h"
//#include "Nodes.h"
//#include "Graph.h"
#include "Variables.h"

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
	vector<Variables> inputList;
	vector<Variables> outputList;
	vector<Variables> registerList;

	// Class objects
	Variables var;

	inputFilename.open(argv[1]);
	if (inputFilename.is_open()) {
		var.fetchVariables(inputFilename, inputList, outputList, registerList);
	}
	else {
		cout << "Error: File doesn't exists." << endl;
		return -1;
	}

	return 0;
}// end of main function