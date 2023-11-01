//
// This assignment implements
// a singly linked list class based on
// a basic node class
//
#include <iostream>
using namespace std;


//Node Class: Contains encapsulation methods for Student Information (ID & GPA)
	//Holds a pointer that points to the next item in the list, or "NULL" if it is end of list
class Node {
private:
	int SID;
	float GPA;
	Node* p_next;
public:
	void Set_SID(int x);
	void Set_GPA(float y);
	int Get_SID();
	float Get_GPA();
	void Set_Pnext(Node* p);
	Node* Get_Pnext();
	Node();
};
void Node::Set_SID(int x) {
	SID = x;
}
void Node::Set_GPA(float y) {
	GPA = y;
}
int Node::Get_SID() {
	return SID;
}
float Node::Get_GPA() {
	return GPA;
}
void Node::Set_Pnext(Node* p) {
	p_next = p;
}
Node* Node::Get_Pnext() {
	return p_next;
}
Node::Node() {
	SID = -1;
	GPA = -1;
	p_next = NULL;
}



//
// The List class uses a Node pointer head to store the head of the linked list
// Contains methods that allow user to perform basic linked list operations
//
class List {
private:
	Node* head;
public:

// List Constructor
	List();

// Print SIDs of all Students in the list starting from head
	void PrtSID();

//Takes in inputs to create Linked List, adding later Nodes to the head
//of the list
	void Create();

// Returns the size of the list [0 if empty]
	int Lsize();

// Returns Node in list if found, NULL if not
	Node* Find(int key);

//Inserts new node "p" in the list at the index given by "idx"
//Returns 1 if insertion was successful, -1 if "idx" is out of list range
	int Insert(Node* p, int idx);

// Remove function removes the idx_th node from the list. 
// Return 1 if removal is successful and -1 if idx is out of range
	int Remove(int idx);
	// Reverse function reserves the list.
	// For example, if the current list has
	// three nodes A->B->C, after running
	// Reverse the order should be C->B->A.
	// As another example, if we call the
	// print function and get 246, after
	// running Reverse we should get 642.
	void Reverse();
	// Clear function removes all nodes from
	// the list (so it becomes an empty list).
	void Clear();
};

//Initialize head to NULL
List::List() {
	head = NULL;
}

//Prints out SID of each Student in the list starting at head
void List::PrtSID() {
	Node* temp = head;
	while (temp != NULL)
	{
		cout << temp->Get_SID();
		temp = temp->Get_Pnext();
	}
}


//Creating Linked List with inputs
void List::Create() {
	int SID;
	float GPA;
	while (cin >> SID >> GPA) { //While Valid Input Is Found
		Node* next = new Node;
		next->Set_SID(SID);
		next->Set_GPA(GPA);		
		next->Set_Pnext(head);  //Creates a new node using the SID and GPA from input,
		head = next;			//then links new node to the head of the list, making new node the new head
	}
}

int List::Lsize() {
	Node* temp = head;
	int size = 0;
	while (temp != NULL) {
		size++;					//Steps through every node in list, adding 1 to size for every node found(Not NULL)
		temp = temp->Get_Pnext();	
	}
	return size;				//Returns Size of List
}

Node* List::Find(int key) {
	Node* temp = head;
	Node* answer = NULL;
	while (temp != NULL) {				//Tests if there is another valid node in the list
		if (temp->Get_SID() == key) {
			answer = temp;
			break;						//Looks if current node's SID is equal to key: If so,
		}								//assigns answer to current node and breaks out of loop (Stops looking)

		temp = temp->Get_Pnext();		//Moves to next node in list
	}

	return answer;						//If node w/ key was found, returns that node, otherwise returns NULL as initialized
}

