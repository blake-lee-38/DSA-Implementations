//
// This file implements an AVL tree, but can also do standard 
// Binary Search Tree adding and removal without checking
// for AVL properties
// 
// It includes a basic Node class for tree Nodes
// and an AVL class to hold AVL tree functions
// 
// 
// 

#include <iostream>
using namespace std;

//
// Basic Node class for tree implementation: could be modified
// to include more satellite data, etc
//
class Node {
private:
	int key;
	Node* p_left; 
	Node* p_right;
	Node* p_parent;
public:
	void Set_key(int x);
	int Get_key();
	void Set_left(Node *p);
	void Set_right(Node* p);
	void Set_parent(Node* p);
	Node* Get_left();
	Node* Get_right();
	Node* Get_parent();
	Node();
	Node* clone();
};

void Node::Set_key(int x) {
	key = x;
}

int Node::Get_key() {
	return key;
}

void Node::Set_left(Node* p) {
	p_left = p;
}

void Node::Set_right(Node* p) {
	p_right = p;
}

void Node::Set_parent(Node* p) {
	p_parent = p;
}

Node* Node::Get_left() {
	return p_left;
}

Node* Node::Get_right() {
	return p_right;
}

Node* Node::Get_parent() {
	return p_parent;
}

//
// Clone function used in rotation of AVL tree
//
Node* Node::clone() {
	Node* clone = new Node;
	clone->Set_key(key);
	clone->Set_left(p_left);
	clone->Set_right(p_right);
	clone->Set_parent(p_parent);
	return clone;
}

Node::Node() {
	key = -1;
	p_left = NULL;
	p_parent = NULL;
	p_right = NULL;
}

class AVL {
private:
	
	// This is root of the AVL
	Node* root;

	//Recursive pre-traverse function used to supplement public PreTraverse function
	void RecursivePreTrav(Node* root);

	//Supplements removal on tree: Finds the either the maximum child in the Node's left subtree
	//or the minimum child in the Node's right subtree [Choice based on boolean value passed]
	Node* findReplacement(Node* p, bool maxLeft);

	//Helper method that return true if the node child is the left child of the node parent
	//and false if the node child is the right child of the node parent
	bool isLeftChild(Node* child, Node* parent);

	//Recursive function used to handle the full removal and replacement on AVL tree as well
	//as maintaining AVL properties
	Node* fillHole(Node* removal);

	//Uses the parents and grandparents of node p to describe the violation type and subsequent
	//rotation sequence needed to restore AVL property
	void RotationSequence(string violation,Node* p);


public:

	// Implements pre-order traverse starting from the root
	// Used to test if updated AVL/BST is correct 
	void PreTraverse();

	// Returns the root node
	// Used to evaluate/test Height function
	Node* GetRoot();

	// Performs search on the AVL with "key"
	// Returns address of a matching node or returns NULL if no 
	// matching node is found
	Node* Search(int key);

	// Adds a new node held by p to AVL
	// Does not consider AVL Property (Standard BST adding)
	// Returns address of Node (Used in AVL adding method)
	Node* Add(Node* p);

	// Removes a node with "key" from AVL
	// Does not consider AVL Property (Standard BST removal)
	// Returns Node's address in the tree (Used in AVL removal method)
	Node* Remove(int key);

	// Adds a new node held by p by first using standard BST add,
	// then checks for violations and calls necessary operations
	// to retain AVL properties
	void Add_AVL(Node* p);

	// Removes a new node with "key" by first using standard BST removal,
	// then checks for violations and calls necessary operations
	// to retain AVL properties
	void Remove_AVL(int key);

	// Returns height of a tree/subtree rooted at "p". 
	int Height(Node* p);

	// Performs clock-wise rotation at node "p"
	// Used to retain AVL property
	// Returns address of new parent node
	Node* Rotate_cw(Node* p);

	// Performs counter clock-wise rotation at node "p"
	// Used to retain AVL property
	// Returns address of new parent node
	Node* Rotate_cc(Node* p);

	// Checks if there is a violation at a node p, and returns the violation scenario
	// Possible return values:
	// - "NO" if no violation 
	// - "LL" if it is left-left violation 
	// - "RR" if it is right-right violation
	// - "LR" if it is left-right violation
	// - "RL" if it is right-left violation
	string CheckViolation(Node* p);

