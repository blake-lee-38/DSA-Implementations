//
// This file implements a  hash table which uses separate chaining 
// to deal with collisions 
// The chains should are implemented using singly linked list. 
// 
#include <iostream>
using namespace std;

//
// Basic Node Class used to construct Lists in Hash Table
// [Contains pointer for next Node in list]
//
class Node {
private:
	int key;
	Node* p_next;
	//Other satellite data could be stored here

public:
	void Set_key(int x);
	int Get_key();
	void Set_p(Node* p);
	Node* Get_p();
	Node();
};

Node::Node() {
	key = -1;
	p_next = NULL;
}

void Node::Set_key(int x) {
	key = x;
}

int Node::Get_key() {
	return key;
}

void Node::Set_p(Node* p) {
	p_next = p;
}

Node* Node::Get_p() {
	return p_next;
}

// 
// The HashTable class implements a hash table whose elements 
// are pointers -> Each pointer points to a linked 
// list that holds the student(s) at that key
// 
class HashTable {

private:

	// Size of the hash table. 
	int size;
	
	// Basic Hash Function
	int hash(int key);

	// Pointer to Table
	// Pointer of Pointer: Points to Array of Pointers
	Node** table;

	
public:

	//
	// This function creates a hash table using dynamic memory allocation
	// and initializes all cells to NULL.
	// 
	// Creates table whose size is equal to divisor due to the nature of the
	// basic hash function
	//
	void CreateTable(int divisor);

	//
	// Searches for a student whose SID = key
	// If a student is found, return Student Node, otherwise, return NULL
	//
	Node* Search(int key);

	//
	// This function adds a student (address stored at "temp") to the hash table
	//
	void Add(Node* temp);

	//
	// This function removes a student whose SID = key from the table
	// If the student is not in the table, it does nothing
	//
	void Remove(int key);

	//
	// Returns the table size [Held in private size variable]
	//
	int Get_Size();


	//
	// Constructor: Initialize table to NULL, size to 0
	//
	HashTable();


	// 
	// Print all Nodes/Students in table from top to bottom
	//
	void PrintTable();
};


//Implementing basic hash function using modulo operator and table size
int HashTable::hash(int key) {
	return key % size;
}


//Implementing CreateTable Method
void HashTable::CreateTable(int divisor) {
	size = divisor;						//Step 1: Setting size equal to divisor
										//[Modulo divisor directly indicates table size]
	table = new Node*[size];
	for (int i = 0; i < size; i++) {	//Step 2: Initialize table using size, fill table values with NULL
		table[i] = NULL;
	}
}


Node* HashTable::Search(int key) {
	int hashVal = hash(key);		//Call hash function to get search value
	Node* temp = table[hashVal];	//Initialize temp Node at head to traverse list

	while (temp != NULL) {
		if (temp->Get_key() == key) return temp;	//While temp is not NULL(end of list) test if key equals search key
		temp = temp->Get_p();
	}												//If key is found, return temp Node
	
	return NULL;					//If the entire list is traversed and nothing found, return NULL
}


//Implementing HashTable's "Add" Method
void HashTable::Add(Node* temp) {
	int hashVal = hash(temp->Get_key());	//Hash the nodes value to find table insertion point

	temp->Set_p(table[hashVal]);		//Collision: If point in table already has data,
	table[hashVal] = temp;				//connect it to the temp node to form linked list w/ temp at head
}


//Implementing HashTable's "Remove" Method
void HashTable::Remove(int key) {
	int hashVal = hash(key);						//Call hash function to get HashTable search value

	if (table[hashVal] == NULL) return;				//Edge Case 1: If that table value is empty, return without doing anything

	if (table[hashVal]->Get_key() == key) {			//Edge Case 2: If the head of the linked list at that table value is the
		Node* toDel = table[hashVal];				//Node we want to remove, move the table pointer to the next node and
		table[hashVal] = table[hashVal]->Get_p();	//free the memory
		delete toDel;
		return;
	}
													//Main Logic

	Node* temp = table[hashVal];					//Initialize temp pointer to traverse list at hashed table value
	while (temp->Get_p() != NULL) {
		if (temp->Get_p()->Get_key() == key) {		//Searching forward: If next node has the value we want to remove:
			Node* toDel = temp->Get_p();			//1. Connect current node to node on other side of value to be removed
			temp->Set_p(toDel->Get_p());			//2. Free memory in removed node
			delete toDel;
			return;									//Return: Once it is found, no need to look anymore
		}
	}
}


//Implementing HashTable's "Get_Size" Method
int HashTable::Get_Size() {
	return size;							//Return table's private size variable [Encapsulation]
}


// Constructor
HashTable::HashTable() {
	table = NULL;
	size = 0;
}

//
// Prints all Students/Nodes in table from top to bottom, starting at the 
// head of each list: Used in testing
//
void HashTable::PrintTable() {
	Node* temp = NULL;
	for (int i = 0; i < size; i++) {
		temp = table[i];
		while (temp != NULL) {
			cout << temp->Get_key() << '\n';
			temp = temp->Get_p();
		}
	}
}

// 
// Main Function [Testing]
// 
int main()
{
	int mode, temp;

	// Used as a search key to test the search and remove functions. 
	int key;

	// Divisor is used by the hash function and CreateTable() function 
	// to automatically determine the table size
	int divisor; 

	Node* Student;

	HashTable x;

	cin >> mode >> key >> divisor;

	x.CreateTable(divisor);

	while (cin >> temp) {

		Student = new Node;

		Student->Set_key(temp);

		x.Add(Student);
	}

	// Mode 0: test table size 
	if (mode == 0) {
		cout << x.Get_Size();
	}

	// Mode 1: test the "Add" function 
	else if (mode == 1) {
		x.PrintTable();
	}

	// Mode 2: test the "Search" function 
	else if (mode == 2) {
		Student = x.Search(key);
		if (Student == NULL) {
			cout << -1;
		}
		else {
			cout << Student->Get_key();
		}
	}

	// Mode 3: test the "Remove" function 
	else if (mode == 3) {
		x.Remove(key);
		x.PrintTable();
	}

	return 0;
}

