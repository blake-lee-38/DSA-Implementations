// 
// This file implements a hash table uses coalesced chaining 
// to deal with collisions -> The chains are implemented 
// using singly linked list 
// 
#include <iostream>
using namespace std;


//
// Basic Node class used to facilitate Hash Table implementation:
// NOTE: int idx_next is stored instead of pointer p_next to 
// allow for coalesced chaining in the table
//
class Node {
private:
	int key;
	int idx_next;
public:
	void Set_key(int x);
	int Get_key();
	void Set_index(int x);
	int Get_index();
	Node();
};

Node::Node() {
	key = -1;
	idx_next = -1;
}

void Node::Set_key(int x) {
	key = x;
}

int Node::Get_key() {
	return key;
}

void Node::Set_index(int x) {
	idx_next = x;
}

int Node::Get_index() {
	return idx_next;
}



// 
// The HashTable class implements a hash table that addresses collisions
// with coalesced chaining
// 
// The table is stored as an array of Node objects -> When the table/array
// is filled, it is resized by doubling size of array/table and rehashing
// elements
// 
class HashTable {

private:

	// Size of the hash table. 
	int size;

	// Stores original divisor when Hash Table is created [For Hash Function]
	int origDiv;

	// Basic hash function that returns key % divisor
	int hash(int key);

	// Pointer to the hash table [Array of Nodes]  
	Node* table;

	// Resizes Hash Table and re-hashes elements
	void Resize();

public:

	// 
	// Creates a hash table (through dynamic memory allocation) and initializes all cells to NULL.
	// Creates a table with size = divisor [due to nature of basic hash function]
	// 
	void CreateTable(int divisor);


	// 
	// Searches for a student whose SID = key 
	// If a student is found return index of the student in the table 
	// Otherwise, return -1
	//
	int Search(int key);


	// 
	// Adds a student to the hash table
	// Uses linear probing to look for an empty cell in the
	// case of a collision
	// 
	void Add(Node temp);


	// 
	// Removes a student whose SID = key from the table
	// If the student is not in the table, it does nothing. 
	//
	void Remove(int key);


	// 
	// Returns table size held in variable "size"
	//
	int Get_Size();


	// 
	// Constructor: Initializes table to NULL, size & origDiv to 0
	//
	HashTable();


	// 
	// First print function used for testing: simply prints all Nodes
	// from table[0] to table[size - 1] in order
	//
	void PrintTable();


	// 
	// Second print function used for testing: Given a key, it hashes
	// and prints out the chain of Nodes starting at that hashed value
	// 
	// Used to test coalesced chaining
	//
	void PrintChain(int key);
};

int HashTable::hash(int key) {
	return key % origDiv;			//Basic hash function
}

void HashTable::CreateTable(int divisor) {
	origDiv = divisor;
	size = divisor;
	table = new Node[size];					//Set size of table to divisor, initialize table with that size
	for (int i = 0; i < size; i++) {
		table[i].Set_key(-1);				//Setting key to -1 indicates all cells are empty
		table[i].Set_index(-1);
	}
}

int HashTable::Search(int key) {
	int hashed = hash(key);
	if (table[hashed].Get_key() == key) return hashed;				//First Case: Check at Location in Table
	Node* traverser = &table[hashed];
	while (traverser->Get_index() != -1) {							//Second Case: Check down the chain, return index if key is found
		if (table[traverser->Get_index()].Get_key() == key) return traverser->Get_index();
		traverser = &table[traverser->Get_index()];
	}
	return -1;														//Third Case: If the end of the chain is reached, return -1 [Not found]														
}

void HashTable::Resize() {
	size = size * 2;
	Node* temp = new Node[size];					//Create new table with double the size
	int i;
	for (i = 0; i < size / 2; i++) {				//Fill first half with old values
		temp[i].Set_key(table[i].Get_key());
		temp[i].Set_index(table[i].Get_index());
	}
	for (i = size / 2; i < size; i++) {				//Fill second half with empty values
		temp[i].Set_key(-1);
		temp[i].Set_index(-1);
	}
	delete table;									//Free old table, reassign to new table
	table = temp;
}