	// Constructor: Intiailizes root = NULL.
	AVL();
};

//
// Recursive helper method for PreTraverse function -> Prints root, then left subtree, then right subtree
//
void AVL::RecursivePreTrav(Node* root) {
	cout << root->Get_key();

	if (root->Get_left() != NULL) RecursivePreTrav(root->Get_left());
	if (root->Get_right() != NULL) RecursivePreTrav(root->Get_right());
}

//
// PreTraverse function for tree -> Simply passes root into recursive PreTraverse function
//
void AVL::PreTraverse() {
	if(root != NULL) RecursivePreTrav(root);
}

//
// Returns tree root
//
Node* AVL::GetRoot() {
	return root;
}

//
// Performs standard search on BST, returning the Node with the specified key if it is found, or NULL if not
//
Node* AVL::Search(int key) {
	Node* searchNode = root;

	while (searchNode != NULL) {
		if (searchNode->Get_key() == key) {
			return searchNode;
		}
		else if (key < searchNode->Get_key()) {
			searchNode = searchNode->Get_left();
		}
		else {
			searchNode = searchNode->Get_right();
		}
	}

	return NULL;
}

//
// Performs standard add on BST with no regard to AVL property, returns address of parent of added node
//
Node* AVL::Add(Node* p) {
	if (root == NULL) {
		root = p;
		return NULL;
	}

	Node* findInsertion = new Node;
	findInsertion = root;
	bool found = false;

	while (!found) {
		if (p->Get_key() < findInsertion->Get_key()) {
			if (findInsertion->Get_left() != NULL) {
				findInsertion = findInsertion->Get_left();
			}
			else {
				p->Set_parent(findInsertion);
				findInsertion->Set_left(p);
				found = true;
			}
		}
		else {
			if (findInsertion->Get_right() != NULL) {
				findInsertion = findInsertion->Get_right();
			}
			else {
				p->Set_parent(findInsertion);
				findInsertion->Set_right(p);
				found = true;
			}
		}
	}

	return findInsertion;
}

//
// Used to find optimal replacement Node after removal: Searches for max
// value in left subtree if maxLeft is true, otherwise searches for min value
// in the right subtree
//
Node* AVL::findReplacement(Node* p, bool maxLeft) {
	if (p->Get_right() == NULL && p->Get_left() == NULL) return p;
	
	if (maxLeft && p->Get_right() == NULL) {
		return p;
	}
	else if (!maxLeft && p->Get_left() == NULL) {
		return p;
	}
	else if (maxLeft) {
		findReplacement(p->Get_right(), maxLeft);
	}
	else {
		findReplacement(p->Get_left(), maxLeft);
	}
}

//
// Helper method used by multiple larger methods: Returns true if child
// node is parent's left child, false is it is right child
//
bool AVL::isLeftChild(Node* child, Node* parent) {
	if (parent->Get_left() == child) {
		return true;
	}
	else {
		return false;
	}
}

