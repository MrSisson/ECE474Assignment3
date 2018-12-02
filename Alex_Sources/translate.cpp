#include "translate.h"

using namespace std; 

translate::translate() {

}
vector <string> allVars;
vector <string> allowedOperations{ "=", "==", "+", "-", ">", ">>", "<", "<<", "?", ":", "*" };
bool error = false;
bool translate::readInputFile(ifstream &input, ofstream &output) {
	string entireOutput = "";
	for (string line; getline(input, line); ) {
		//replace spaces in line with | to make things easier for parsing
		replace(line.begin(), line.end(), ' ', '|');
		//If input lines have extra spaces on the end, remove them
		while (line.find("||") != string::npos) {
			line.erase(line.length() - 2, 2);
		}
		//if line contains the word input, output, or wire, call output function to add the variables to the array of all variable names for error checking
		if ((line.find("input") != string::npos && line.find("|") == 5) || (line.find("output") != string::npos && line.find("|") == 6) || (line.find("wire") != string::npos && line.find("|") == 4) || (line.find("register") != string::npos && line.find("|") == 8)) {
			checkInitializationVars(line);
		}
		else if (line.length() == 0) {

		}
		else {
			variableExists(line);
		}
		entireOutput += line + "\n";
		if (error == true) {
			return false;
		}
	}
	return true;
}

void translate::checkInitializationVars(string inputLine) {
	//Create array with all defined variables for error checking
	if (inputLine.find("input") != string::npos || inputLine.find("output") != string::npos || inputLine.find("wire") != string::npos || inputLine.find("register") != string::npos) {
		string tempString = inputLine.substr(inputLine.find("|"));
		tempString.erase(0, 1);
		tempString = tempString.substr(tempString.find("|"));
		tempString.erase(0, 1);
		while (tempString.length() != 0) {
			if (tempString.find(",") != string::npos) {
				allVars.push_back(tempString.substr(0, tempString.find(",")));
				tempString.erase(0, allVars[allVars.size() - 1].length() + 2);
			}
			else {
				allVars.push_back(tempString.substr(0, tempString.find("|")));
				tempString = "";
			}
		}
	}
}

