#include <iostream> 
#include <fstream>  
#include <string>   
using namespace std;

const int MAX = 100; // Define the maximum size of the stack
int top = -1; // Initialize the top of the stack to -1, indicating that the stack is empty

// Define a structure for storing student information
struct Student {
    string id;   
    string name; 
    string dob;  
    double cgpa;
} stack[MAX]; // Declare an array of 'Student' structures to serve as the stack, with a maximum size of 'MAX'

// Function to push a student record onto the stack
bool push(const Student& student) {
    if (top >= MAX - 1) { 
        cout << "Stack Overflow\n";
        return false; 
    } else {
        stack[++top] = student; // Increment 'top' and insert the student record at the new top position
        return true; // Return true indicating push operation succeeded
    }
}

// Function to pop a student record from the stack
Student pop() {
    if (top < 0) { 
        cout << "Stack Underflow\n"; 
        return {}; // Return an empty 'Student' structure
    } else {
        return stack[top--]; // Return the top student record and decrement 'top'
    }
}


bool isEmpty() {
    return top < 0;
}

// Function to read student records from a file and push them onto the stack
void readAndPushRecords() {
    ifstream inFile("studentin.dat"); // Open the input file "studentin.dat" for reading student records
    
    Student student; // Declare a 'Student' structure to hold the data for each student
    
    // Read data from 'inFile' into the 'student' structure's members (id, name, dob, cgpa)
    // Continue reading as long as there is data to read
    while (inFile >> student.id >> student.name >> student.dob >> student.cgpa) {
        push(student); // Push each student record read from the file onto the stack
    }
    
    inFile.close(); // Close the input file stream
}

// Function to pop student records from the stack and write them to an output file
void popAndWriteRecords() {
    ofstream outFile("studentout.dat"); // Open the output file "studentout.dat" for writing student records
    
    // Pop each student record from the stack and write to the output file
    while (!isEmpty()) {
        Student student = pop(); // Pop the top student record from the stack
        cout << student.id << " " << student.name << " " << student.dob << " " << student.cgpa << endl; 
        outFile << student.id << " " << student.name << " " << student.dob << " " << student.cgpa << endl;
    }
    
    outFile.close(); // Close the output file stream
}

int main() {
    readAndPushRecords(); 
    popAndWriteRecords();
    return 0; 
}