//
// Used during removal to maintain BST properties and choose correct Node to fill the hole
//
Node* AVL::fillHole(Node* removal) {
	if (removal == NULL) return NULL;
	bool isRoot = (removal->Get_parent() == NULL);

//Case 1: If the Node we are removing is a leaf node, then we will simply set the applicable
//parent pointer to NULL and return the parent after removing the Node
	if (removal->Get_right() == NULL && removal->Get_left() == NULL) {
		if (isRoot) {
			delete removal;
			root = NULL;
			return root;
		}
		Node* returnParent = removal->Get_parent();
		if (isLeftChild(removal, returnParent)) {
			returnParent->Set_left(NULL);
		}
		else {
			returnParent->Set_right(NULL);
		}
		delete removal;
		return returnParent;
	}

//Case 2: If the Node we are removing only has a left subtree, then we will remove the Node and
//shift its left subtree to take its place, updating the correct pointers in the parent Node and
//left child node, then returning the parent Node
	else if (removal->Get_right() == NULL) {
		if (isRoot) {
			root = root->Get_left();
			delete removal;
			return root;
		}
		Node* returnParent = removal->Get_parent();
		removal->Get_left()->Set_parent(returnParent);
		if (isLeftChild(removal, returnParent)) {
			returnParent->Set_left(removal->Get_left());
		}
		else {
			returnParent->Set_right(removal->Get_left());
		}
		delete removal;
		return returnParent;
	}

//Case 3: See Case 2, but instead Node only has right subtree
	else if (removal->Get_left() == NULL) {
		if (isRoot) {
			root = root->Get_right();
			delete removal;
			return root;
		}
		Node* returnParent = removal->Get_parent();
		removal->Get_right()->Set_parent(returnParent);
		if (isLeftChild(removal, returnParent)) {
			returnParent->Set_left(removal->Get_right());
		}
		else {
			returnParent->Set_right(removal->Get_right());
		}
		delete removal;
		return returnParent;
	}

//Case 4: Node has both a left and right subtree:
	// (1) Calculate the height of both subtrees to determine where to look: want to find replacement Node in subtree with higher height to maintain efficiency
	// (2) Find the correct replacement Node using findReplacement method and result of height calculation
	// (3) Perform the pointer changes needed to replace the replacement node with the node to be removed
	// (4) Delete the node that was intented to be removed, then call fillHole method on Node that was moved up so that it can be correctly replaced/deleted
	else {
		bool searchLeft = (Height(removal->Get_left()) >= Height(removal->Get_right()));
		Node* replacement = (searchLeft) ? findReplacement(removal->Get_left(), searchLeft) : findReplacement(removal->Get_right(), searchLeft);
		Node* clone = replacement->clone();
		clone->Set_left(removal->Get_left());
		clone->Set_right(removal->Get_right());
		clone->Set_parent(removal->Get_parent());
		if (removal->Get_parent() != NULL) {
			if (isLeftChild(removal, removal->Get_parent())) {
				removal->Get_parent()->Set_left(clone);
			}
			else {
				removal->Get_parent()->Set_right(clone);
			}
		}
		if (removal->Get_left() != NULL) removal->Get_left()->Set_parent(clone);
		if (removal->Get_right() != NULL) removal->Get_right()->Set_parent(clone);
		delete removal;
		fillHole(replacement);
	}
}

//
// Searches for the node whose key is "key", then calls the fillHole method to correctly remove
// and replace the node [without AVL property]
//
Node* AVL::Remove(int key) {
	return fillHole(Search(key));
}

//
// Performs rotations needed to maintain AVL property using string from CheckViolation method
//
void AVL::RotationSequence(string violation, Node* p) {
	if (violation == "NO") return;
	
	if (violation == "LL") {
		Rotate_cw(p);
	}
	else if (violation == "LR") {
		Rotate_cc(p->Get_left());
		Rotate_cw(p);
	}
	else if (violation == "RR") {
		Rotate_cc(p);
	}
	else if (violation == "RL") {
		Rotate_cw(p->Get_right());
		Rotate_cc(p);
	}
}

//
// Adds to tree while maintaining AVL property: first performs standard BST add, then checks
// for violations and handles them properly until root is reached
//
void AVL::Add_AVL(Node* p) {
	Node* firstParent = Add(p);

	while (firstParent != NULL) {
		RotationSequence(CheckViolation(firstParent), firstParent);
		if (firstParent->Get_parent() == NULL) root = firstParent;
		firstParent = firstParent->Get_parent();
	}
}

//
// Removes node with key "key" from tree while maintaining AVL property: removes using standard BST
// removal, then checks for violations and handles them until bottom of the tree is reached
//
void AVL::Remove_AVL(int key) {
	Node* firstCheck = Remove(key);

	while (firstCheck != NULL) {
		RotationSequence(CheckViolation(firstCheck), firstCheck);
		firstCheck = firstCheck->Get_parent();
	}

}

//
// Recursive function used to find the height of the subtree rooted at node p, used for AVL checks
//
int AVL::Height(Node* p) {
	if (p == NULL) return -1;

	if (p->Get_left() == NULL && p->Get_right() == NULL) {
		return 0;
	}
	else if (p->Get_left() == NULL) {
		return Height(p->Get_right()) + 1;
	}
	else if (p->Get_right() == NULL) {
		return Height(p->Get_left()) + 1;
	}
	else {
		int lSize = Height(p->Get_left());
		int rSize = Height(p->Get_right());
		return max(lSize, rSize) + 1;
	}
}

