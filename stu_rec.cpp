#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Structure to hold student information
struct Student {
    int rollNumber;
    string name;
    int age;
    string grade;
};

// Function prototypes
void addStudent();
void displayAllStudents();
void searchStudent(int rollNumber);
void updateStudent(int rollNumber);
void deleteStudent(int rollNumber);

int main() {
    int choice;
    do {
        cout << "\n***** Student Record Management System *****" << endl;
        cout << "1. Add Student Record" << endl;
        cout << "2. Display All Records" << endl;
        cout << "3. Search Record" << endl;
        cout << "4. Update Record" << endl;
        cout << "5. Delete Record" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3: {
                int rollNumber;
                cout << "Enter Roll Number to Search: ";
                cin >> rollNumber;
                searchStudent(rollNumber);
                break;
            }
            case 4: {
                int rollNumber;
                cout << "Enter Roll Number to Update: ";
                cin >> rollNumber;
                updateStudent(rollNumber);
                break;
            }
            case 5: {
                int rollNumber;
                cout << "Enter Roll Number to Delete: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;
            }
            case 6:
                cout << "Exiting Program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a number from 1 to 6." << endl;
        }
    } while (choice != 6);

    return 0;
}

// Function to add a new student record
void addStudent() {
    ofstream file("student_records.txt", ios::app);
    if (!file) {
        cerr << "Error: Unable to open file!" << endl;
        return;
    }

    Student student;
    cout << "\nEnter Student Details:" << endl;
    cout << "Roll Number: ";
    cin >> student.rollNumber;
    cout << "Name: ";
    cin.ignore(); // Ignore newline left by previous cin
    getline(cin, student.name);
    cout << "Age: ";
    cin >> student.age;
    cout << "Grade: ";
    cin >> student.grade;

    file << student.rollNumber << "," << student.name << "," << student.age << "," << student.grade << endl;
    file.close();

    cout << "Student Record added successfully!" << endl;
}

// Function to display all student records
void displayAllStudents() {
    ifstream file("student_records.txt");
    if (!file) {
        cerr << "Error: Unable to open file!" << endl;
        return;
    }

    cout << "\n***** List of All Students *****" << endl;
    cout << setw(15) << "Roll Number" << setw(20) << "Name" << setw(10) << "Age" << setw(10) << "Grade" << endl;
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;

    Student student;
    char comma;
    while (file >> student.rollNumber >> comma >> ws && getline(file, student.name, ',') && file >> student.age >> comma && getline(file, student.grade)) {
        cout << setw(15) << student.rollNumber << setw(20) << student.name << setw(10) << student.age << setw(10) << student.grade << endl;
    }

    file.close();
}

// Function to search for a student record by roll number
void searchStudent(int rollNumber) {
    ifstream file("student_records.txt");
    if (!file) {
        cerr << "Error: Unable to open file!" << endl;
        return;
    }

    Student student;
    char comma;
    bool found = false;
    while (file >> student.rollNumber >> comma >> ws && getline(file, student.name, ',') && file >> student.age >> comma && getline(file, student.grade)) {
        if (student.rollNumber == rollNumber) {
            found = true;
            cout << "\n***** Student Record Found *****" << endl;
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Age: " << student.age << endl;
            cout << "Grade: " << student.grade << endl;
            break;
        }
    }

    if (!found) {
        cout << "Student with Roll Number " << rollNumber << " not found." << endl;
    }

    file.close();
}

// Function to update a student record
void updateStudent(int rollNumber) {
    ifstream file("student_records.txt");
    if (!file) {
        cerr << "Error: Unable to open file!" << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "Error: Unable to open temporary file!" << endl;
        file.close();
        return;
    }

    Student student;
    char comma;
    bool found = false;
    while (file >> student.rollNumber >> comma >> ws && getline(file, student.name, ',') && file >> student.age >> comma && getline(file, student.grade)) {
        if (student.rollNumber == rollNumber) {
            found = true;
            cout << "\nEnter New Details for Roll Number " << rollNumber << ":" << endl;
            cout << "Name: ";
            cin.ignore(); // Ignore newline left by previous cin
            getline(cin, student.name);
            cout << "Age: ";
            cin >> student.age;
            cout << "Grade: ";
            cin >> student.grade;
        }
        tempFile << student.rollNumber << "," << student.name << "," << student.age << "," << student.grade << endl;
    }

    file.close();
    tempFile.close();

    remove("student_records.txt");
    rename("temp.txt", "student_records.txt");

    if (found) {
        cout << "Student Record updated successfully!" << endl;
    } else {
        cout << "Student with Roll Number " << rollNumber << " not found." << endl;
    }
}

// Function to delete a student record
void deleteStudent(int rollNumber) {
    ifstream file("student_records.txt");
    if (!file) {
        cerr << "Error: Unable to open file!" << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "Error: Unable to open temporary file!" << endl;
        file.close();
        return;
    }

    Student student;
    char comma;
    bool found = false;
    while (file >> student.rollNumber >> comma >> ws && getline(file, student.name, ',') && file >> student.age >> comma && getline(file, student.grade)) {
        if (student.rollNumber == rollNumber) {
            found = true;
            cout << "\nStudent Record with Roll Number " << rollNumber << " deleted." << endl;
            continue; // Skip writing this record to temp file
        }
        tempFile << student.rollNumber << "," << student.name << "," << student.age << "," << student.grade << endl;
    }

    file.close();
    tempFile.close();

    remove("student_records.txt");
    rename("temp.txt", "student_records.txt");

    if (!found) {
        cout << "Student with Roll Number " << rollNumber << " not found." << endl;
    }
}
