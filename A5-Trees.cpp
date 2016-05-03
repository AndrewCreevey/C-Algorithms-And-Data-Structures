// -- Andrew Creevey -- 12236284 -- //

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>

using namespace std;

class Tree {
private:
	char data;
	Tree *leftptr, *rightptr;
public:
	Tree (char newthing, Tree* L, Tree* R);  //constructor with paramters
	~Tree () { }
	char RootData () { return data; }  //inline functions
	Tree* Left () { return leftptr; }
	Tree* Right () { return rightptr; }
};

Tree::Tree (char newthing, Tree* L, Tree* R) {
	data = newthing;
	leftptr = L;
	rightptr = R;
}

//--------------------------------------------------------------------------//
//Display functions

void inOrder (Tree *T) {
	if (T == NULL) {
		return;
	}
	if (T -> Left () != NULL) printf ("("); //added for parenthesis 
	inOrder (T -> Left ());
	printf ("%c", T -> RootData ());
	inOrder (T -> Right ());
	if (T -> Right () != NULL) printf (")"); //added for parenthesis 
}

void PostOrder (Tree *T) {
	if (T == NULL) {
		
		return; 
	}
	PostOrder (T -> Left ());
	PostOrder (T -> Right ());
	printf ("%c ", T -> RootData ());
}

//--------------------------------------------------------------------------//
//Node declaration and Stack functions

struct Node {
	Tree* data;
	Node *next;
};

class Stack {
private: //the data differs from the array
	Node *listpointer;
public: //the functions (methods) are identical
	Stack ();
	~Stack ();
	void Push (Tree* newthing);
	void Pop ();
	Tree* Top ();
	bool isEmpty ();
};

Stack::Stack () { //constructor
	listpointer = NULL;
}

Stack::~Stack () { //destructor
}

void Stack::Push (Tree* newthing) {
//place the new thing on top of the stack
Node *temp;
	temp = new Node; //same as add node to front of linked-list
	temp -> data = newthing;
	temp -> next = listpointer; //NOTE: no overflow problem
	listpointer = temp;
}
void Stack::Pop () { 
//remove top item from the stack
Node *p;
	p = listpointer;
	if (listpointer != NULL) { //check to avoid underflow
		listpointer = listpointer -> next;
		delete p; //always delete temp variable
  }
}

Tree* Stack::Top () {
//return the value of the top item
	return listpointer -> data;
}

bool Stack::isEmpty () {
//returns true if the stack is empty
	if (listpointer == NULL) {
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------//
//Variables needed

Stack S ;

Tree *T1, *T2, *T;  // always use pointers to trees

//--------------------------------------------------------------------------//
//Main function

int main (int argc, char **argv) {
	if (argc != 2) {
		cout << "Arithmetic tree requires one argument.\n" << endl;
		exit (-1);
	}
	char expression [100];
	char digit;
	char operation;
	ifstream data;
	data.open (argv [1]);
	
	while (data >> expression) {
		if	(isdigit (expression [0])) { //look at the first character
			sscanf (expression, "%c", &digit);
			S.Push (new Tree (expression [0], NULL, NULL));
		} else { //operator
			sscanf (expression, "%c", &operation);
			T1 = S.Top (); S.Pop ();
			T2 = S.Top (); S.Pop ();
			S.Push (new Tree (expression [0], T2, T1));
		}                             
	}
	
	T = S.Top ();
	
	//Print results
	cout << "In-fix:" << endl;
	inOrder (T);
	cout << endl << "Post-fix:" << endl;
	PostOrder (T);
	cout << endl;
}

//--------------------------------------------------------------------------//