int List::Insert(Node* p, int idx) {
	if (idx < 1 || idx > Lsize() + 1) return -1;	//Tests if value of idx is in valid range to insert node
	else if (idx == 1) {
		p->Set_Pnext(head);				//Handles case where idx is equal to one and inserts node at head of list
		head = p;
	}
	else {
		Node* target = head;
		for (int i = 1; i < idx - 1; i++) {
			target = target->Get_Pnext();		//Moves the target node to one index before "idx"
		}
		p->Set_Pnext(target->Get_Pnext());		//Creates link between the node to be inserted and the list elements following it
		target->Set_Pnext(p);					//Creates link between the element at "idx - 1" and the new node being inserted
	}
	return 1;
}

int List::Remove(int idx) {
	if (idx < 1 || idx > Lsize()) return -1;	//Tests if value of idx is in valid range to remove a node
	else if (idx == 1) {
		Node* removal = head;
		head = removal->Get_Pnext();			//Handles case where idx is equal to 1: Removes head of the list and stores it in 
		delete removal;							//"removal" variable so that memory can be propoerly freed
	}
	else {
		Node* target = head;					//Handles case where idx is valid, but not 1
		for (int i = 1; i < idx - 1; i++) {
			target = target->Get_Pnext();		//Moves target node to one before index specified by "idx"
		}
		Node* removal = target->Get_Pnext();	//Stores node to be deleted in "removal" variable to be able to properly free memory later
		target->Set_Pnext(removal->Get_Pnext());//"Jumps Over" node to be removed: Establishes connection between node before and after removal node
		delete removal;							//Frees up memory for node that was removed
	}

	return 1;
}

void List::Reverse() {
	Node* traverser = head;					//Creates traverser variable to step through every element of List
	head = NULL;
	while (traverser != NULL) {				//Loops until every element in list has been covered
		Node* next = traverser->Get_Pnext();//Creates next variable to hold next element in List
		traverser->Set_Pnext(head);			
		head = traverser;					//Adds node pointed to by traverser to the head of the new list
		traverser = next;					//Assigns traverser to next element in original list
	}
}											//As loop runs, each later element in the list will be brought to the front
											//by being assigned to head, then pushed back as more and more elements get
											//brought to front, thus reversing the lists order

void List::Clear() {
	Node* previous = head;
	Node* next = previous;
	while (previous != NULL) {				//Uses next and previous pointers to step through every element of the list
		next = previous->Get_Pnext();
		delete previous;					//One by one, the next pointer holds the next element of the list, then the
		previous = next;					//previous pointer is used to free the memory at the current index, then moved
	}										//up to catch up with next, then process is repeated
	
	head = NULL;							//Assign head back to NULL
}




int main()
{
	int mode, key, sid, idx;
	float gpa;
// First five inputs are for testing:
	// "mode" determines which function to test.
	// "key" is used to evaluate Find().
	// "sid" and "gpa" are used to evaluate Insert().
	// "idx" is used to evaluate Insert() and Remove().
	cin >> mode >> key >> sid >> gpa >> idx;
	
	// declare a singly linked list named "x"
	List x;
	
	// input data to x.
	// After this, a list should be created
	// and stored at address "head".
	x.Create();

	// Mode 0: test Create()
	if (mode == 0) {
		x.PrtSID();
	}

	// Mode 1: test Lsize()
	else if (mode == 1) {
		cout << x.Lsize();
	}

	// Mode 2: test Find()
	else if (mode == 2) {
		Node* temp = x.Find(key);
		if (temp == NULL) {
			cout << -1;
		}
		else {
			cout << temp->Get_GPA();
		}
	}

	// Mode 3: test Insert()
	else if (mode == 3) {
		Node* temp = new Node;
		temp->Set_SID(key);
		temp->Set_GPA(3.5);
		x.Insert(temp, idx);
		x.PrtSID();
	}

	// Mode 4: test Remove()
	else if (mode == 4) {
		x.Remove(idx);
		x.PrtSID();
	}

	// Mode 5: test Reverse()
	else if (mode == 5) {
		x.Reverse();
		x.PrtSID();
	}

	// Mode 6: test Clear()
	else if (mode == 6) {
		x.Clear();
		cout << x.Lsize();
	}

	else {
		cout << "Invalid Test";
	}
	return 0;
}