//
// This file contains implementations of a recursive binary search and merge sort algorithm
// The tests perform binary search on an input array and merge sort on an input linked list
// 
// Through this assignment, I learned important concepts related to recursion and designing
// recursive algorithms, as well as the importance of choosing the right data structure for
// a planned operation 
// [ex. array access makes it optimal for binary search, whereas easy list splitting makes it
// optimal for merge sort] 
// 
#include <iostream>
using namespace std;


//Node Class: Basic Node class designed for merge sort with Singly Linked List
class Node {
public:
	void Set_SID(int x);
	int Get_SID();
	void Set_Pnext(Node* p);
	Node* Get_Pnext();
	Node();
private:
	int SID;
	Node* p_next;
};
void Node::Set_SID(int x) {
	SID = x;
}
int Node::Get_SID() {
	return SID;
}
void Node::Set_Pnext(Node* p) {
	p_next = p;
}
Node* Node::Get_Pnext() {
	return p_next;
}
Node::Node() {
	SID = -1;
	p_next = NULL;
}

//
// Recursive binary search function:
// 
// The function takes a list as input, 
// and outputs index of the search key 
// in the list. It returns -1 if the 
// key is not in the list. 
// 
// For testing purposes, the function also
// prints out the index that is being "searched"
// at every iteration
// 
// 
int BSearch(int* list, int start, int end, int key) {
	if (start > end) {
		if (list[start] == key) {					//Handles the case when start and end converge to one element:
			cout << list[start];
			return start;							//If the element is found, print element and return its index, if not, return -1
		}
		else return -1;
	}

	int test = (start + end) / 2;					//Initialize Test Value Halfway between start and end indexes
	cout << list[test];
	if (key == list[test]) {
		return test;								//If key value found here, return test [Index of value]
	}
	else if (key > list[test]) {
		return BSearch(list, test + 1, end, key);	//If key value is greater than current test, redo search with right sublist
	}
	else{
		return BSearch(list, start, test - 1, key); //If key value is less than current test, redo search with left sublist
	}
}



//
// Recursive merge sort function:
// 
// The function takes a list 
// as input, and outputs address of the 
// head node of the sorted list
//  
// 
Node* MSort(Node* list1, int size) {
	if (size == 1) {
		return list1;								//If the list size is 1, it is inherently sorted, so return it
	}
	
	//
	//	SPLITTING STAGE
	//
	Node* split = list1;
	for (int i = 0; i < (size / 2) - 1; i++) {
		split = split->Get_Pnext();					//Use the size parameter to navigate pointer split to halfway through list
	}
	
	Node* right = split->Get_Pnext();				
	split->Set_Pnext(NULL);							//Use the split pointer to: (1) Make a new pointer that points to the second half of the list
													//							(2) Disconnect First Half from Second Half

	int sizeLeft = size / 2;
	Node* test1 = MSort(list1, sizeLeft);			//Calls sort on the newly split left half of the list
	int sizeRight = size - (size / 2);
	Node* test2 = MSort(right, sizeRight);			//Calls sort on the newly split right half of the list
													//Size is (size - (size / 2)) to account for integer division truncating

	//
	//		SORTING STAGE
	//
	Node* resultHead = NULL;						//Initialize resultHead pointing to head of new, sorted list
	if (test1->Get_SID() < test2->Get_SID()) {
		resultHead = test1;							
		test1 = test1->Get_Pnext();
	}
	else {											//Initialize resultHead based on which lists' first element is smaller
		resultHead = test2;
		test2 = test2->Get_Pnext();
	}

	Node* nextElement = resultHead;					//Initialize nextElement pointer to traverse down and add to list using 4 cases:
	while (test1 != NULL || test2 != NULL) {

		if (test1 == NULL) {
			nextElement->Set_Pnext(test2);
			nextElement = nextElement->Get_Pnext();		//Case 1: If test1 is empty, add the rest of the elements of test2
			test2 = test2->Get_Pnext();
		}

		else if (test2 == NULL){
			nextElement->Set_Pnext(test1);
			nextElement = nextElement->Get_Pnext();		//Case 2: If test2 is empty, add the rest of the elements of test1
			test1 = test1->Get_Pnext();
		} 
		
		else if (test1->Get_SID() < test2->Get_SID()) {
			nextElement->Set_Pnext(test1);					//Case 3: If the next element of test1 is less than that of test2,
			nextElement = nextElement->Get_Pnext();			//add the next element of test1 and move test1 down its list
			test1 = test1->Get_Pnext();
		}

		else {
			nextElement->Set_Pnext(test2);
			nextElement = nextElement->Get_Pnext();			//Case 4: If the next element of test2 is less than that of test1,
			test2 = test2->Get_Pnext();						//add the next element of test2 and move test2 down its list
		}
	}
	return resultHead;										//Return resultHead, which points to the head of the newly sorted list
}


int main()
{
	// This array holds the list for binary search
	int L1[11];

	// This is the head pointer which holds the list for merge sort
	Node* L2 = NULL;

	//Mode = Function being Tested
	//Temp = Data being read in from user
	//Key = Search key for binary search
	int mode, temp, key; 

	cin >> mode >> key;

	// Takes input for binary search
	// For simplicity, we assume there are always 11 input integers that are 
	// unique and sorted in ascending order
	for (int i = 0; i < 11; i++) {
		cin >> L1[i];
	}

	
	// Takes input for merge sort
	// "L2" Stores the head of the linked list
	while (cin >> temp) {

		Node* next = new Node;
		next->Set_SID(temp);		//Initialize new node, setting SID to the read in value of temp

		next->Set_Pnext(L2);		//Add new node to the head of the linked list and re-assign head pointer(L2)
		L2 = next;
	}

	// -----------------------------------
	// Testing implementation.
	// -----------------------------------
	// 

	// Mode 0: test BSearch()
	if (mode == 0) {
		cout << BSearch(L1, 0, 10, key);			//Parameters: L1 is whole list, 0 is first element, 10 is last element, key is key
	}

	// Mode 1: test MSort()
	else if (mode == 1) {
		Node* counter = L2;
		int size = 1;
		while (counter->Get_Pnext() != NULL) {
			++size;
			counter = counter->Get_Pnext();		//Get the size of the list L2 by traversing until a NULL node is found
		}

		L2 = MSort(L2, size);					//Pass L2 and the newly found list size to recursive method
		Node* temp = L2;
		while (temp != NULL) {
			cout << temp->Get_SID();
			temp = temp->Get_Pnext();
		}
	}
	
	return 0;
}