bool translate::variableExists(string inputLine) {
	string intialLine = inputLine;
	string operation = "";
	int numSpaces = count(inputLine.begin(), inputLine.end(), '|');
	bool changedSpaces = false;
	if (inputLine.find("||") != string::npos) {
		numSpaces = numSpaces - 2;
		changedSpaces = true;
	}
	//Check to make sure second char in line is equal sign
	if (inputLine.substr(inputLine.find("|") + 1, 1) != "=") {
		//cout << "no equal sign" << endl;
		error = true;
		return false;
	}
	if (numSpaces == 2) {
		for (int i = 0; i < numSpaces + 1; i++) {
			if (i == 1) {
				inputLine.erase(0, inputLine.find("|") + 1);
			}
			else if (i == 2) {
				if (changedSpaces == true) {
					if (find(allVars.begin(), allVars.end(), inputLine.substr(0, inputLine.find("|"))) != allVars.end()) {
						//Final var exists
					}
					else {
						//cout << "error, " << inputLine << " doesn't exist" << endl;
						error = true;
						return false;
					}
				}
				else {
					if (find(allVars.begin(), allVars.end(), inputLine.substr(0)) != allVars.end()) {
						//Final var exists
					}
					else {
						//cout << "error, " << inputLine << " doesn't exist" << endl;
						error = true;
						return false;
					}
				}

			}
			else if (find(allVars.begin(), allVars.end(), inputLine.substr(0, inputLine.find("|"))) != allVars.end()) {
				//Variable exists, no errors
				inputLine = inputLine.substr(inputLine.find("|"));
				inputLine.erase(0, 1);
			}
			else {
				//cout << inputLine << "   has a variable that isn't defined prior" << endl;
				error = true;
				return false;
			}
		}
	}
	if (numSpaces == 4) {
		for (int i = 0; i < numSpaces + 1; i++) {
			//cout << inputLine << endl;
			if (i == 1) {
				inputLine.erase(0, inputLine.find("|") + 1);
			}
			else if (i == 3) {
				if (find(allowedOperations.begin(), allowedOperations.end(), inputLine.substr(0, inputLine.find("|"))) != allowedOperations.end()) {
					//Operation is valid
				}
				else {
					//Operation is invalid
					//cout << "operation is invalid   1" << endl;
					error = true;
					return false;
				}
				inputLine.erase(0, inputLine.find("|") + 1);
			}
			else if (i == 4) {
				if (changedSpaces == true) {
					if (find(allVars.begin(), allVars.end(), inputLine.substr(0, inputLine.find("|"))) != allVars.end()) {
						//Final var exists
					}
					else {
						//cout << "error, " << inputLine << " doesn't exist" << endl;
						error = true;
						return false;
					}
				}
				else {
					if (find(allVars.begin(), allVars.end(), inputLine.substr(0)) != allVars.end()) {
						//Final var exists
					}
					else {
						//cout << "error, " << inputLine << " doesn't exist" << endl;
						error = true;
						return false;
					}
				}

			}
			else if (find(allVars.begin(), allVars.end(), inputLine.substr(0, inputLine.find("|"))) != allVars.end()) {
				//Variable exists, no errors
				inputLine = inputLine.substr(inputLine.find("|"));
				inputLine.erase(0, 1);
			}
			else {
				//cout << inputLine << "   has a variable that isn't defined prior" << endl;
				error = true;
				return false;
			}
		}
	}

	if (numSpaces == 6) {
		for (int i = 0; i < numSpaces + 1; i++) {
			if (i == 1) {
				inputLine.erase(0, inputLine.find("|") + 1);
			}
			else if (i == 3) {
				if (find(allowedOperations.begin(), allowedOperations.end(), inputLine.substr(0, inputLine.find("|"))) != allowedOperations.end()) {
					//Operation is valid
				}
				else {
					//Operation is invalid
					//cout << "operation is invalid" << endl;
					error = true;
					return false;
				}
				inputLine.erase(0, inputLine.find("|") + 1);
			}
			else if (i == 5) {
				if (find(allowedOperations.begin(), allowedOperations.end(), inputLine.substr(0, inputLine.find("|"))) != allowedOperations.end()) {
					//Operation is valid
				}
				else {
					//Operation is invalid
					//cout << "operation is invalid" << endl;
					error = true;
					return false;
				}
				inputLine.erase(0, inputLine.find("|") + 1);
			}
			else if (i == 6) {
				if (find(allVars.begin(), allVars.end(), inputLine.substr(0)) != allVars.end()) {
					//Final var exists
				}
				else {
					//cout << "error, " << inputLine << " doesn't exist" << endl;
					error = true;
					return false;
				}
			}
			else if (find(allVars.begin(), allVars.end(), inputLine.substr(0, inputLine.find("|"))) != allVars.end()) {
				//Variable exists, no errors
				inputLine = inputLine.substr(inputLine.find("|"));
				inputLine.erase(0, 1);
			}
			else {
				//cout << inputLine << "   has a variable that isn't defined prior" << endl;
				error = true;
				return false;
			}
		}
	}

	return true;
}


