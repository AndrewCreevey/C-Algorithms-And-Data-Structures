/* -- Andrew Creevey -- 12236284 -- */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <stack>

using namespace std;

int *d; // distances
char *s; // states

struct Node {
	char key;
	int distance;
	Node *next;
};

/* declare a new Graph */
struct GraphNode {
	char key;
	Node *listpointer;
};

//------------------------------------------------------------------------------//
/* Implement the Graph class  */
class Graph {
private:
	vector <GraphNode> adjlist;
public:
   Graph (){};
	~Graph (){};
	void AddNewGraphNode (char newgraphnode);
	void AddNewEdgeBetweenGraphNodes (char A, char B, int distance);
	void PrintAllGraphNodesWithCosts ();
	void Dijkstra();
	int GetVertexLocation(char key);
	void PrintDijkstra();
	void PrintLLnodes (Node*& listpointer);
	bool AllVertexIsPerm();
};

Graph MyGraph;

void AddNode (Node*& listpointer, char newkey, int newdistance) {
	Node *temp;
	temp = new Node;
	temp -> key = newkey;
	temp -> distance = newdistance;
	temp -> next = listpointer;
	listpointer = temp;
}

void Graph::PrintLLnodes (Node*& listpointer){
	Node *temp;
	temp = listpointer;
	while(temp != NULL) {
		printf("to node %c dist: %d \n", temp -> key, temp -> distance);
		temp = temp ->	next;
	}
}

void Graph::AddNewGraphNode (char newgraphnode) {
	GraphNode temp;
	temp.key = newgraphnode;
	temp.listpointer = NULL; //important
	adjlist.push_back (temp);
}

void Graph::AddNewEdgeBetweenGraphNodes (char A, char B, int distance) {  
	//find which node A is
	int a;
	for (a = 0; adjlist.size (); a++){
		if (A == adjlist [a].key) break;
	}
	AddNode (adjlist [a].listpointer, B, distance); 
}

void Graph::PrintAllGraphNodesWithCosts () {
	for (unsigned a = 0; a < adjlist.size (); a++){
		printf ("From Node %c: \n", adjlist[a].key);
		PrintLLnodes (adjlist[a].listpointer);
	}
}

int Graph::GetVertexLocation(char key) {
	for (unsigned i = 0; i < adjlist.size(); ++i) {
		if (adjlist[i].key == key)
			return i;
	}
}

bool Graph::AllVertexIsPerm() {
	for (unsigned i = 0; i < adjlist.size(); ++i) {
		Node *current = adjlist[i].listpointer;
		while (current != NULL) {
			if (s[GetVertexLocation(current->key)] == 't')
				return false;
			current = current->next;
		}
	}
	return true;
}

//------------------------------------------------------------------------------//
// Dijkstra functions

void Graph::PrintDijkstra() {
	for (unsigned i = 1; i < adjlist.size(); i++) {
		printf("From A to %c:%d\n", adjlist[i].key, d[i]);
	}
}

void Graph::Dijkstra() {
	d = new int[adjlist.size()];
	s = new char[adjlist.size()];
	int vecVertex = 0;

	d[vecVertex] = 0;
	s[vecVertex] = 'p';

	// initialize distances and states
	for (unsigned i = 1; i < adjlist.size(); ++i) {
		d[i] = INT_MAX;
		s[i] = 't';
	}

	stack<int> prevLocations; // store previous location in the 'vecVertex' vector

	while (!AllVertexIsPerm()) {
		Node *current = adjlist[vecVertex].listpointer;
		int numOfTempVertices = 0;
		// update costs of neighbours
		while (current != NULL) {
			int v = GetVertexLocation(current->key);
			// get adjacent node's location in the vector
			d[v] = min(d[v], d[vecVertex] + current->distance);
			if (s[v] == 't') {
				numOfTempVertices++;
			}
			current = current->next;
		}

		int minimum = INT_MAX;
		int temp = 0;
		current = adjlist[vecVertex].listpointer;
		while (current != NULL){
			if ((d[GetVertexLocation (current->key)] < minimum) && 
					(s[GetVertexLocation(current->key)] == 't')){
				minimum = d[GetVertexLocation (current->key)];
				temp = GetVertexLocation (current->key);
			}
			current = current->next;
		}
		s[vecVertex] = 'p';  // set state to permanent
		if(AllVertexIsPerm()) {
			break;
		}
		if (numOfTempVertices == 0) {
			vecVertex = prevLocations.top();
			prevLocations.pop();
		}
		if (numOfTempVertices == 1) {
			vecVertex = temp; // get location of next vertex
		}
		if (numOfTempVertices >= 2) {
			// if current vertex has more than one adjacent node with temp state
			prevLocations.push(vecVertex); // store previous vertex location
			vecVertex = temp;
		}
	}
}

//------------------------------------------------------------------------------//

int main (int argc, char** argv ) {
	//read an input text file
	string expression;
	ifstream input_file;
	//if (argc != 2) { cout << "Type a file name. " << endl << argv [1] << endl;	exit (0); }
	//input_file.open (argv [1]);
	input_file.open ("A6-Graph-1.txt");
	if (input_file.is_open () == false) { 
		cout << "Could not read file: " << endl << argv [1] << endl; 
		exit (0); 
	}
	string token;
	while (!input_file.eof ()) {
		getline (input_file, expression);
		stringstream line (expression);
		if (input_file.eof ()) break;
		if (expression [0] == '#') continue; //jump line, this is a line of comments
		char node_name;
		if (expression [0] == 'N' && expression [1] == 'o') {//read a Node name, single character
			getline (line, token, ' ');
			getline (line, token, ' ');
			node_name = (token.c_str ()) [0];
			/* Insert nodes into the graph */
			MyGraph.AddNewGraphNode(node_name);
		} else {
			char nodefrom;
			getline (line, token, ' ');
			nodefrom = (token.c_str ()) [0];
			char nodeto;
			getline (line, token, ' ');
			nodeto = (token.c_str ()) [0];
			int cost;
			getline (line, token, ' ');
			cost = atoi (token.c_str ());
			/* Insert these edges into the graph */
			MyGraph.AddNewEdgeBetweenGraphNodes(nodefrom, nodeto, cost);
		}
	}
	//After loading the graph from the text file in the while loop above, run your implementation of Dijkstra here
	//Dijkstra can be implemented either as a function or as a method of the class Graph
	
	//call Dijkstra
	MyGraph.Dijkstra();
	
	//Print answer in the required format
	MyGraph.PrintDijkstra();	
}

//------------------------------------------------------------------------------//
