#include <iostream>
#include <string>
using namespace std;

// Define a Student struct to hold individual student information
struct Student
{
    string name;
    string ID;
    double CGPA;
};

// Define a Node struct to act as the building block for the linked list
struct Node
{
    Student data; // Data of type Student
    Node *next;   // Pointer to the next node in the list
};

// Declare the StudentList class to manage the linked list of students
class StudentList
{
private:
    Node *head;   // Pointer to the first node in the list
    int listSize; // Keeps track of the number of nodes in the list

public:
    StudentList() : head(nullptr), listSize(0) {}

    // Destructor deallocates all nodes to prevent memory leaks
    ~StudentList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    // insert function adds a new student record at a specified position
    void insert(int position, string name, string ID, double CGPA)
    {
        if (position < 0 || position > listSize)
        {
            cout << "Invalid position" << endl;
            return;
        }

        // Create a new node with the provided student information
        Node *newNode = new Node;  // Allocate new node
        newNode->data.name = name; // Set student name
        newNode->data.ID = ID;     // Set student ID
        newNode->data.CGPA = CGPA; // Set student CGPA
        newNode->next = nullptr;   // Initialize next pointer to nullptr

        if (position == 0)
        { // Insert at beginning
            newNode->next = head;
            head = newNode;
        }
        else
        { // Insert after the specified position
            Node *temp = head;
            for (int i = 1; i < position && temp != nullptr; i++)
            {
                temp = temp->next;
            }
            if (temp)
            {
                newNode->next = temp->next;
                temp->next = newNode;
            }
            else
            {
                // Handle error if position is out of bounds
                delete newNode; // Clean up memory
                cout << "Position out of bounds" << endl;
                return;
            }
        }
        listSize++;
        cout << "Added the student record to the list" << endl;
    }

    // find function searches for a student by name and returns its position
    int find(string name)
    {
        Node *temp = head;
        int position = 1;
        while (temp != nullptr)
        {
            if (temp->data.name == name)
            {
                return position;
            }
            temp = temp->next;
            position++;
        }
        return -1;
    }

    // deleteRecord function removes a student record from the list by name
    int deleteRecord(string name)
    {
        // Check if list is empty
        if (head == nullptr)
            return -1;

        // Special case: delete first node
        if (head->data.name == name)
        {
            Node *toDelete = head;
            head = head->next;
            delete toDelete;
            listSize--;
            return 0;
        }

        // General case: search and delete node
        Node *temp = head;
        while (temp->next != nullptr && temp->next->data.name != name)
        {
            temp = temp->next;
        }
        // If not found, return -1
        if (temp->next == nullptr)
        {
            return -1;
        }

        // Delete the found node
        Node *toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        listSize--;
        return 0;
    }

    // display function prints all student records in the list
    void display()
    {
        Node *temp = head;
        cout << "There are " << listSize << " records present in the list." << endl;
        int position = 1;
        while (temp != nullptr)
        {
            cout << position << ". " << temp->data.name << ", " << temp->data.ID << ", " << temp->data.CGPA << endl;
            temp = temp->next;
            position++;
        }
    }

    int size()
    {
        return listSize;
    }

    int isEmpty()
    {
        return head == nullptr ? 1 : 0;
    }
};

void menu()
{
    cout << "List Operations:" << endl;
    cout << "1. Add a student record to the list" << endl;
    cout << "2. Find a student record by name" << endl;
    cout << "3. Delete a student record from the list" << endl;
    cout << "4. Display the list" << endl;
    cout << "5. isEmpty" << endl;
    cout << "6. Size" << endl;
    cout << "7. Exit" << endl;
}

int main()
{
    StudentList sl;
    int choice;
    string name, ID;
    double CGPA;
    int position;

    while (true)
    {
        menu();
        cout << "Enter Menu Option: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter student name: ";
            cin >> name;
            cout << "Enter ID no: ";
            cin >> ID;
            cout << "Enter CGPA: ";
            cin >> CGPA;
            cout << "Enter index: ";
            cin >> position;
            sl.insert(position, name, ID, CGPA);
            break;
        case 2:
            cout << "Enter the Name of the student: ";
            cin >> name;
            position = sl.find(name);
            if (position != -1)
            {
                cout << "The student " << name << " is present at index " << position << endl;
            }
            else
            {
                cout << "Student not found." << endl;
            }
            break;
        case 3:
            cout << "Enter the Name of the student to be deleted from the list: ";
            cin >> name;
            if (sl.deleteRecord(name) == 0)
            {
                cout << "The student " << name << " is deleted from the list." << endl;
            }
            else
            {
                cout << "Student not found." << endl;
            }
            break;
        case 4:
            sl.display();
            break;
        case 5:
            cout << "The list is " << (sl.isEmpty() ? "empty." : "not empty.") << endl;
            break;
        case 6:
            cout << "The size of the list is " << sl.size() << endl;
            break;
        case 7:
            return 0;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
    return 0;
}
