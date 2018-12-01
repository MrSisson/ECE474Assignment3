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


string translate::handleOperations(int num, string inputLine, vector<variable> outputs, vector<variable> inputs, vector<variable> wires)
{
	string token, token2;
	vector<string> inputsAndWires;
	istringstream inputLineStream(inputLine);

	variable *outputVariable, *firstVariable, *secondVariable;
	variable *thirdVariable = NULL; //only used for mux
	string translatedLine;
	bool firstVarBitExtendZero = false;
	bool secondVarBitExtendZero = false;
	bool isSignedModule = false;
	bool hasThirdInput = false;
	bool validVariable = false;
	unsigned int datawidth = 0;

	outputVariable = NULL;
	firstVariable = NULL;
	secondVariable = NULL;

	//verify output variable
	inputLineStream >> token;
	if (token.empty())
	{
		return translatedLine;
	}
	else if (token.length() >= 2)
	{
		if (token[0] == '/' && token[1] == '/')
		{
			return translatedLine;	//entire line is a comment
		}
	}
	for (unsigned int i = 0; i < outputs.size(); ++i)
	{
		if (outputs[i].getName() == token)
		{
			validVariable = true;
			outputVariable = &outputs[i];
			break;
		}
	}
	if (!validVariable)
	{
		for (unsigned int i = 0; i < wires.size(); ++i)
		{
			if (wires[i].getName() == token)
			{
				validVariable = true;
				outputVariable = &wires[i];
				break;
			}
		}
	}
	if (!validVariable)
	{
		//cout << "cannot assign this variable: " << token << "\t (must be output or wire)" << '\n';	//Error
		return "";
	}
	isSignedModule = outputVariable->getIsSigned();

	inputLineStream >> token;
	if (token != "=")
	{
		//cout << "invalid operation - output must be set equal to operation" << "\n";	//Error
		return "";
	}

	//verify first variable
	validVariable = false;
	inputLineStream >> token;

	if (token.length() != 0)
	{
		for (unsigned int i = 0; i < wires.size(); ++i)
		{
			if (wires[i].getName() == token)
			{
				validVariable = true;
				firstVariable = &wires[i];
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
				validVariable = true;
				firstVariable = &inputs[i];
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
				validVariable = true;
				firstVariable = &outputs[i];
				break;
			}
		}
	}
	if (!validVariable)
	{
		//cout << "Could not identity input/wire variable: " << token << " \n";	//Error
		return "";
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
		for (unsigned int i = 0; i < wires.size(); ++i)
		{
			if (wires[i].getName() == token2)
			{
				validVariable = true;
				secondVariable = &wires[i];
				break;
			}
		}

		if (!validVariable)
		{
			for (unsigned int i = 0; i < inputs.size(); ++i)
			{
				if (inputs[i].getName() == token2)
				{
					validVariable = true;
					secondVariable = &inputs[i];
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
					validVariable = true;
					secondVariable = &outputs[i];
					break;
				}
			}
		}
		if (!validVariable)
		{
			//cout << "Invalid variable: " << token2 << "\n";	//Error
			return "";
		}
	}

	datawidth = outputVariable->getWidth();

	if (isSignedModule)
	{
		if (firstVariable->getWidth() < datawidth)
		{	//check if we need to zero extend unsigned values
			if (!firstVariable->getIsSigned())
			{
				firstVarBitExtendZero = true;
			}
		}
		if (secondVariable != NULL)
		{
			if (secondVariable->getWidth() < datawidth)
			{
				if (!secondVariable->getIsSigned())
				{
					secondVarBitExtendZero = true;
				}
			}
		}
	}
		//identify operator
	if (token.empty())	//REG
	{
		translatedLine += "REG #(.DATAWIDTH(" + to_string(datawidth) + ")) reg" + to_string(num) + "( ";
		if (firstVarBitExtendZero && isSignedModule)
		{
			translatedLine += "$signed({1'b0," + firstVariable->getName() + "}), Clk, Rst, ";
		}
		else
		{
			translatedLine += firstVariable->getName() + ", Clk, Rst, ";
		}
		translatedLine += outputVariable->getName() + ");\n";
		//cout << translatedLine << '\n';
		return translatedLine;			//Valid output

	}
	if (!secondVariable == NULL)
	{
		if (token == "+")		//ADD
		{
			translatedLine += "ADD #(.DATAWIDTH(" + to_string(datawidth) + ")) add" + to_string(num) + "( ";
		}
		else if (token == "-")		//SUB
		{
			translatedLine += "SUB #(.DATAWIDTH(" + to_string(datawidth) + ")) sub" + to_string(num) + "( ";
		}
		else if (token == "*")		//MUL
		{
			translatedLine += "MUL #(.DATAWIDTH(" + to_string(datawidth) + ")) mul" + to_string(num) + "( ";
		}
		else if (token == "<<")		//SHL
		{
			translatedLine += "SHL #(.DATAWIDTH(" + to_string(datawidth) + ")) shl" + to_string(num) + "( ";
		}
		else if (token == ">>")		//SHR
		{
			translatedLine += "SHR #(.DATAWIDTH(" + to_string(datawidth) + ")) shr" + to_string(num) + "( ";
		}
		else if (token == "?")		//MUX
		{
			inputLineStream >> token;
			if (token == ":")
			{
				validVariable = false;
				inputLineStream >> token;
				thirdVariable = firstVariable;

				if (token.length() != 0)
				{
					for (unsigned int i = 0; i < wires.size(); ++i)
					{
						if (wires[i].getName() == token)
						{
							validVariable = true;
							firstVariable = &wires[i];
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
							validVariable = true;
							firstVariable = &inputs[i];
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
							validVariable = true;
							firstVariable = &outputs[i];
							break;
						}
					}
				}
				if (!validVariable)
				{
					//cout << "Invalid variable: " << token << "\n";		//ERROR
					translatedLine = "";
					return translatedLine;
				}
				else
				{
					translatedLine += "MUX2x1 #(.DATAWIDTH(" + to_string(datawidth) + ")) mux" + to_string(num) + "( ";
					hasThirdInput = true;
					if (isSignedModule)
					{
						if (firstVariable->getWidth() < datawidth)
						{	//check if we need to zero extend unsigned values
							if (!firstVariable->getIsSigned())
							{
								firstVarBitExtendZero = true;
							}
							else
							{
								firstVarBitExtendZero = false;
							}
						}
						else
						{
							firstVarBitExtendZero = false;
						}
					}
				}
			}
			else
			{
				//cout << "Invalid operator: " << token << "\n";		//ERROR
				return "";
			}

		}
		else		//must be comparator or invalid operator
		{
			translatedLine = "";
			if (secondVariable != NULL)
			{	//get datawidth of module
				if (secondVariable->getWidth() > firstVariable->getWidth())
				{
					datawidth = secondVariable->getWidth();
				}
				else
				{
					datawidth = firstVariable->getWidth();
				}
				//check if module is signed
				if (secondVariable->getIsSigned() || firstVariable->getIsSigned())
				{
					isSignedModule = true;
					translatedLine += "COMP #(.DATAWIDTH(" + to_string(datawidth) + ")) comp" + to_string(num) + "( ";
					if (!firstVariable->getIsSigned())
					{
						translatedLine += "$signed({1'b0," + firstVariable->getName() + "}), ";
					}
					else
					{
						translatedLine += firstVariable->getName() + ", ";
					}
					if (!secondVariable->getIsSigned())
					{
						translatedLine += "$signed({1'b0," + secondVariable->getName() + "}), ";
					}
					else
					{
						translatedLine += secondVariable->getName() + ", ";
					}
				}
				else
				{
					isSignedModule = false;
					translatedLine += "COMP #(.DATAWIDTH(" + to_string(datawidth) + ")) comp" + to_string(num) + "( "
						+ firstVariable->getName() + ", " + secondVariable->getName() + ", ";
				}

				//determine output to wire
				if (token == ">")
				{
					translatedLine += outputVariable->getName() + ", 0, 0);\n";
				}
				else if (token == "==")
				{
					translatedLine += "0, 0, " + outputVariable->getName() + ");\n";
				}
				else if (token == "<")
				{
					translatedLine += "0, " + outputVariable->getName() + ", 0);\n";
				}
				else
				{
					//cout << "Invalid operator: " << token << "\n";	//ERROR
					return "";
				}
			}
			else
			{
				//cout << "Missing operator or variable: " << token << '\n';	//ERROR
				translatedLine = "";
				return translatedLine;
			}
			//cout << translatedLine << "\n";
			return translatedLine;	//valid output
		}
	}
	else
	{
		//cout << "Incomplete operation \n";		//ERROR
		return "";
	}

	//all require this ********** (EXCEPT comparator)
	if (firstVarBitExtendZero && isSignedModule)
	{
		translatedLine += "$signed({1'b0," + firstVariable->getName() + "}), ";
	}
	else
	{
		translatedLine += firstVariable->getName() + ", ";
	}
	if (secondVarBitExtendZero && isSignedModule)
	{
		translatedLine += "$signed({1'b0," + secondVariable->getName() + "}), ";
	}
	else
	{
		translatedLine += secondVariable->getName() + ", ";
	}
	if (hasThirdInput)
	{
		translatedLine += thirdVariable->getName() + ", ";
	}
	translatedLine += outputVariable->getName() + ");\n";
	//cout << translatedLine << "\n";
	//*****************************


	return translatedLine + "\n";
}