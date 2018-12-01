#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// Headers 
#include "variable.h"
#include "translate.h"
#include "Graph.h"

using namespace std;

vector<variable> inputVariables;
vector<variable> outputVariables;
vector<variable> wireVariables;
vector<variable> registerVariables;
vector<string> parameters;
vector<string> outputFileStrings;
int count = 0;

///////////// Functions Declaration //////////////////////////////////////////////////////////////////////////////
void printParameters();
void addVariables(string type, string name, bool isSigned, int width);
string convertTypes(string line);
bool checkInput(string name);
string operations(int num, string line);
///////////// FU N C T I O N   M A I N //////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

	if (argc != 4) {
		cout << "ERROR: Incorrect arguments." << endl;
		cout << "Correct argumets:\thlsyn cFile latency verilogFile" << endl;
		return 0;
	}

	string inputFileLine;
	string moduleLine = "`timescale 1ns / 1ps\n\nmodule ";
	
	//opening input and output files
	translate mainThread;
	ifstream inputFile;
	ofstream outputFile;


	inputFile.open(argv[1]);
	if (inputFile.is_open()) {
		string clkrst = "input Int1 Clk, Rst";
		string convert = convertTypes(clkrst);
		outputFileStrings.push_back(convert);
		int counter = 1;
		for (inputFileLine; getline(inputFile, inputFileLine); ) {
				string convert = convertTypes(inputFileLine);
				if ((convert.compare("opp") != 0)&& (convert.compare("") != 0)){
					outputFileStrings.push_back(convert);
				}
				else { 
				}
		}
		inputFile.close();
	}

	outputFileStrings.push_back("\n\n");
	printParameters();

	inputFile.open(argv[1]);
	if (inputFile.is_open()) {
			int num = 0;
				for (inputFileLine; getline(inputFile, inputFileLine); ) {
					//outputFileStrings.push_back(mainThread.handleOperations(num, inputFileLine, outputVariables, inputVariables, wireVariables));
						num += 1;
				}
			inputFile.close();
	}
	else {	
		cout << "Could not open input file: " << argv[1] << "." << endl;
	}

	/***********************PRINT TO OUTPUT**********************************************/

	//outputFileStrings.push_back("\n\n");
	printParameters();
	for (unsigned int i = 0; i < parameters.size(); i++) {
		outputFileStrings.insert(outputFileStrings.begin(), parameters[i]);
	}
	outputFile.open(argv[2]);
	string removetxt = ".txt";
	string moduleName = argv[1];
	if (moduleName.substr(moduleName.size() - removetxt.size()) == removetxt) {
		moduleName = moduleName.substr(0, moduleName.size() - removetxt.size());
	}
	moduleLine += moduleName;
	moduleLine += "(";
	for (unsigned int i = 0; i < inputVariables.size(); i++) {
		moduleLine += inputVariables.at(i).getName();
		moduleLine += ", ";
	}
	for (unsigned int i = 0; i < outputVariables.size(); i++) {
		if (i == outputVariables.size()-1) {
			moduleLine += outputVariables.at(i).getName();
			moduleLine += ");\n\n";
		}
		else {
			moduleLine += outputVariables.at(i).getName();
			moduleLine += ", ";
		}
		
	}
	outputFile << moduleLine;
	for (unsigned int i = 0; i < outputFileStrings.size(); i++) {
		outputFile << outputFileStrings.at(i);
	}
	outputFile << "\n\nendmodule";
	outputFile.close();
	/////////////////////////////////////////////////////////////////////////////////////////////
	//cin.get();

	return 0;
}//main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***********************FUNCTION DEFINITIONS*******************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// printParameters //
void printParameters() {
	string outString = "";
	for (unsigned int i = 0; i < inputVariables.size(); i++) {
		string param = "";
		if (inputVariables[i].getIsSigned()) {
			param += "parameter Int" + to_string(inputVariables[i].getWidth()) + " = " + to_string(inputVariables[i].getWidth());
		}
		else {
			param += "parameter UInt" + to_string(inputVariables[i].getWidth()) + " = " + to_string(inputVariables[i].getWidth());

		}
		parameters.push_back(param + ";\n");
	}
	for (unsigned int i = 0; i < outputVariables.size(); i++) {
		string param = "";
		if (outputVariables[i].getIsSigned()) {
			param += "parameter Int" + to_string(outputVariables[i].getWidth()) + " = " + to_string(outputVariables[i].getWidth());
		}
		else {
			param += "parameter UInt" + to_string(outputVariables[i].getWidth()) + " = " + to_string(outputVariables[i].getWidth());

		}
		parameters.push_back(param + ";\n");
	}
	for (unsigned int i = 0; i < wireVariables.size(); i++) {
		string param = "";
		if (wireVariables[i].getIsSigned()) {
			param += "parameter Int" + to_string(wireVariables[i].getWidth()) + " = " + to_string(wireVariables[i].getWidth());
		}
		else {
			param += "parameter UInt" + to_string(wireVariables[i].getWidth()) + " = " + to_string(wireVariables[i].getWidth());
		}
		parameters.push_back(param + ";\n");
	}
	for (unsigned int i = 0; i < registerVariables.size(); i++) {
		string param = "";
		if (registerVariables[i].getIsSigned()) {
			param += "parameter Int" + to_string(registerVariables[i].getWidth()) + " = " + to_string(registerVariables[i].getWidth());
		}
		else {
			param += "parameter UInt" + to_string(registerVariables[i].getWidth()) + " = " + to_string(registerVariables[i].getWidth());
		}
		parameters.push_back(param + ";\n");
	}

	sort(parameters.begin(), parameters.end());
	parameters.erase(unique(parameters.begin(), parameters.end()), parameters.end());
}