//
// Performs counter-clockwise Node rotation from Node p and returns new parent for further checks
//
Node* AVL::Rotate_cc(Node* p) {
	Node* newRoot = p->Get_right();
	newRoot->Set_parent(p->Get_parent());
	if (p->Get_parent() != NULL && isLeftChild(p, p->Get_parent())) {
		p->Get_parent()->Set_left(newRoot);
	}
	else if(p->Get_parent() != NULL) {
		p->Get_parent()->Set_right(newRoot);
	}
	if(newRoot->Get_left() != NULL) newRoot->Get_left()->Set_parent(p);
	p->Set_parent(newRoot);
	p->Set_right(newRoot->Get_left());
	newRoot->Set_left(p);

	return p->Get_parent();
}

//
// Performs clockwise Node rotation from Node p and returns new parent for further checks
//
Node* AVL::Rotate_cw(Node* p) {
	Node* newRoot = p->Get_left();
	newRoot->Set_parent(p->Get_parent());
	if (p->Get_parent() != NULL && isLeftChild(p, p->Get_parent())) {
		p->Get_parent()->Set_left(newRoot);
	}
	else if(p->Get_parent() != NULL) {
		p->Get_parent()->Set_right(newRoot);
	}
	if (newRoot->Get_right() != NULL) newRoot->Get_right()->Set_parent(p);
	p->Set_parent(newRoot);
	p->Set_left(newRoot->Get_right());
	newRoot->Set_right(p);

	return p->Get_parent();
}

//
// Checks for AVL violation at Node p, then returns what type of violation it is
//  [See class declaration for more details]
//
string AVL::CheckViolation(Node* p) {
	int lHeight = Height(p->Get_left());
	int rHeight = Height(p->Get_right());

	if (abs(lHeight - rHeight) <= 1) {
		return "NO";
	}
	else if (lHeight > rHeight) {
		if (Height(p->Get_left()->Get_left()) >= Height(p->Get_left()->Get_right())) {
			return "LL";
		}
		else {
			return "LR";
		}
	}
	else {
		if (Height(p->Get_right()->Get_right()) >= Height(p->Get_right()->Get_left())) {
			return "RR";
		}
		else {
			return "RL";
		}
	}
}

//
// Constructor: Initialize root to NULL
//
AVL::AVL() {
	root = NULL;
}


// --------------
// Main Function 
// --------------
int main()
{
	// mode_test: indicate which function to test 
	// model_avl: if 1, do adding with AVL property
	//            if 0, do adding without AVL property (standard bst adding)
	// key_temp:  keys of nodes to add to AVL initially
	// key_search:key of node for search/remove
	int mode_test, mode_avl, key_temp, key_search;
	
	Node* temp;

	// This is our AVL tree object.
	AVL tree;

	cin >> mode_test >> mode_avl >> key_search;

	while (cin >> key_temp) {

		temp = new Node;
		temp->Set_key(key_temp);

		if (mode_avl == 0)
		{
			tree.Add(temp);
		}
		else if (mode_avl == 1) {
			tree.Add_AVL(temp);
		}
	}

	// Mode 0: test "Add" function
	if (mode_test == 0) {
		tree.PreTraverse();
	}

	// Mode 1: test "Add_AVL" function
	else if (mode_test == 1) {
		tree.PreTraverse();
	}

	// Mode 2: test "Search" function 
	else if (mode_test == 2) {
		temp = tree.Search(key_search);
		if (temp == NULL) {
			cout << -1;
		}
		else {
			cout << temp->Get_key();
		}		
	}

	// Mode 3: test "Remove" function 
	else if (mode_test == 3) {
		tree.Remove(key_search);
		tree.PreTraverse();
	}

	// Mode 4: test "Remove_AVL" function 
	else if (mode_test == 4) {
		tree.Remove_AVL(key_search);
		tree.PreTraverse();
	}

	// Mode 5: test "Height" function 
	else if (mode_test == 5) {
		cout << tree.Height(tree.GetRoot());
	}


	return 0;
}