void HashTable::Add(Node temp) {
	int hashed = hash(temp.Get_key());
	
	if (table[hashed].Get_key() == -1) {
		table[hashed].Set_key(temp.Get_key());		//First Case: If hash location is empty, add at that location
		return;
	}

	for (int i = 1; i < size; i++) {						//Second Case: If hash location is full, probe until empty cell is found and add
		if (table[(hashed + i) % size].Get_key() == -1) {
			table[hashed + i].Set_key(temp.Get_key());
			Node* list = &table[hashed];
			while (list->Get_index() != -1) list = &table[list->Get_index()];
			list->Set_index(hashed + i);
			return;
		}
	}

	Resize();												//If no empty cell if found, resize the table

	for (int i = 1; i < size; i++) {
		if (table[(hashed + i) % size].Get_key() == -1) {		//Re-find new index after resizing table
			table[hashed + i].Set_key(temp.Get_key());
			Node* list = &table[hashed];
			while (list->Get_index() != -1) list = &table[list->Get_index()];
			list->Set_index(hashed + i);
			return;
		}
	}
}

void HashTable::Remove(int key) {
	int target = hash(key);

	if (table[target].Get_key() == -1) return;				//If key index is empty, there is no node to remove so return

	if (table[target].Get_key() == key) {
		if (table[target].Get_index() == -1) {
			table[target].Set_key(-1);						//If key is at index, move node that is next in the chain to
			return;											//index, then return
		}
		Node* nextChain = &table[table[target].Get_index()];
		table[target].Set_key(nextChain->Get_key());
		table[target].Set_index(nextChain->Get_index());
		nextChain->Set_index(-1);
		nextChain->Set_key(-1);
		return;
	}
	Node* chainTraverse = &table[target];
	while (chainTraverse->Get_index() != -1) {				//Traverse through chain looking for key, if found, remove node
		Node* test = &table[chainTraverse->Get_index()];	//[set to empty], and rebuild chain around node
		if (test->Get_key() == key) {
			chainTraverse->Set_index(test->Get_index());
			test->Set_index(-1);
			test->Set_key(-1);
			return;
		}
		chainTraverse = &table[chainTraverse->Get_index()];
	}
}															//If key is never found, return without doing anything

// Constructor
HashTable::HashTable() {
	table = NULL;
	size = 0;
	origDiv = 0;
}

int HashTable::Get_Size() {
	return size;			//Returns table size
}

//First Print Function
void HashTable::PrintTable() {
	for (int i = 0; i < size; i++) {
		cout << table[i].Get_key() << '\n';
	}
}


// 2nd Print Function
void HashTable::PrintChain(int key) {
	int temp = hash(key);
	while (temp != -1) {
		cout << table[temp].Get_key() << '\n';
		temp = table[temp].Get_index();
	}
}


// 
// Main Function: Testing
// 
int main()
{
	int mode, temp;

	// Search key to test the search and remove functions. 
	int key;

	// Used by the 2nd print function.
	int key_chain;

	// Used by the hash function and CreateTable() function 
	int divisor;

	
	Node Student;

	HashTable x;

	cin >> mode >> key >> key_chain >> divisor;

	x.CreateTable(divisor);

	while (cin >> temp) {

		Student.Set_key(temp);

		x.Add(Student); 
	}

	// Mode 0: test the "Add" function and the resizing/rehashing processes. 
	if (mode == 0) {
		x.PrintTable();
	}

	// Mode 1: test if chains are correct
	else if (mode == 1) {
		x.PrintChain(key_chain);	
	}

	// Mode 2: test the "Search" function 
	else if (mode == 2) {
		cout << x.Search(key);
	}

	// Mode 3: test the "Remove" function 
	else if (mode == 3) {
		x.Remove(key);
		x.PrintTable();
		x.PrintChain(key);
	}

	return 0;
}