// addVariables //
void addVariables(string type, string name, bool isSigned, int width) {
	
	if (name.compare("") != 0) {
		
		for (int i = 0; i < name.length(); i++){
			if (name.at(i) == ' ' || name.at(i) == '\t'){
				name.erase(i, 1);
					i--;
				}
		}

		if (type.compare("input ") == 0) {  //if variable is an input, add to inputVariables vector
			variable var = variable(name, isSigned, width);
			inputVariables.push_back(var);
		}

		else if (type.compare("output ") == 0) {  //if variable is an output, add to outputVariables vector
			variable var = variable(name, isSigned, width);
			outputVariables.push_back(var);
		}

		else if (type.compare("wire ") == 0) {  //if variable is an wire, add to wireVariables vector
			variable var = variable(name, isSigned, width);
			wireVariables.push_back(var);
		}

		else if (type.compare("register ") == 0) {  //if variable is an register, add to registerVariables vector
			variable var = variable(name, isSigned, width);
			registerVariables.push_back(var);
		}
	}

}

// convertTypes //
string convertTypes(string line) {
	string inString = line;
	string outString = "";
	string splitterVar = ", ";
	if (line.compare("") != 0) {
		//1 BIT
		if ((line.find("Int1") != string::npos) && !(line.find("Int16") != string::npos)) {

			// UNSIGNED INPUT
			if (line.find("UInt1") != string::npos) {
				//truncate up to UInt1
				string splitterSize = "UInt1 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				//outString += "[Uint1-1:0] "; // no need because these are 1 bit variables
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, false, 1);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, false, 1);
			}
			//SIGNED INPUTS
			else {
				//truncate up to Int1
				string splitterSize = "Int1 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				//outString += "[Uint1-1:0] "; // no need because these are 1 bit variables
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, true, 1);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, true, 1);
			}
		}

		// 2 BIT
		else if (line.find("Int2") != string::npos) {

			// UNSIGNED INPUT
			if (line.find("UInt2") != string::npos) {
				//truncate up to UInt2
				string splitterSize = "UInt2 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				outString += "[Uint2-1:0] "; // no need because these are 1 bit variables
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, false, 2);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, false, 2);
			}
			//SIGNED INPUTS
			else {
				//truncate up to Int2
				string splitterSize = "Int2 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				outString += "[Int2-1:0] ";
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, true, 2);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, true, 2);
			}
		}

		//8 BIT
		else if (line.find("Int8") != string::npos) {

			// UNSIGNED INPUT
			if (line.find("UInt8") != string::npos) {
				//truncate up to UInt8
				string splitterSize = "UInt8 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				outString += "[Uint8-1:0] ";
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, false, 8);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, false, 8);
			}
			//SIGNED INPUTS
			else {
				//truncate up to Int8
				string splitterSize = "Int8 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				outString += "[Int8-1:0] ";
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, true, 8);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, true, 8);
			}
		}

		//16 BIT
		else if (line.find("Int16") != string::npos) {

			// UNSIGNED INPUT
			if (line.find("UInt16") != string::npos) {
				//truncate up to UInt16
				string splitterSize = "UInt16 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				outString += "[Uint16-1:0] ";
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, false, 16);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, false, 16);
			}
			//SIGNED INPUTS
			else {
				//truncate up to Int16
				string splitterSize = "Int16 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				outString += "[Int16-1:0] ";
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, true, 16);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, true, 16);
			}
		}

		//32 BIT
		else if (line.find("Int32") != string::npos) {
			// UNSIGNED INPUT
			if (line.find("UInt32") != string::npos) {
				//truncate up to UInt32
				string splitterSize = "UInt32 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				outString += "[Uint32-1:0] ";
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, false, 32);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, false, 32);
			}
			//SIGNED INPUTS
			else {
				//truncate up to Int32
				string splitterSize = "Int32 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				outString += "[Int32-1:0] ";
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, true, 32);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, true, 32);
			}
		}

		//64 BIT
		else if (line.find("Int64") != string::npos) {

			// UNSIGNED INPUT
			if (line.find("UInt64") != string::npos) {
				//truncate up to UInt64
				string splitterSize = "UInt64 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				outString += "[Uint64-1:0] ";
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, false, 64);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, false, 64);
			}
			//SIGNED INPUTS
			else {
				//truncate up to Int64
				string splitterSize = "Int64 ";
				outString += inString.substr(0, inString.find(splitterSize)); // outstring = "input | output | wire"
				string temp = outString;
				inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				outString += "[Int64-1:0] ";
				outString += inString;
				//look for the variables
				size_t pos = 0;
				string token;
				while (((pos = inString.find(splitterVar)) != string::npos) && inString != "") {
					token = inString.substr(0, pos);
					addVariables(temp, token, true, 64);
					inString.erase(0, pos + splitterVar.length());
				}
				addVariables(temp, inString, true, 64);
			}
		}
		else {
			return "opp";
		}

		if (outString.find("register") != string::npos) {
			string err = "ister";
			outString.erase(3, 5);
		}

		return (outString + ";\n");
	}
	else {
		return ""; 
	}
}

