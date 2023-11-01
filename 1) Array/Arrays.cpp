//
// 
// This file contains an implementation of a Student and University class. It served
// as a basic introduction to C++ programming principles with a focus on the first
// Data Structure we learned: arrays.
//
//


#include <iostream>

using namespace std;

/*
Student Class: Contains basic encapsulation (get/set) methods for use
in University class
*/
class Student {
public:
	void set_SID(int x); // Assigns x to SID
	void prt_SID(); // Prints SID
	void set_GPA(float y);// Assigns y to GPA
	void prt_GPA(); // Prints GPA
	void reset(); // Resets SID and GPA to -1
	float get_GPA(); // Returns GPA
	Student(); // Constructor -> Initializes
				// both SID and GPA to -1
private:
	int SID; // It holds a student's ID
	float GPA; // It holds a student's GPA
};

void Student::set_SID(int x) {
	SID = x;
}

void Student::prt_SID() {
	cout << SID;
}

void Student::set_GPA(float y) {
	GPA = y;
}

void Student::prt_GPA() {
	cout << GPA;
}

void Student::reset() {
	GPA = -1; 
	SID = -1;
}

float Student::get_GPA() {
	return GPA;
}

//Constructs a new student object with initialize values of SID as -1 and GPA as -1
Student::Student() { 
	GPA = -1; 
	SID = -1;
}

class University {
public:
//Fills Sooner array with Students in x
	void set_Stu(Student x[]);

// Prints the mean GPA of the five student in Sooner array
	float GPA_Mean(); 

// Prints the max GPA of these five students.
	float GPA_Max(); 

// Prints the min GPA of these five students.
	float GPA_Min(); 

// Constructor -> Initializes all student SID and GPA to -1
	University(); 

private:
	Student Sooner[5]; // Holds the records of five students
};

void University::set_Stu(Student x[]) {
//Calculates Size of Sooner Array
	int size = sizeof(Sooner) / sizeof(Sooner[0]);

//Fills Sooner array with values in array x
	for (int i = 0; i < size; i++) {
		Sooner[i] = x[i];
	}
}

float University::GPA_Mean() {
	int size = sizeof(Sooner) / sizeof(Sooner[0]);
	float sum = 0.0;

//Finds total GPA sum by stepping through each array element
	for (int i = 0; i < size; i++) {
		sum += Sooner[i].get_GPA();
	}

//Returns the mean by dividing the GPA total by the number of students
	return sum / size;
}

float University::GPA_Max() {
	float max = Sooner[0].get_GPA();
	int size = sizeof(Sooner) / sizeof(Sooner[0]);

//Finds maximum by stepping through each array element
	for (int i = 0; i < size; i++) {
		if (Sooner[i].get_GPA() > max) {
			max = Sooner[i].get_GPA();
		}
	}

//Returns max GPA found
	return max;
}

float University::GPA_Min() {
	float min = Sooner[0].get_GPA();
	int size = sizeof(Sooner) / sizeof(Sooner[0]);

//Finds minimum by stepping through each array element
	for (int i = 0; i < size; i++) {
		if (Sooner[i].get_GPA() < min) {
			min = Sooner[i].get_GPA();
		}
	}

//Returns minimum GPA found
	return min;
}


//Creates new University object by clearing out(resetting) every Student in Sooner array
University::University() {
	int size = sizeof(Sooner) / sizeof(Sooner[0]);
	for (int i = 0; i < size; i++) {
		Sooner[i].reset();
	}
}


// === End of Task 2 ====
	int main()
	{
		Student x[5];
		University OU;
		int sid;
		float gpa;


		// This tests constructor function,
		// print function and header files.
		for (int i = 0; i < 5; i++) {
			x[i].prt_SID(); cout << ' ';
			x[i].prt_GPA(); cout << endl;
		}
		
		
		//Uses a for loop to fill the array x with input in the described format
		for (int i = 0; i < 5; i++) {
			cin >> sid >> gpa;
			x[i].set_SID(sid);
			x[i].set_GPA(gpa);
		}
		

		// This tests set function
		for (int i = 0; i < 5; i++) {
			x[i].prt_SID(); cout << ' ';
			x[i].prt_GPA(); cout << endl;
		}
		

		// This tests your University class.
		OU.set_Stu(x);
		OU.GPA_Mean(); cout << ' ';
		OU.GPA_Max(); cout << ' ';
		OU.GPA_Min(); cout << endl;
		

		// This tests reset function.
		for (int i = 0; i < 5; i++) {
			x[i].reset();
			x[i].prt_SID(); cout << ' ';
			x[i].prt_GPA(); cout << endl;
		}


		return 0;
	}