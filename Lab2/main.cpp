#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int MAX_SIZE = 100; // Maximum size of the queue

// Define a structure to hold student information
struct Student {
    string id;
    string name;
    string dob;
    float cgpa;
};

// Define a class to manage the queue of students
class StudentQueue {
private:
    Student students[MAX_SIZE]; // Array of students to serve as the queue
    int front, rear, size; // Indices for the front and rear of the queue, and the current size
public:
    // Constructor initializes the queue properties
    StudentQueue() : front(0), rear(-1), size(0) {}

    // Check if the queue is full
    bool isFull() const {
        return size == MAX_SIZE;
    }
    // Check if the queue is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Add a student to the rear of the queue
    void enqueue(const Student& student) {
        if (isFull()) {
            cout << "Queue is full" << endl;
            return;
        }
        rear = (rear + 1) % MAX_SIZE; // Increment rear index circularly
        students[rear] = student; // Add the student to the queue
        size++; // Increment the queue size
    }

    // Remove and return a student from the front of the queue
    Student dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            exit(1); // Exit the program for simplicity
        }
        Student temp = students[front]; // Store the front student
        front = (front + 1) % MAX_SIZE; // Increment front index circularly
        size--;
        return temp;
    }
};

// Read student records from a file and add them to the queue
void readFromFileAndEnqueue(StudentQueue &queue, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return;
    }

    Student student;
    // Read student data and enqueue
    while (file >> student.id >> student.name >> student.dob >> student.cgpa) {
        queue.enqueue(student);
    }

    file.close();
}

// Dequeue students and write their information to a file, also store in a vector for later use
void dequeueAndWriteToFile(StudentQueue &queue, const char* filename, vector<Student>& tempStorage) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return;
    }

    // Dequeue students and write to file
    while (!queue.isEmpty()) {
        Student student = queue.dequeue();
        tempStorage.push_back(student); // Store student for later use
        file << student.id << " " << student.name << " " << student.dob << " " << student.cgpa << endl;
        cout << student.id << " " << student.name << " " << student.dob << " " << student.cgpa << endl;
    }

    file.close();
}

// Display names of students with CGPA less than a specified value
void displayStudentsBelowCGPA(const vector<Student>& students, float cgpa) {
    cout << "Names of students with CGPA less than 9:" << endl;
    for (const auto& student : students) {
        if (student.cgpa < cgpa) {
            cout << student.name << endl;
        }
    }
}

int main() {
    StudentQueue queue; // Create a queue instance
    vector<Student> tempStorage; // Create a vector to store students after dequeueing

    readFromFileAndEnqueue(queue, "studentin.dat");
    dequeueAndWriteToFile(queue, "studentout.dat", tempStorage);
    displayStudentsBelowCGPA(tempStorage, 9.0);

    return 0;
}