// checkInput //
bool checkInput(string name) {
	bool inputIsValid = false;
	for(unsigned int i = 0; i < inputVariables.size(); i++) {
		if (name.compare(inputVariables[i].getName()) == 0) {
			inputIsValid = true;
		}
	}

	for (unsigned int i = 0; i < wireVariables.size(); i++) {
		if (name.compare(wireVariables[i].getName()) == 0) {
			inputIsValid = true;
		}
	}

	for (unsigned int i = 0; i < registerVariables.size(); i++) {
		if (name.compare(registerVariables[i].getName()) == 0) {
			inputIsValid = true;
		}
	}
	return inputIsValid;
}

string operations(int count, string line) {
	string inString = line;
	string outputVar = "";
	bool outputIsValid = false;

	if (line.find("=") != string::npos) {
		string splitterSize = " = ";
		outputVar = inString.substr(0, inString.find(splitterSize));
		inString.erase(0, inString.find(splitterSize) + splitterSize.length());

		for (unsigned int i = 0; i < outputVariables.size(); i++) {
			if (outputVar.compare(outputVariables[i].getName()) == 0) {
				outputIsValid = true;
			}
		}
		for (unsigned int i = 0; i < wireVariables.size(); i++) {
			if (outputVar.compare(wireVariables[i].getName()) == 0) {
				outputIsValid = true;
			}
		}
		for (unsigned int i = 0; i < registerVariables.size(); i++) {
			if (outputVar.compare(registerVariables[i].getName()) == 0) {
				outputIsValid = true;
			}
		}

		if (outputIsValid) {

			//Addition
			if (inString.find("+") != string::npos) {
				string splitterSize = " + ";
				string firstInput = inString.substr(0, inString.find(splitterSize));
				string secondInput = inString.erase(0, inString.find(splitterSize) + splitterSize.length());
				if (checkInput(firstInput) && checkInput(secondInput)) {
					
				}
				else {
					return "ERROR";
				}
			}

			//Subtraction
			else if (inString.find("-") != string::npos) {

			}

			//Multiplier
			else if (inString.find("*") != string::npos) {

			}

			//COMP (gt output)
			else if ((inString.find(">") != string::npos) && !(inString.find(">>")!= string::npos)){

			}

			//COMP (lt output)
			else if ((inString.find("<") != string::npos) && !(inString.find("<<") != string::npos)) {
		
			}

			//COMP (eq output)
			else if (inString.find("==") != string::npos) {

			}

			//mux
			else if ((inString.find("?") != string::npos) && (inString.find(":") != string::npos)) {

			}

			//SHR
			else if (inString.find(">>") != string::npos) {

			}

			//SHL
			else if (inString.find("<<") != string::npos) {

			}

		}


		else {
			return "ERROR";
		}
	}

	else {
		//not an operation
		return "";
	}
}