//
// ========================================
// Assignment 1: C++ Programming
// ========================================
//
// In this assignment, we will implement
// a Student class and a University class.
//
// The Student class has two private member
// variables and five member functions (not
// counting the constructor). Their designs
// are explained in the template below.
//
// The University class has one private member
// variable and four member functions. Their
// designs are explained in the template below.
//
// In the template, you will see two types of
// sections: "Task" and "Test". A "Task" section
// is where you need to implement something,
// and a "Test" section is testing your implementation
// (you don't need to do anything in this section).
//
// For all print functions, only print the value
// and do not add any additional character
// such as space or change line. For example,
// if you are asked to print the value of x,
// write "cout << x;" instead of "cout << x << endl;"
//
//
// ======= Task 1 =======
// Complete the header files

#include <iostream>

using namespace std;

// === End of Task 1 ====
// ======= Task 2 =======
// Design and implement all member functions of the
// following two classes: Student and University.
// All member functions must be implemented outside
// the class definitions.
//
class Student {
public:
	void set_SID(int x); // It assigns x to SID.
	void prt_SID(); // It prints SID.
	void set_GPA(float y);// It assigns y to GPA.
	void prt_GPA(); // It prints GPA.
	void reset(); // It resets SID and GPA to -1.
	float get_GPA(); // It returns GPA.
	Student(); // Constructor. It initializes
	// both SID and GPA to -1.
private:
	int SID; // It holds a student's ID.
	float GPA; // It holds a student's GPA.
};

void Student::set_SID(int x) {
	SID = x; //Assigns Student's SID to integer argument passed "x"
}

void Student::prt_SID() {
	cout << SID; //Prints out Student's SID to Console
}

void Student::set_GPA(float y) {
	GPA = y; //Assigns Student's GPA to float value passed "y"
}

void Student::prt_GPA() {
	cout << GPA; //Prints out Student's GPA to Console
}

void Student::reset() {
	GPA = -1; //Resets Student's GPA to -1
	SID = -1; //Resets Student's SID to -1
}

float Student::get_GPA() {
	return GPA; //Returns the Student's GPA value (encapsulation)
}

Student::Student() { //Constructs a new student object with initialize values of SID as -1 and GPA as -1
	GPA = -1; 
	SID = -1;
}

class University {
public:
	void set_Stu(Student x[]);// It assigns x to Sooner.
	float GPA_Mean(); // It prints the mean GPA of the five students held
						// by Sooner[5].
		float GPA_Max(); // It prints the max GPA of these five students.
	float GPA_Min(); // It prints the min GPA of these five students.
	University(); // Constructor. Initialize all student SID and GPA
				// to - 1.
		// Note: The above three functions must be implemented by yourself
		// and not called from existing mean, max or min functions.
private:
	Student Sooner[5]; // It holds the records of five students.
};

void University::set_Stu(Student x[]) {
	//Calculates Size of Sooner Array
	int size = sizeof(Sooner) / sizeof(Sooner[0]);
	//Steps through array to fill Sooner array with values contained in array x
	for (int i = 0; i < size; i++) {
		Sooner[i] = x[i];
	}
}

float University::GPA_Mean() {
	//Calculates Size of Sooner Array
	int size = sizeof(Sooner) / sizeof(Sooner[0]);
	float sum = 0.0;
	//Steps through Sooner array accumulating a sum of every student's GPA
	for (int i = 0; i < size; i++) {
		sum += Sooner[i].get_GPA();
	}
	//Returns the mean by dividing the GPA total by the number of students
	cout << (sum / size);
	return sum / size;
}

float University::GPA_Max() {
	//Initializes a "max" variable to store the max GPA
	float max = Sooner[0].get_GPA();
	//Calculates Size of Sooner Array
	int size = sizeof(Sooner) / sizeof(Sooner[0]);
	//Steps through array and checks every Student's GPA; If GPA is higher than max, assign Student's GPA to max
	for (int i = 0; i < size; i++) {
		if (Sooner[i].get_GPA() > max) {
			max = Sooner[i].get_GPA();
		}
	}
	//Returns max GPA found
	cout << max;
	return max;
}

float University::GPA_Min() {
	//Initializes a "min" variable to store the minimum GPA
	float min = Sooner[0].get_GPA();
	//Calculates Size of Sooner Array
	int size = sizeof(Sooner) / sizeof(Sooner[0]);
	//Steps through array and checks every Student's GPA; If GPA is lower than min, assign Student's GPA to min
	for (int i = 0; i < size; i++) {
		if (Sooner[i].get_GPA() < min) {
			min = Sooner[i].get_GPA();
		}
	}
	//Returns minimum GPA found
	cout << min;
	return min;
}

University::University() { //Creates new University object by clearing out(resetting) Sooner array
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
		// The following two variables can be used
		// to store inputs, but you don't have to use
		int sid;
		float gpa;
		// ======= Test 1 =======
		// This tests your constructor function,
		// print function and header files.
		for (int i = 0; i < 5; i++) {
			x[i].prt_SID(); cout << ' ';
			x[i].prt_GPA(); cout << endl;
		}
		// === End of Test 1 ====
		// ======= Task 3 =======
		// Write a program that takes the SID
		// and GPA of five students as input
		// and assigne them to x[5].
		//
		// Formt of the inputs should be (with space)
		// SID1 GPA1 SID2 GPA2 SID3 GPA3 SID4 GPA4 SID5 GPA5
		
		
		//Uses a for loop to fill the array x with input in the described format
		for (int i = 0; i < 5; i++) {
			cin >> sid >> gpa;
			x[i].set_SID(sid);
			x[i].set_GPA(gpa);
		}
		

		// === End of Task 3 ====
		// ======= Test 2 =======
		// This tests your set function
		for (int i = 0; i < 5; i++) {
			x[i].prt_SID(); cout << ' ';
			x[i].prt_GPA(); cout << endl;
		}
		// === End of Test 2 ====
		// ======= Test 3 =======
		// This tests your University class.
		OU.set_Stu(x);
		OU.GPA_Mean(); cout << ' ';
		OU.GPA_Max(); cout << ' ';
		OU.GPA_Min(); cout << endl;
		// === End of Test 3 ====
		// ======= Test 4 =======
		// This tests your reset function.
		for (int i = 0; i < 5; i++) {
			x[i].reset();
			x[i].prt_SID(); cout << ' ';
			x[i].prt_GPA(); cout << endl;
		}
		// === End of Test 4 ====
		return 0;
	}