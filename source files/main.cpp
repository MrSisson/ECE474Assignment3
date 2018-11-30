//#include "Edges.h"
//#include "Nodes.h"
//#include "Graph.h"

#include "Variables.h"
#include "ReadInputFile.h"
#include "WriteOutputFile.h"

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
	WriteOutputFile write;
	
	// Testing Graph Class ------------------------
	Graph graph;
	Nodes tempNode;
	Edges tempEdge;
	int tempWeight = 0;
	string cond = "Test Condition ";
	string op = "Operation ";
	// --------------------------------------------


	inputFilename.open(argv[1]);
	cout << "argv0:\t" << argv[0] << endl;									// DEBUGGING (Remove this)
	cout << "argv1:\t" << argv[1] << endl;									// DEBUGGING (Remove this)
	cout << "argv2:\t" << argv[2] << endl;									// DEBUGGING (Remove this)
	cout << "argv3:\t" << argv[3] << endl;									// DEBUGGING (Remove this)

	// Get data from input file
	if (inputFilename.is_open()) {
		cout << "Opened File for read" << endl;								// DEBUGGING (Remove this)
		// fetching variables from input file
		cout << "Fetching variables" << endl;								// DEBUGGING (Remove this)
		read.fetchVariables(inputFilename, var);
		cout << "Fetching variables completed" << endl;						// DEBUGGING (Remove this)
		// Do stuffs....

		// Testing Graph Class -------------------------------
		for (int temp = 0; temp < 10; temp++) {
			cond = cond.substr(0, 15);
			cond = cond + to_string(tempWeight);
			op = op.substr(0, 10);
			op = op + to_string(tempWeight);

			tempEdge.setCondtionalOperation(cond);
			tempNode.setEdges(&tempEdge);
			tempNode.setOperation(op);

			tempWeight++;
			graph.setEdges(tempEdge);
			graph.setNodes(tempNode);
			graph.setWeight(tempWeight);
		}
		// ----------------------------------------------------

		// close input file
		inputFilename.close();
		cout << "File closed" << endl;										// DEBUGGING (Remove this)
	}
	else {	// Error!!
		cout << "Error: Input file doesn't exists." << endl;
		return -1;
	}


	// Generate output file
	outputFilename.open(argv[3]);
	if (outputFilename.is_open()) {
		cout << "Opened file for write" << endl;							// DEBUGGING (Remove this)
		// writing to output file
		write.createHLSMHeader(outputFilename);
		cout << "Wrote HLSM Header" << endl;								// DEBUGGING (Remove this)
		write.writeDatatypeInstantiation(outputFilename, read);
		cout << "Wrote Datatype Instantiations" << endl;					// DEBUGGING (Remove this)
		write.writeGraph(outputFilename, graph);

		// close output file
		outputFilename.close();
		cout << "File closed" << endl;										// DEBUGGING (Remove this)
	}
	else {	// Error!!
		cout << "Error: Output file doesn't exists." << endl;				// DEBUGGING (Remove this)
		return -1;
	}
	
	cout << "Reached the end of main" << endl;								// DEBUGGING (Remove this)
	return 0;
}// end of main function