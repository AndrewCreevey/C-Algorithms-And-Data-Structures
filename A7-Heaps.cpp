/* ---------------------------------- */
/* ------- Name ----------- ID ------ */
/* -- Andrew Creevey --- 12236284 --- */
/* ---------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector <int> vector_random;
vector <int> vector_reversed;
vector <int> vector_sorted;

//Heap class
class Heap {
public:
	Heap (): last (-1), comparisons (0) { };
	~Heap () { };
	void InsertHeap (int item);
	int Delete ();
	void PrintHeap () const;
	void Swap (int &item1, int &item2);
	int GetComparisons () { 
		return comparisons; 
	}
	void ResetComparisons () { 
		comparisons = 0; 
	}
private:
	vector <int> data;
	int last;
	int comparisons;
};

/* ------------------------------------------------------------------------------------------------------------ */

void Heap::InsertHeap (int item) {
	data.push_back (item); 																		// add to the end
	last++;

	if (last == 0) {																				// only one item in Heap
		return;
	}
	int child_index = last;
	int par_index = 0;
	bool swapping = true;

	while (swapping) { 																			// fix the heap
		swapping = false;
		if ((child_index % 2) == 0) {															// if item added is right side
			par_index = child_index / 2 - 1; 												// find the parent index
		} else 	{																						// if item added is left side
			par_index = child_index / 2; 														// find the parent index
		}
		if (par_index >= 0) {
			comparisons++; 																		// comparison here
			if (data[child_index] > data[par_index]) {
				swap(data[child_index], data[par_index]);
				swapping = true;
				child_index = par_index;
			}
		}
	}
}

/* ------------------------------------------------------------------------------------------------------------ */

int Heap::Delete () {
	if (last < 0) {
		return 0;
	}
	unsigned int deletednum = data[0]; 														//the root
	data[0] = data[last];
	data[last] = 0; 																				//delete last item
	last = last - 1; 																				// one less element in the heap
	int parindex = 0; 																			//root at the moment
	int leftindex = parindex * 2 + 1; 														//left child
	int rightindex = parindex * 2 + 2; 														//right child
	int swapping = true; 																		// need to rearrange to make it a heap again
	if (data[leftindex] > 0) comparisons++;
	if (data[rightindex] > 0) comparisons++;
	
	while ((data[parindex] < data[leftindex] || data[parindex] < data[rightindex]) && swapping) {
		swapping = false;
		
		if (data[rightindex] < data[leftindex]) {											//follow left
			swap (data[leftindex], data[parindex]);
			parindex = leftindex;
			swapping = true;
		} else { 																					//else follow right
			swap (data[rightindex], data[parindex]);
			swapping = true;
			parindex = rightindex;
		}
		leftindex = parindex * 2 + 1; 														// left side of parent index
		rightindex = parindex * 2 + 2; 														// right side of parent index
		if (leftindex > last) {
			break;
		} else {
			if (rightindex > last) {
				comparisons++; 																	// comparison here
				if (data[parindex] < data[leftindex]) {
					swap(data[parindex], data[leftindex]);
				}
				break;
			}
		}
		if (data[leftindex] > 0) comparisons++;
		if (data[rightindex] > 0) comparisons++;
	}
	return deletednum;
}

/* ------------------------------------------------------------------------------------------------------------ */

void Heap::PrintHeap () const {
	for (int i = 0; i <= last; i++) {
		cout << data.at(i) << ' ';
	}
	cout << endl;
}

/* ------------------------------------------------------------------------------------------------------------ */

void heapsort (vector<int> &sortingvector, int number_of_elements, char* filename){
	Heap myHeap;
	
	for (unsigned int i = 0; i < sortingvector.size (); i++) {
		myHeap.InsertHeap (sortingvector[i]);
	}
	cout << "Heap before sorting: " << filename << endl;
	myHeap.PrintHeap ();
	
	int insertComparisons = myHeap.GetComparisons();
	myHeap.ResetComparisons ();

	for (unsigned int i = 0; i < sortingvector.size (); i++) {
		int temp = myHeap.Delete ();
		if (temp > 0) sortingvector[i] = temp;
	}
	int deleteComparisons = myHeap.GetComparisons ();
	
	cout << "InsertHeap: " << insertComparisons << " comparisons" << endl;
	cout << "DeleteRoot: " << deleteComparisons << " comparisons" << endl;
	cout << "Vector after sorting:" << endl;
	
	for (unsigned int i = sortingvector.size() - 1; i > 0; i--) {
		cout << sortingvector[i] << ' ';
	}
	cout << sortingvector[0] << ' ';
	cout << endl;
}

/* ------------------------------------------------------------------------------------------------------------ */

main (int argc, char** argv) {																//get filename from arguments
	char expression[100];
	int number;
	ifstream input_file_random;
	ifstream input_file_reversed;
	ifstream input_file_sorted;
	if (argc == 4) {
	  input_file_random.open (argv[1]);
	  input_file_reversed.open (argv[2]);
	  input_file_sorted.open (argv[3]);
	} else {
		printf("The program needs 3 filenames and in the order: random, reversed and sorted.\n");
		exit(0);
	}
	int number_of_elements_random = 0;
	while (input_file_random >> number){
		sscanf (expression, "%d", &number);	
		vector_random.push_back (number);
		number_of_elements_random++;
	}
	
	int number_of_elements_reversed = 0;
	while (input_file_reversed >> number){
		sscanf (expression, "%d", &number);
		vector_reversed.push_back (number);
		number_of_elements_reversed++;
	}

	int number_of_elements_sorted = 0;
	while (input_file_sorted >> number){
		sscanf (expression, "%d", &number);
		vector_sorted.push_back (number);
		number_of_elements_sorted++;
	}
	
	//Print out info
	heapsort(vector_random, number_of_elements_random, argv[1]);
	cout << endl;
	heapsort(vector_reversed, number_of_elements_reversed, argv[2]);
	cout << endl;
	heapsort(vector_sorted, number_of_elements_sorted, argv[3]);
}

/* ------------------------------------------------------------------------------------------------------------ */