int translate::handleOperations(string inputLine, vector<variable> outputs, vector<variable> inputs, vector<variable> registers)
{
	string token, token2;
	vector<string> inputsAndWires;
	istringstream inputLineStream(inputLine);

	bool firstVarBitExtendZero = false;
	bool secondVarBitExtendZero = false;
	bool isSignedModule = false;
	bool validVariable = false;
	unsigned int datawidth = 0;


	//verify output variable
	inputLineStream >> token;
	if (token.empty())
	{
		return 1;		//Valid line (empty, do nothing)
	}
	else if (token.length() >= 2)
	{
		if (token[0] == '/' && token[1] == '/')
		{
			return 1;	//entire line is a comment	//Valid Line (comment, do nothing)
		}
	}
	for (unsigned int i = 0; i < outputs.size(); ++i)
	{
		if (outputs[i].getName() == token)
		{
			validVariable = true;	//Valid Output
			break;
		}
	}
	if (!validVariable)
	{
		for (unsigned int i = 0; i < registers.size(); ++i)
		{
			if (registers[i].getName() == token)
			{
				validVariable = true;	//Valid Output
				break;
			}
		}
	}
	if (!validVariable)
	{
		//cout << "cannot assign this variable: " << token << "\t (must be output or wire)" << '\n';	//ERROR
		return -1;																					//ERROR
	}

	inputLineStream >> token;
	if (token != "=")
	{
		//cout << "invalid operation - output must be set equal to operation" << "\n";	//ERROR
		return -1;																		//ERROR
	}

	//verify first variable
	validVariable = false;
	inputLineStream >> token;

	if (token.length() != 0)
	{
		for (unsigned int i = 0; i < registers.size(); ++i)
		{
			if (registers[i].getName() == token)
			{
				validVariable = true;	//Valid first Variable after operator
				break;
			}
		}
	}
	if (!validVariable)
	{
		for (unsigned int i = 0; i < inputs.size(); ++i)
		{
			if (inputs[i].getName() == token)
			{
				validVariable = true;	//Valid first Variable after operator
				break;
			}
		}
	}
	if (!validVariable)
	{
		for (unsigned int i = 0; i < outputs.size(); ++i)
		{
			if (outputs[i].getName() == token)
			{
				validVariable = true;	//Valid first Variable after operator
				break;
			}
		}
	}
	if (!validVariable)
	{
		//cout << "Could not identity input/wire variable: " << token << " \n";	
		return -1;																//ERROR
	}

	//identify operator
	validVariable = false;
	if (inputLineStream.eof())
	{
		token = "";
	}
	else
	{
		inputLineStream >> token;
	}
	if (inputLineStream.eof())
	{
		token2 = "";
	}
	else
	{
		inputLineStream >> token2;
	}

	//verify second variable
	if (token2.length() != 0)
	{
		for (unsigned int i = 0; i < registers.size(); ++i)
		{
			if (registers[i].getName() == token2)
			{
				validVariable = true;	//Valid second Variable after operator
				break;
			}
		}

		if (!validVariable)
		{
			for (unsigned int i = 0; i < inputs.size(); ++i)
			{
				if (inputs[i].getName() == token2)
				{
					validVariable = true;	//Valid second Variable after operator
					break;
				}
			}
		}
		if (!validVariable)
		{
			for (unsigned int i = 0; i < outputs.size(); ++i)
			{
				if (outputs[i].getName() == token2)
				{
					validVariable = true;	//Valid second Variable after operator
					break;
				}
			}
		}
		if (!validVariable)
		{
			//cout << "Invalid variable: " << token2 << "\n";	//ERROR
			return -1;											//ERROR
		}
	}

	//datawidth = outputVariable->getWidth();		// Possibly don't care about datawidth here anymore

		//identify operator
	if (token.empty())	//REG
	{

		return 1;			//Valid output
	}
	if (validVariable)	//Means there was a second variable, indicating an operation other than x = y
	{
		if (token == "+")		//ADD
		{
			//If token2 is empty, then no variable on other side of operator == error
		}
		else if (token == "-")		//SUB
		{
			
		}
		else if (token == "*")		//MUL
		{
			
		}
		else if (token == "<<")		//SHL
		{
			
		}
		else if (token == ">>")		//SHR
		{
			
		}
		else if (token == "?")		//MUX
		{
			inputLineStream >> token;
			if (token == ":")	//Mux operation continues
			{
				validVariable = false;
				inputLineStream >> token;

				if (token.length() != 0)
				{
					for (unsigned int i = 0; i < registers.size(); ++i)
					{
						if (registers[i].getName() == token)
						{
							validVariable = true;	//Valid third variable after = operator (already verified 2nd before checking operation type
							break;
						}
					}
				}
				if (!validVariable)
				{
					for (unsigned int i = 0; i < inputs.size(); ++i)
					{
						if (inputs[i].getName() == token)
						{
							validVariable = true;	//Valid third variable after = operator
							break;
						}
					}
				}
				if (!validVariable)
				{
					for (unsigned int i = 0; i < outputs.size(); ++i)
					{
						if (outputs[i].getName() == token)
						{
							validVariable = true;	//Valid third variable after = operator
							break;
						}
					}
				}
				if (!validVariable)
				{
					//cout << "Invalid variable: " << token << "\n";		//ERROR
					return -1;												//ERROR missing third variable for mux comparison
				}
			}
			else
			{
				//cout << "Invalid operator: " << token << "\n";		//ERROR
				return -1;												//ERROR
			}

		}
		else		//must be comparator or invalid operator
		{
			//determine output to wire
			if (token == ">")
			{
					
			}
			else if (token == "==")
			{
					
			}
			else if (token == "<")
			{
					
			}
			else
			{
				//cout << "Invalid operator: " << token << "\n";	//ERROR
				return -1;												//ERROR
			}

			//cout << translatedLine << "\n";
			return 1;							//valid output
		}
	}
	else
	{
		//cout << "Incomplete operation \n";			//ERROR
		return -1;												//ERROR
	}

	return 1;
}