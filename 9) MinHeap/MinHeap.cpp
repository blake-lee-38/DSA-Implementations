//
// 
// This file implements a Min Heap data structure using
// an array-based implementation strategy - In testing,
// the basic add/remove functions are tested, as well as
// the application of a Min Heap to sort an array of Nodes
// 
// 
#include <iostream>
using namespace std;

// 
// Basic Node class for implementation: Could be changed
// to add more satellite data, etc
//
class Node {
private:
	int key;
public:
	void Set_key(int x);
	int Get_key();
	Node();
};
void Node::Set_key(int x) {
	key = x;
}
int Node::Get_key() {
	return key;
}
Node::Node() {
	key = -1;
}

// 
// MinHeap Class: Implements MinHeap data structure with basic add/remove
// methods and private helper methods [SwapUp and SwapDown] to ensure
// MinHeap properties are retained - Includes a traverse function for 
// testing
//
class MinHeap {
private:
	Node* root;
	int ArraySize;
	int HeapSize;

	int SwapUp(int idx);
	int SwapDown(int idx);

public:

	// 
	// Prints keys using breadth-first traverse [each element of array in order]
	//
	void BSTraverse();

	// 
	// Adds a Node to the heap and performs needed functions to retain MinHeap
	// properties
	//  
	void Add(Node* p);

	// 
	// Removes the root of the Min Heap and performs needed function to retain
	// MinHeap properties
	//
	void Remove();

	// 
	// Returns the Root of the Min Heap [Smallest element in collection]
	//
	Node* Root();

	//
	// Resizes root array to allow more elements to be added
	//
	void Resize(int n);

	// 
	// Constructor: Initializes root array, HeapSize to 0, ArraySize to 10
	//
	MinHeap();
	
};

// Used for testing: Uses BST to print all non-empty cells
void MinHeap::BSTraverse() {

	for (int i = 0; i < ArraySize; i++) {
		if (root[i].Get_key() != -1) {
			cout << root[i].Get_key();
		}
	}

}

// Helper method for Add function: Swaps Node with parent if Node's
// key is smaller, then returns new index for further checking
// Returns -1 if no swap is needed
int MinHeap::SwapUp(int idx) {
	if (idx == 0) return -1;

	if (root[idx].Get_key() < root[(idx - 1) / 2].Get_key()) {
		Node temp = root[idx];
		root[idx] = root[(idx - 1) / 2];
		root[(idx - 1) / 2] = temp;
		return ((idx - 1) / 2);
	}
	else {
		return -1; //No Swap Needed
	}
}

// Add method: Adds Node to the end of the MinHeap array [resizes if needed]
// then uses SwapUp method to retain MinHeap property
void MinHeap::Add(Node* p) {

	if (ArraySize == HeapSize) {
		Resize(ArraySize * 2);
	}
	
	root[HeapSize] = *p;

	int checkSwap = HeapSize;
	while (checkSwap != -1) {
		checkSwap = SwapUp(checkSwap);
	}

	HeapSize++;
}

// Helper method for Remove function: Swaps Node with smallest child if either has a key lower
// than the parent -> First checks if left and right child indices are in array to prevent
// out of bounds access
int MinHeap::SwapDown(int idx) {
	int leftChild = ((idx + 1) * 2) - 1;

	if (leftChild >= ArraySize) 
		return -1;
	else if (leftChild + 1 >= ArraySize) {
		if (root[leftChild].Get_key() != -1 && root[leftChild].Get_key() < root[idx].Get_key()) {
			Node temp = root[leftChild];
			root[leftChild] = root[idx];
			root[idx] = temp;
			return -1;
		}
		return -1;
	}

	if ((root[leftChild].Get_key() < root[leftChild + 1].Get_key()) && root[leftChild].Get_key() < root[idx].Get_key()) {
		Node temp = root[leftChild];
		root[leftChild] = root[idx];
		root[idx] = temp;
		return leftChild;
	}
	else if (root[leftChild + 1].Get_key() != -1 && root[leftChild + 1].Get_key() < root[idx].Get_key()) {
		Node temp = root[leftChild + 1];
		root[leftChild + 1] = root[idx];
		root[idx] = temp;
		return leftChild + 1;
	}

	return -1;
}

// Remove Function: Removes the root of the MinHeap, then replaces with the last Node in the array,
// and uses SwapDown function to restore property
void MinHeap::Remove() {

	HeapSize--;
	root[0].Set_key(root[HeapSize].Get_key());
	root[HeapSize].Set_key(-1);

	int checkSwap = 0;
	while (checkSwap != -1) {
		checkSwap = SwapDown(checkSwap);
	}
}


//Returns the root of the Min Heap [Smallest key]
Node* MinHeap::Root() {
	return root;
}

//Resizes array of Nodes that represents MinHeap by copying all nodes to a different array,
//then resizing root and copying data back over
void MinHeap::Resize(int n) {

	Node* temp = new Node[ArraySize];
	for (int i = 0; i < ArraySize; i++) {
		temp[i] = root[i];
	}

	delete root;
	root = new Node[n];

	for (int i = 0; i < ArraySize; i++) {
		root[i] = temp[i];
	}
	delete[] temp;

}

// Constructor
MinHeap::MinHeap() {
	
	root = new Node[10];
	ArraySize = 10;
	HeapSize = 0;

}

int main()
{
	// Mode: Determines which testing function
	// Key: keys of nodes to be added to heap 
	int mode, key;
	cin >> mode; 

	MinHeap heap;
	Node* temp;

	//Adding Nodes to Heap
	while (cin >> key) {
        temp = new Node;
		temp->Set_key(key);	
		heap.Add(temp);
	}

	// Mode 0: test Add()
	if (mode == 0) {
		heap.BSTraverse();
	}

	// Mode 1: test Root()
	else if (mode == 1) {
		temp = heap.Root();
		cout << temp->Get_key();
	}

	// Mode 2: test Remove()
	else if (mode == 2) {
		heap.Remove();
		heap.BSTraverse();
	}

	// Mode 3: MinHeap Application: Sort
	else if (mode == 3) {

		// Construct Array of Nodes with Keys 5, 4, 3, 2, 1
		Node arr[5];
		for (int i = 0; i < 5; i++) {
			arr[i].Set_key(5-i);
		}

		// Add keys to MinHeap one-by-one
		for (int i = 0; i < 5; i++) {
			heap.Add(&arr[i]);
		}

		// Remove keys from MinHeap one-by-one and place them back
		// into array: now sorted from MinHeap operations
		for (int i = 0; i < 5; i++) {
			arr[i] = *heap.Root();
			heap.Remove();
		}

		// Print out new array: Should be 1, 2, 3, 4, 5
		for (int i = 0; i < 5; i++) {
			cout << arr[i].Get_key();
		}


	}
	
	return 0;
}

