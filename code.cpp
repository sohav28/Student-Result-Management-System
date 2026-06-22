#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Base Class: Person (Demonstrating Inheritance)
class Person {
protected:
    string name;
public:
    void setPersonDetails() {
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
    }
    void showPersonDetails() const {
        cout << "Name: " << name << endl;
    }
};

// Derived Class: Student (Inherits from Person)
class Student : public Person {
private:
    int rollNumber;
    float dsa_marks, oop_marks, dbms_marks;
    float totalMarks;
    float percentage;
    char grade;

    void calculateGrade() {
        totalMarks = dsa_marks + oop_marks + dbms_marks;
        percentage = totalMarks / 3.0;
        if (percentage >= 90) grade = 'A';
        else if (percentage >= 75) grade = 'B';
        else if (percentage >= 50) grade = 'C';
        else if (percentage >= 35) grade = 'D';
        else grade = 'F';
    }

public:
    void acceptData() {
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        setPersonDetails(); // Calling base class method
        cout << "Enter Marks for DSA: ";
        cin >> dsa_marks;
        cout << "Enter Marks for OOP: ";
        cin >> oop_marks;
        cout << "Enter Marks for DBMS: ";
        cin >> dbms_marks;
        calculateGrade();
    }

    void displayData() const {
        cout << "\n====================================" << endl;
        cout << "Roll Number   : " << rollNumber << endl;
        showPersonDetails(); // Calling base class method
        cout << "DSA Marks     : " << dsa_marks << endl;
        cout << "OOP Marks     : " << oop_marks << endl;
        cout << "DBMS Marks    : " << dbms_marks << endl;
        cout << "Total Marks   : " << totalMarks << "/300" << endl;
        cout << "Percentage    : " << fixed << setprecision(2) << percentage << "%" << endl;
        cout << "Grade         : " << grade << endl;
        cout << "====================================" << endl;
    }

    // Tabular display ke liye helpers
    void displayRow() const {
        cout << left << setw(12) << rollNumber 
             << setw(20) << name 
             << setw(8) << dsa_marks 
             << setw(8) << oop_marks 
             << setw(8) << dbms_marks 
             << setw(10) << fixed << setprecision(2) << percentage 
             << setw(5) << grade << endl;
    }

    int getRollNumber() const {
        return rollNumber;
    }
};

// File Handling Functions
void addStudentRecord() {
    Student stud;
    ofstream outFile("records.dat", ios::binary | ios::app);
    
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    stud.acceptData();
    outFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
    outFile.close();
    cout << "\nStudent record added successfully!" << endl;
}

void displayAllRecords() {
    Student stud;
    ifstream inFile("records.dat", ios::binary);
    
    if (!inFile) {
        cout << "No records found! (File does not exist)" << endl;
        return;
    }
    
    cout << "\n------------------------------------------------------------------------\n";
    cout << left << setw(12) << "Roll No" << setw(20) << "Name" << setw(8) << "DSA" 
         << setw(8) << "OOP" << setw(8) << "DBMS" << setw(10) << "Percentage" << setw(5) << "Grade" << endl;
    cout << "------------------------------------------------------------------------\n";
    
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        stud.displayRow();
    }
    inFile.close();
}

void searchStudentRecord(int rollNo) {
    Student stud;
    ifstream inFile("records.dat", ios::binary);
    bool found = false;
    
    if (!inFile) {
        cout << "No records found!" << endl;
        return;
    }
    
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.getRollNumber() == rollNo) {
            stud.displayData();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        cout << "\nRecord not found for Roll Number: " << rollNo << endl;
    }
}

void updateStudentRecord(int rollNo) {
    Student stud;
    fstream file("records.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    
    if (!file) {
        cout << "No records found!" << endl;
        return;
    }
    
    while (file.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.getRollNumber() == rollNo) {
            stud.displayData();
            cout << "\nEnter New Details:" << endl;
            stud.acceptData();
            
            // Move file pointer back to override this specific object
            int pos = (-1) * static_cast<int>(sizeof(Student));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&stud), sizeof(Student));
            
            cout << "\nRecord updated successfully!" << endl;
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "\nRecord not found!" << endl;
}

void deleteStudentRecord(int rollNo) {
    Student stud;
    ifstream inFile("records.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary); // Temporary file
    bool found = false;
    
    if (!inFile) {
        cout << "No records found!" << endl;
        return;
    }
    
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.getRollNumber() == rollNo) {
            found = true;
            continue; // Skip writing the deleted record to the temp file
        }
        outFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
    }
    
    inFile.close();
    outFile.close();
    
    remove("records.dat");          // Remove old file
    rename("temp.dat", "records.dat"); // Rename temp file to original
    
    if (found) cout << "\nRecord deleted successfully!" << endl;
    else cout << "\nRecord not found!" << endl;
}

// Driver Code
int main() {
    int choice;
    int rollNo;
    
    do {
        cout << "\n====== STUDENT RESULT MANAGEMENT SYSTEM ======" << endl;
        cout << "1. Create Student Record" << endl;
        cout << "2. Display All Students Records" << endl;
        cout << "3. Search Student Record" << endl;
        cout << "4. Update Student Record" << endl;
        cout << "5. Delete Student Record" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;
        
        switch (choice) {
            case 1: addStudentRecord(); break;
            case 2: displayAllRecords(); break;
            case 3: 
                cout << "Enter Roll Number to Search: ";
                cin >> rollNo;
                searchStudentRecord(rollNo); 
                break;
            case 4: 
                cout << "Enter Roll Number to Update: ";
                cin >> rollNo;
                updateStudentRecord(rollNo); 
                break;
            case 5: 
                cout << "Enter Roll Number to Delete: ";
                cin >> rollNo;
                deleteStudentRecord(rollNo); 
                break;
            case 6: cout << "Exiting Program. Good Bye!" << endl; break;
            default: cout << "Invalid choice! Please enter a valid option." << endl;
        }
    } while (choice != 6);
    
    return 0;
}