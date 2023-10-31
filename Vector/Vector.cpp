//
// This file implements
// a vector class based on an arrays, pointers,
// and dynamic memory allocation.
//
#include <iostream>
using namespace std;


class MyVector {
public:
// Returns the size of the current vector.
	int vsize();

// Returns 1 if the current vector has no elements and 0 otherwise.
	int empty();

// Returns the element at the idx_th index of the vector or -1 if idx is invalid
	int at(int idx);

// Resizes the current vector into a vector of size n [Can be any positive integer]
	//If n < current size, keeps first n elements from previous vector
	//If n > current size, appends 0s to the end of previous vector
	void resize(int n);

// Adds a new element "x" to the end of the current vector [resizes]
	void push_back(int x);

// Removes the last element from the current vector
	void pop_back();
	
// Inserts a new element "x" as the idx_th element in the current vector.
// Does nothing if "idx" is outside the range of the current vector.
	void insert(int idx, int x);

// Removes the idx_th element
// Does nothing if the current vector is empty or if "idx" is outside the range of the current vector.
	void erase(int idx);

// Initializes pointer "p" to NULL and "size" to 0
	MyVector();

private:

	int* p; // Points that holds the "vector" [address of an array that holds the vector elements]

	int size; // This integer holds the size of the current vector

};

int MyVector::vsize() {
	return size; //Returns the value held in the vector's "size" variable
}

int MyVector::empty() {
	if (vsize() == 0) { //Uses vsize() function to test if the vector is empty:
		return 1;		//If size is 0[empty], return 1, if size is anything else[not empty], return 0
	}
	return 0;
}

int MyVector::at(int idx) {
	if (idx < 0 || idx >= size) return -1; //Tests if idx value is valid
	return p[idx];						//Returns -1 if invalid and returns value at that index if valid
}


void  MyVector::resize(int n) {
	int* q = new int[size];				//Initialize pointer q to hold integer array

	for (int i = 0; i < size; i++) {	//Fill array q with data from p
		q[i] = p[i];					
	}

	delete[] p;							//Release pointer p, link it to new array with new size
	p = new int[n];						

	for (int i = 0; i < size && i < n; i++) {
		p[i] = q[i];					//Fill p back up with data from q, until either size of n is reached or all
	}									//data from q is filled back into p
	
	
	if (n > size) {
		for (int i = size; i < n; i++) {
			p[i] = 0;					//If n is bigger than size, fill the rest of p with 0s
		}
	}
	size = n;							//Set new size equal to n
	delete[] q;
}

void MyVector::push_back(int x) {
	int *q = new int[size];				//Initialize pointer q to hold integer array
	for (int i = 0; i < size; i++) {
		q[i] = p[i];					//Fill array pointed to by q with data from p
	}
	delete[] p;
	size++;								
	p = new int[size];					//Release pointer p, link it to new array with new size
	for (int i = 0; i < size - 1; i++) {
		p[i] = q[i];					//Fill p with stored data from q up to second to last element
	}
	p[size - 1] = x;					//Set last element of p to int passed to function (x)
	delete[] q;
}

void MyVector::pop_back() {
	if (size == 0) return;				//Returns and does nothing is p is empty
	int* q = new int[size];				//Initialize pointer q to hold integer array
	for (int i = 0; i < size; i++) {
		q[i] = p[i];					//Fill array pointed to by q with data from p
	}
	delete[] p;
	p = new int[size - 1];				//Release pointer p, link it to new array with new size [One less]
	size--;
	for (int i = 0; i < size; i++) {
		p[i] = q[i];					//Fill array p with data from array q [Without last element]
	}
	delete[] q;
}

void MyVector::insert(int idx, int x) {
	if (idx < 0 || idx >= size) return;	//Tests if index passed is valid
	int* q = new int[size];				
	for (int i = 0; i < size; i++) {
		q[i] = p[i];					//Initialize pointer q to hold integer array, fill q w/ data from p
	}
	delete[] p;
	size++;
	p = new int[size];					//Increment size, create new array with new size pointed to by p
	for (int x = 0; x < idx; x++) {
		p[x] = q[x];					//Fill p with data from q up to given index
	}
	p[idx] = x;							//Set data of p at index given to the value given to function
	for (int i = idx + 1; i < size; ++i) {
		p[i] = q[i - 1];				//Fill the rest of p with the remaining data in q [Pushing data one index back]
	}
	delete[] q;
}

void MyVector::erase(int idx) {
	if (idx < 0 || idx >= size || size == 0) return; //Tests if index is valid, if not it returns and does nothing
	int* q = new int[size];
	for (int i = 0; i < size; i++) {
		q[i] = p[i];						//Initialize pointer q to hold integer array, fill q w/ data from p
	}
	delete[] p;
	size--;
	p = new int[size];						//Decrement size, create new array with new size pointed to by p
	for (int i = 0; i < size; i++) {
		if (i < idx) {
			p[i] = q[i];					//Fills array pointed to by p:
		}									//For data before erase index given, fill with mirrored data from q
		else {								//For data after erase index given, fill with next index from q [Thus skipping index passed to function]
			p[i] = q[i + 1];
		}
	}
	delete[] q;
}

MyVector::MyVector() {
	p = NULL;		//Constructor initializes p to NULL and size to 0
	size = 0;
}



















// The main function is used to test implmentation and various actions

int main()
{
	MyVector x;
	int mode;
	int new_size, idx, data;
	int temp;
	cin >> mode; // This decides which function to test

	cin >> new_size >> idx >> data;

	// Mode 0: test push_back(), vsize() and at()
	if (mode == 0) {
		while (cin >> temp) {
			x.push_back(temp);
		}
		cout << x.vsize() << '\n';
		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}

	// Mode 1: test resize()
	else if (mode == 1)
	{
		while (cin >> temp) {
			x.push_back(temp);
		}
		x.resize(new_size);
		cout << x.vsize() << '\n';
		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}


	// Mode 2: test pop_back()
	else if (mode == 2) {
		while (cin >> temp) {
			x.push_back(temp);
		}
		x.pop_back();
		cout << x.vsize() << '\n';
		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}


	// Mode 3: test insert()
	else if (mode == 3) {
		while (cin >> temp) {
			x.push_back(temp);
		}
		x.insert(idx, data);
		cout << x.vsize() << '\n';
		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}


	// Mode 4: test erase()
	else if (mode == 4) {
		while (cin >> temp) {
			x.push_back(temp);
		}
		x.erase(idx);
		cout << x.vsize() << '\n';
		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	else {
		cout << "Wrong Mode Input!";
	}
	return 0;
}