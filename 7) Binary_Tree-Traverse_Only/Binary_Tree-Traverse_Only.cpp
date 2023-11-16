//
// 
// This file implements the 4 different traverse algorithms of a binary tree, but
// does not actually implement the tree actions/properties [Can be seen in next file]
// 
// Traverse Algorithms: Pre-Order, In-Order, Post-Order, Breadth-First
// 
// It also implements a Convert function that uses a Breadth-First algorithm to convert
// the Binary Tree into an array
// 
// 
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

//
// Basic Node Class used to implement binary tree: Each node holds pointers to its
// parent, left child, and right child [or NULL if it doesn't have any of these]
//
class Node {
private:
	int key;
	Node* left;
	Node* right;
	Node* parent;
public:
	void Set_key(int x);
	int Get_key();
	void Set_left(Node* p);
	void Set_right(Node* p);
	void Set_parent(Node* p);
	Node* Get_left();
	Node* Get_right();
	Node* Get_parent();
	Node();
};
Node::Node() {
	key = 0;
	left = NULL;
	right = NULL;
	parent = NULL;
}
void Node::Set_key(int x) {
	key = x;
}
int Node::Get_key() {
	return key;
}
void Node::Set_left(Node* p) {
	left = p;
}
void Node::Set_right(Node* p) {
	right = p;
}
void Node::Set_parent(Node* p) {
	parent = p;
}
Node* Node::Get_left() {
	return left; 
}
Node* Node::Get_right() {
	return right;
}
Node* Node::Get_parent() {
	return parent;
}

//  
// Function performs Traverse on the tree/subtree whose
// root is Node "p" based on the String input "s":
// 
// Input "s" expects value in {"pre","post","in","bf"}
// "pre" : pre-order traverse
// "post" : post-order traverse
// "in" : in-order traverse
// "bf" : breadth-first traverse
// Any other value of "s" prints "-1" and returns
// 
// The function prints out the key of every Node as it is visited
// 
void Traverse(Node* p, string s) {
	if (p->Get_left() == NULL && p->Get_right() == NULL) {
		cout << p->Get_key();
		return;												//Base Case: Once a leaf node is reached, print out its key and return
	}

	if (s == "pre") {
		cout << p->Get_key();
		if (p->Get_left() != NULL) Traverse(p->Get_left(), s);		//Pre-Order: Prints head key, then calls left subtree, then right subtree
		if (p->Get_right() != NULL) Traverse(p->Get_right(), s);
	}
	else if (s == "in") {
		if (p->Get_left() != NULL) Traverse(p->Get_left(), s);
		cout << p->Get_key();										//In-Order: Calls left subtree, then prints head, then calls right subtree
		if (p->Get_right() != NULL) Traverse(p->Get_right(), s);
	}
	else if (s == "post") {
		if (p->Get_left() != NULL) Traverse(p->Get_left(), s);		//Post-Order: Calls left subtree, then calls right subtree, then prints head
		if (p->Get_right() != NULL) Traverse(p->Get_right(), s);
		cout << p->Get_key();
	}
	else if (s == "bf") {
		queue<Node*>* x = new queue<Node*>;							//Breadth-First: NOT RECURSIVE --> Uses queue to keep track of nodes and their
		x->push(p);													//children, printing out one by one
		while (!x->empty()) {
			if (x->front()->Get_left() != NULL) x->push(x->front()->Get_left());
			if (x->front()->Get_right() != NULL) x->push(x->front()->Get_right());
			cout << x->front()->Get_key();
			x->pop();
		}
		delete x;
	}
	else {
		cout << -1;													//If none of the key strings are picked up, return -1
	}
}



// 
// Function measures height of a list-based tree/subtree held at "root"
// 
// Returns an integer representing the height
// 
int HeightRecursive(Node* root, int curDepth);	//Initialize Function

int Height(Node* root) {
	return HeightRecursive(root, 0);			//Make a call to Recursive Function, starting with tree root and height 0
}

int HeightRecursive(Node* root, int curDepth) {		//root is the root of the subtree being looked it, curDepth keeps track of the current depth of that node
	if (root->Get_left() == NULL && root->Get_right() == NULL) return curDepth;	//If node is leaf, return its depth

	int leftDepth = curDepth;	//Initialize separate depth vars for each side of subtree
	int rightDepth = curDepth;
	if (root->Get_left() != NULL) leftDepth = HeightRecursive(root->Get_left(), curDepth + 1);		//If root has a left child, test left subtree and increase curDepth
	if (root->Get_right() != NULL) rightDepth = HeightRecursive(root->Get_right(), curDepth + 1);	//If root has a right child, test right subtree and increase curDepth

	if (leftDepth > rightDepth) return leftDepth;		//Return the larger value between depth of right and left subtree [Height of tree is maximum depth found]
	return rightDepth;
}

// 
// Function converts a list-based tree into an array-based tree 
// 
// "root" is a pointer to the root node of the given list-based tree 
// "height" is height of the tree (found using Height function)
// 
// Function returns a pointer of an object array which holds the tree 
//  
Node* Convert2Array(Node* root, int height) {
	int size = pow(2, (height + 1)) - 1;	//Find max number of nodes given the height of a binary tree
	Node* treeArr = new Node[size];						//Initialize array with given height parameters
	queue<Node*>* x = new queue<Node*>;
	x->push(root);
	int i = 0;											//Breadth-First traverse: Similar to traverse function, use queue to keep track of children while
	while (!x->empty() && i < size) {					//adding root nodes to array one by one
		if (x->front()->Get_left() != NULL) {
			x->push(x->front()->Get_left());
		}
		if (x->front()->Get_right() != NULL) {
			x->push(x->front()->Get_right());
		}
		treeArr[i++] = *x->front();
		x->pop();
	}
	delete x;
	return treeArr;									//Free queue space, return resulting array
}

// 
// Main Function: Used for testing
//  
int main()
{
	// Constructing a binary tree [Formal addition function in next file]
	Node A, B, C, D, E, F, G;
	A.Set_key(5);
	B.Set_key(4);
	C.Set_key(2);
	D.Set_key(11);
	E.Set_key(9);
	F.Set_key(12);
	G.Set_key(7);
	A.Set_left(&B);
	A.Set_right(&C);
	B.Set_left(&D);
	B.Set_right(&E);
	C.Set_left(&F);
	C.Set_right(&G);
	B.Set_parent(&A);
	C.Set_parent(&A);
	D.Set_parent(&B);
	E.Set_parent(&B);
	F.Set_parent(&C);
	G.Set_parent(&C);

	Node* root = &A;

	// Input test mode
	int mode;

	cin >> mode;

	// Mode 0: test pre-order traverse
	if (mode == 0) {
		Traverse(root, "pre");
	}

	// Mode 1: test post-order traverse 
	else if (mode == 1) {
		Traverse(root, "post");
	}

	// Mode 2: test in-order traverse 
	else if (mode == 2) {
		Traverse(root, "in");
	}

	// Mode 3: test breadth-first traverse 
	else if (mode == 3) {
		Traverse(root, "bf");
	}

	// Mode 4: test Height function 
	else if (mode == 4) {
		cout << Height(root);
	}

	// Mode 5: test Convert function 
	else if (mode == 5) {
		Node *arr = Convert2Array(root, Height(root));
		for (int i = 0; i < pow(2, Height(root) + 1) - 1; i++) {
			cout << arr[i].Get_key();
		};
	}

	return 0;
}

