#include "Graph.h"
  
using namespace std; 

// constructors
Graph::Graph() {} // default constructor

Graph::Graph(Nodes newNodes, Edges newEdges, int newWeight) {
	this->nodes.push_back(newNodes);
	this->edges.push_back(newEdges);
	this->weight = newWeight;
}

// setters
void Graph::setNodes(Nodes newNodes) {
	this->nodes.push_back(newNodes);
}

void Graph::setEdges(Edges newEdges) {
	this->edges.push_back(newEdges);
}

void Graph::setWeight(int newWeight) {
	this->weight = newWeight;
}

// getters
vector<Nodes> Graph::getNodes() {
	return this->nodes;
}

vector<Edges> Graph::getEdges() {
	return this->edges;
}

int Graph::getWeight() {
	return this->weight;
}

unsigned int Graph::getNumNodes() {
	return nodes.size();
}

//Methods

void Graph::addNode(Nodes newNode, string edgeCondition, int ifStatementLevel) {
	vector<string> newNodeVars;
	int asapTime = 0;

	newNodeVars = newNode.getVariablesInvolved();
	if (newNodeVars.size() == 0) {
		cout << "Error (Graph.addNode): newNode has 0 variables" << endl;
		return;
	}
	newNode.setIfStatementLevel(ifStatementLevel);
	nodes.push_back(newNode);
	cout << newNode.getOperation() << endl;
	if (nodes.size() > 1) {
		for (int j = 0; j < newNodeVars.size(); ++j) {
			for (int i = nodes.size() - 2; i >= 0; i--) {
				if (nodes.at(i).getOutputVariable() == newNodeVars.at(j) || nodes.at(i).getIfStatementLevel() < ifStatementLevel) {	//Compare output variable with graph nodes to find dependency and create and Edge
					Edges newEdge;
					newEdge.setNextNode(&nodes.at(nodes.size() - 1));
					newEdge.setPrevNode(&nodes.at(i));
					if (nodes.at(i).getIfStatementLevel() < ifStatementLevel) {
						newEdge.setCondtionalOperation(edgeCondition);	//Sets edge condition if exists
					}
					nodes.at(i).addEdge(newEdge); //adds edge to node pointing to newNode				//FIXME AVOID DUPLICATE EDGES (override edge ==)
					//calculate asapTime
					if (nodes.at(i).getAsapTime() >= asapTime) {
						asapTime = nodes.at(i).getAsapTime() + 1;	//AsapTime is 1 higher than preceding Node
					}
					break;
				}
			}
		}
	}
	nodes.at(nodes.size() - 1).setAsapTime(asapTime);
	
}

//void Graph::calculateWeights(Operations &op)
//{
//	int tempWeight = -1;
//
//	// Calculate weight by determining type of operation
//
//	this->weight = tempWeight;
//}

//void Graph::setupNodesEdges(ReadInputFile &rif)
//{	
//	int tempStateNum = 0;
//	int tempNumCycles = 0;
//	string tempOperation = "\0";
//	for (Operations op : rif.operationList) {
//		this->nodes.
//	}
//}
