/* -- Name: Andrew Creevey -- ID: 12236284 -- */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>

using namespace std;

struct Node {
	int data;
	Node *next;
};

class Queue {
private:
	Node *front, *rear;
	int counter;
public:
	Queue ();
	~Queue ();
	void Join (int newthing);
	void Leave ();
	int Front ();
	bool isEmpty ();
	void Print ();
	int Length ();
};

//=================================================================================//

#define TIMEDELAY 3
#define N 128
int OutQueues_current[N];
int Congestion_Size[N];

Queue InputQueues[N];
Queue OutputQueues[N];

void init_simulation ();
int sum_elements_array (int array[]);

int number_of_ports = 0;

//=================================================================================//
//================================== Main =========================================//

int main (int argc, char** argv ){
	//read the file, print the input ports contents
	int portnumber = 0;
	int destination = 0;
	string expression;
	string geninput;
	ifstream input_file;
	input_file.open ("A3-Sim3.txt");
	if (input_file.is_open () == false) {
		cout << "Could not read file: " << endl << argv[1] << endl; 
		exit (0);
	}
	string token;
	while (!input_file.eof ()) {
		getline (input_file, expression);
		stringstream line (expression);
		if( input_file.eof ()) break;
		if (expression[0] == '#') continue; //jump line, this is a line of comments
		if (expression[0] == 'P') {
			getline(line, token,' ');
			getline(line, token,' ');
			number_of_ports = atoi (token.c_str ());
			continue; //got the number of ports
		}
		portnumber++;
		while (getline (line, token,' ')) {
			destination = atoi (token.c_str ());
			if (destination < 0 || destination > number_of_ports || number_of_ports < portnumber) {
				cout << "ERROR in the format of the text file" << endl; 
				exit (0);
			}
			InputQueues[portnumber-1].Join(destination);
		}
	}
	init_simulation ();
	unsigned long int clock = 0;
	unsigned long int currentsum = 9999999;
	portnumber = 0;
	
	while (currentsum > 0) {
		if (InputQueues[portnumber].isEmpty() == false) {
			OutputQueues[InputQueues[portnumber].Front()-1].Join(InputQueues[portnumber].Front());
			InputQueues[portnumber].Leave();
		}
		portnumber++;
		if (portnumber > (number_of_ports - 1)) portnumber = 0;
		clock++;
		if (clock % (TIMEDELAY * number_of_ports) == 0 && clock != 0) { //DO NOT MODIFY THIS LINE!
			for (int a = 0; a < number_of_ports; a++) {
				OutputQueues[a].Leave();
			}
		}
		int temp = 0;
		for (int a = 0; a < number_of_ports; a++) {
			temp = temp + OutputQueues[a].Length();
			OutQueues_current[a] = OutputQueues[a].Length();
		}
		currentsum = temp;
		if (currentsum > sum_elements_array (Congestion_Size)) {
			for (int a = 0; a < number_of_ports; a++) {
				Congestion_Size[a] = OutQueues_current[a];
			}
		}
	}
	for (int a = 0; a < number_of_ports; a++) {
		cout << "Output port " << a+1 << ": " << Congestion_Size[a] << " packets" << endl; 
	}
}

//=================================================================================//
//Functions

void init_simulation () {
	for (int a = 0; a < N; a++) {
		OutQueues_current[a] = 0;
		Congestion_Size[a] = 0;
	}
}

int sum_elements_array (int array[]) {
	int sum = 0;
	for (int a = 0; a < N; a++) {
		sum = sum + array[a];
	}
	return sum;
}

Queue::Queue () {
	// constructor
	front = NULL;  
	rear = NULL;
	counter = 0;
}

Queue::~Queue () {
	// destructor
}

void Queue::Join (int newthing) {
	// place the new thing at the rear of the queue
	Node *temp;
	temp = new Node;
	temp -> data = newthing;
	temp -> next = NULL;
	if (rear != NULL) { 
		rear -> next = temp; 
	}
	rear = temp;
	if (front == NULL) { 
	  front = temp; 
	}
	counter++;
}


void Queue::Leave () {
	// remove the front item from the queue
	Node * temp;
	if (front == NULL) { 
		return; 
	}
	temp = front;
	front = front -> next;
	if (front == NULL) { 
	  rear = NULL;
	}
	delete temp;
	counter--;
}

int Queue::Front () {
// return the value of the front item
	if (front != NULL) {
		return front -> data;
	} 
	return 0;
}

bool Queue::isEmpty () {
// return true if the queue is empty
	if (front == NULL) { 
		return true; 
	}
	return false;
}

void Queue::Print () {
	if (front == NULL) return;
	Node *temp = front;
	printf ("Listing the queue: ");
	while (temp != NULL) {
		printf ("%d ", temp -> data);
		temp = temp -> next;
	}
	printf ("\n");
}

int Queue::Length () {
	return counter;
}
