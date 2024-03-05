#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Define a struct to represent a student record
struct Student {
    string id;
    string name;
    string dob; // Date of birth
    float cgpa;
};

// Global queue settings
const int MAX = 100; // Maximum number of elements in the queue
Student queue[MAX];
int front = -1;
int rear = -1;

// Function to check if the queue is full
bool isFull() {
    return (front == 0 && rear == MAX - 1) || (rear == (front - 1) % (MAX - 1));
}

// Function to check if the queue is empty
bool isEmpty() {
    return front == -1;
}

// Function to add a student record to the queue
void enqueue(Student element) {
    if (isFull()) {
        cout << "Queue is full. Cannot enqueue.\n";
        return;
    } else {
        if (front == -1) // First element being added
            front = rear = 0;
        else if (rear == MAX - 1 && front != 0)
            rear = 0; // Wrap around
        else
            rear++;

        queue[rear] = element;
    }
}

// Function to remove a student record from the queue
Student dequeue() {
    Student element;
    if (isEmpty()) {
        cout << "Queue is empty. Cannot dequeue.\n";
        return element; // Return empty student if queue is empty
    }

    element = queue[front];
    if (front == rear) {
        // Only one element was in the queue, now it will be empty
        front = -1;
        rear = -1;
    } else if (front == MAX - 1)
        front = 0; // Wrap around
    else
        front++;

    return element;
}

// Function to read student records from file and enqueue them
void readStudentsFromFile(const char* filename) {
    ifstream inFile(filename);
    string id, name, dob;
    float cgpa;

    while (inFile >> id >> name >> dob >> cgpa) {
        Student s = {id, name, dob, cgpa};
        enqueue(s);
    }

    inFile.close();
}

// Function to write the dequeued students to a file and screen, and display names with CGPA < 9
void processQueue(const char* outFilename) {
    ofstream outFile(outFilename);
    while (!isEmpty()) {
        Student s = dequeue();
        cout << s.id << " " << s.name << " " << s.dob << " " << s.cgpa << endl;
        outFile << s.id << " " << s.name << " " << s.dob << " " << s.cgpa << endl;

        if (s.cgpa < 9.0) {
            cout << "NAME: " << s.name << endl;
        }
    }

    outFile.close();
}

int main() {
    readStudentsFromFile("studentin.dat");
    processQueue("studentout.dat");

    return 0;
}
