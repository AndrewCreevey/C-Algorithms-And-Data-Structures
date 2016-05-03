/* Name: Andrew Creevey -- ID: 12236284 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Node {
	int row;
	int col;
	int value;
	Node *next;
};

int MaxRow, MaxCol, MatrixSize;

Node *A, *B, *Result;

void read_matrix (Node *&a, char *filename);
void AddNode (Node *&listpointer, int x, int y, int z);
void PrintLL (Node *listpointer);
void PrintMatrix (Node *listpointer, int size);
int Search (Node * listpointer, int x, int y);
void AddMatrix (Node *listpointer1, Node *listpointer2);

//---------------------------------------------------------------------------------//

int main (int argc, char** argv) {
	A = NULL, B = NULL, Result = NULL;
	
	//Reads and Prints Matrix A
	read_matrix (A, (char*)"A1-Matrix1.txt");		//comment this line while testing on server/submitting
	printf ("Matrix 1: ");
	PrintLL (A);
	PrintMatrix (A, MatrixSize);

	//Reads and Prints Matrix B
	read_matrix (B, (char*)"A1-Matrix2.txt");		//comment this line while testing on server/submitting
	printf ("Matrix 2: ");
	PrintLL (B);
	PrintMatrix (B, MatrixSize);
	
	//Adds Matrix A + B and Prints Result Matrix
	AddMatrix (A, B);
	printf ("Matrix Result: ");
	PrintLL (Result);
	PrintMatrix (Result, MatrixSize);
}

//---------------------------------------------------------------------------------//

void AddMatrix (Node *listpointer1, Node *listpointer2) {
	int i, j, answer;
	Node *A1, *B1;
	A1 = listpointer1;
	B1 = listpointer2;
	
	for (i = 0; i < MaxRow; i++) {
		for (j = 0; j < MaxCol; j++) {
			answer = Search (A1, i, j) + Search (B1, i, j);
			if (answer != 0) {
				AddNode (Result, i, j, answer);
			}
		}
	}
}

//---------------------------------------------------------------------------------//

int Search (Node * listpointer, int x, int y) {
	// search for the node with row equal to x and col equal to y
	Node *current;
	current = listpointer;
	while (true) {
		if (current == NULL) { break; }
		if (current -> row == x && current -> col == y) {
			return (current -> value);
		}
		current = current->next;
	}
	//If point does not exist, return 0
	return (0);
}

//---------------------------------------------------------------------------------//

void PrintMatrix (Node *listpointer, int size) {
	int trackrow = 0; int trackcol = 0;
	Node *current;
	current = listpointer;
	while (true) {
		if (current == NULL) { break; }
		if ((trackrow == current -> row) && (trackcol == current -> col)) {
			printf ("%d ", current -> value);
			current = current -> next;
		}
		else {
			printf ("0 ");
		}
		trackcol++;
		if (trackcol > (size - 1)) {
			printf ("\n");
			trackcol = 0;
			trackrow++;
		}
	}
	while (trackrow < size) {
		printf ("0 ");
		trackcol++;
		if (trackcol > (size - 1)) {
			printf ("\n");
			trackcol = 0;
			trackrow++;
		}
	}
}
	
//---------------------------------------------------------------------------------//

void PrintLL (Node *listpointer) {
	Node *current;
	current = listpointer;
	if (current == NULL) {
		printf ("\n");
		return;
	}
	while (current != NULL) {
		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");
}

//---------------------------------------------------------------------------------//

void AddNode (Node *&listpointer, int x, int y, int z) {
	Node *current;
	current = listpointer;
	if (current != NULL) {
		while (current -> next != NULL){
			current = current -> next;
		}
	}
	Node *temp;
	temp = new Node;
	temp -> row = x;
	temp -> col = y;
	temp -> value = z;
	temp -> next = NULL;
	if (current != NULL) current -> next = temp;
	else listpointer = temp;
}

//---------------------------------------------------------------------------------//

void read_matrix (Node* &a, char *file_name) {
	int rw = 0, cl = 0, val = 0;
	ifstream input;
	input.open (file_name);
	if (!input.good ()) {
		cout << "Cannot open file" << rw << " " << cl << endl;
		exit (0);
	}
	string line;
	if (input.good ()) {
		getline (input, line);
		stringstream sline (line);
		sline >> rw >> cl;
	}
	for (int i = 0; i < rw; i++) {
		if (input.good ()) {
			getline (input, line);
			stringstream sline (line);
			for (int j = 0; j < cl; j++) {
				sline >> val;
				if (val == 0) continue;
				AddNode (a, i, j, val);
			}
		}
	}
	MaxRow = rw;
	MaxCol = cl;
	MatrixSize = (rw + cl) / 2;
	input.close ();
}

//---------------------------------------------------------------------------------//
