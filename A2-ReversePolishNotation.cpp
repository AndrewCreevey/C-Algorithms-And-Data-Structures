/* Andrew Creevey - 12236284 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>

using namespace std;

struct Node {
	int data;
	Node *next;
};

class Stack {
private:
	Node *listpointer;
public:
	Stack();
	~Stack();
	void Push(int newthing);
	void Pop();
	int Top();
	bool isEmpty();
};

Stack::Stack() {
	listpointer = NULL;
}

Stack::~Stack() {
}

void Stack::Push(int newthing) {
	//newthing at the top of the stack
	Node *temp;
	temp = new Node;
	temp -> data = newthing;
	temp -> next = listpointer;
	listpointer = temp;
}

void Stack::Pop() {
	Node *p;
	p = listpointer;
	if(listpointer != NULL) {
		listpointer = listpointer -> next;
		delete p;
	}
}

int Stack::Top() {
	return listpointer -> data;
}

bool Stack::isEmpty() {
	if(listpointer == NULL) {
		return true;
	}
	return false;
}

	

int main( int argc, char** argv ){//get arguments from command line, i.e., yourexec filename
	Stack S;
	string expression;
	int result = 0, op1 = 0,op2 = 0,number = 0;
	char oper;
	
	ifstream input_file;
	input_file.open("A2-RPN.txt");
	if(!input_file.good()){
	  cout<< "cannot read file " << argv[1] << endl; 
	  exit(0);
	}
	while(!input_file.eof()){
		getline(input_file,expression);
		if(isdigit(expression[0])){
		  stringstream line(expression);
		  line >> number;
			cout << "Number: " << number << endl;
			S.Push(number);
		}
		if(expression[0]=='+' || expression[0]=='-'|| expression[0]=='/'||expression[0]=='*') {
			stringstream line(expression);
			line >> oper;
			cout << "Operator: " << oper << endl;
			if(S.isEmpty() == false) {
				op2 = S.Top();				  //op2 = TOP
				S.Pop(); //POP
			}
			if(S.isEmpty() == false) {
				op1 = S.Top(); //op1 = TOP
				S.Pop(); //POP
			}
			else {
				cout << "Too many operators" << endl;
				exit(0);
			}
			
			if(oper=='+') { //applying operator to op1 and op2
				result=op1 + op2;
			}
			if(oper=='*') {
				result=op1 * op2;
			}
			if(oper == '-') {
				result = op1 - op2;
			}
			if(oper == '/') {
				result = op1 / op2;
			}
			
			S.Push(result); //Push Result
		}
	}
	result = S.Top();;	//finalanswer = TOP
	S.Pop(); //the last element of the stack should be the final answer...
	if(S.isEmpty() == false) {
		cout << "Too many numbers" << endl;
		exit(0);
	}
	else {
		cout << "Result: " << result << '\n' << endl;
	}
}
