#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int MAX_SIZE = 100;

struct Student {
    string id;
    string name;
    string dob;
    float cgpa;
};

class StudentQueue {
private:
    Student students[MAX_SIZE];
    int front, rear, size;
public:
    StudentQueue() : front(0), rear(-1), size(0) {}

    bool isFull() const {
        return size == MAX_SIZE;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void enqueue(const Student& student) {
        if (isFull()) {
            cout << "Queue is full" << endl;
            return;
        }
        rear = (rear + 1) % MAX_SIZE;
        students[rear] = student;
        size++;
    }

    Student dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            exit(1); // Exit the program for simplicity
        }
        Student temp = students[front];
        front = (front + 1) % MAX_SIZE;
        size--;
        return temp;
    }

    // This function is no longer needed
    // void displayStudentsBelowCGPA(float cgpa);
};

void readFromFileAndEnqueue(StudentQueue &queue, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return;
    }

    Student student;
    while (file >> student.id >> student.name >> student.dob >> student.cgpa) {
        queue.enqueue(student);
    }

    file.close();
}

void dequeueAndWriteToFile(StudentQueue &queue, const char* filename, vector<Student>& tempStorage) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return;
    }

    while (!queue.isEmpty()) {
        Student student = queue.dequeue();
        tempStorage.push_back(student); // Store student for later use
        file << student.id << " " << student.name << " " << student.dob << " " << student.cgpa << endl;
        cout << student.id << " " << student.name << " " << student.dob << " " << student.cgpa << endl;
    }

    file.close();
}

void displayStudentsBelowCGPA(const vector<Student>& students, float cgpa) {
    cout << "Names of students with CGPA less than 9:" << endl;
    for (const auto& student : students) {
        if (student.cgpa < cgpa) {
            cout << student.name << endl;
        }
    }
}

int main() {
    StudentQueue queue;
    vector<Student> tempStorage;

    readFromFileAndEnqueue(queue, "studentin.dat");
    dequeueAndWriteToFile(queue, "studentout.dat", tempStorage);
    displayStudentsBelowCGPA(tempStorage, 9.0);

    return 0;
}
