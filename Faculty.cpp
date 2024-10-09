#include <iostream>
#include <fstream>
#include <string>
#include "Faculty.h"

using namespace std;

Faculty::Faculty() {
    head = nullptr;
}

void Faculty::createFaculty(const string& name, const string& initial, const string& designation, const string& email, const string& phoneNumber) {
    FacultyNode* newNode = new FacultyNode;
    newNode->name = name;
    newNode->initial = initial;
    newNode->designation = designation;
    newNode->email = email;
    newNode->phoneNumber = phoneNumber;
    newNode->availableCredits = 11.0;
    newNode->numCourses = 0;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        FacultyNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void Faculty::readFacultyList(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Failed to open the file." << endl;
        return;
    }

    string name, initial, designation, email, phoneNumber;
    while (getline(inputFile, name)) {
        getline(inputFile, initial);
        getline(inputFile, designation);
        getline(inputFile, email);
        getline(inputFile, phoneNumber);

        createFaculty(name, initial, designation, email, phoneNumber);
    }

    inputFile.close();
}

void Faculty::readFaculty(const string& name) {
    if (head == nullptr) {
        cout << "No faculties in the list." << endl;
        return;
    }

    FacultyNode* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            cout << "Name: " << current->name << endl;
            cout << "Initial: " << current->initial << endl;
            cout << "Designation: " << current->designation << endl;
            cout << "Email: " << current->email << endl;
            cout << "Phone Number: " << current->phoneNumber << endl;
            cout << "Available Credits: " << current->availableCredits << endl;
            cout << endl;
            return;
        }
        current = current->next;
    }

    cout << "Faculty not found." << endl;
}

void Faculty::updateFaculty(const string& name, const string& newPhoneNumber) {
    if (head == nullptr) {
        cout << "No faculties in the list." << endl;
        return;
    }

    FacultyNode* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            current->phoneNumber = newPhoneNumber;
            cout << "Phone Number updated successfully." << endl;
            return;
        }
        current = current->next;
    }

    cout << "Faculty not found." << endl;
}

void Faculty::deleteFaculty(const string& name) {
    if (head == nullptr) {
        cout << "No faculties in the list." << endl;
        return;
    }

    if (head->name == name) {
        FacultyNode* temp = head;
        head = head->next;
        delete temp;
        cout << "Faculty deleted successfully." << endl;
        return;
    }

    FacultyNode* current = head;
    while (current->next != nullptr) {
        if (current->next->name == name) {
            FacultyNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Faculty deleted successfully." << endl;
            return;
        }
        current = current->next;
    }

    cout << "Faculty not found." << endl;
}

void Faculty::printAllFaculties() {
    if (head == nullptr) {
        cout << "No faculties in the list." << endl;
        return;
    }

    FacultyNode* current = head;
    while (current != nullptr) {
        cout << "Name: " << current->name << endl;
        cout << "Initial: " << current->initial << endl;
        cout << "Designation: " << current->designation << endl;
        cout << "Email: " << current->email << endl;
        cout << "Phone Number: " << current->phoneNumber << endl;
        cout << "Available Credits: " << current->availableCredits << endl;
        current = current->next;
    }
}

void Faculty::writeFacultyListToFile(const string& filename) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cout << "Failed to open the file." << endl;
        return;
    }

    FacultyNode* current = head;
    while (current != nullptr) {
        outputFile << current->name << endl;
        outputFile << current->initial << endl;
        outputFile << current->designation << endl;
        outputFile << current->email << endl;
        outputFile << current->phoneNumber << endl;
        outputFile << endl;
        current = current->next;
    }

    outputFile.close();
    cout << "Faculty data has been written to " << filename << "." << endl;
}
