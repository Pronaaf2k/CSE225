#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"

struct FacultyNode {
    string name;
    string initial;
    string designation;
    string email;
    string phoneNumber;
    double availableCredits;
    CourseNode* courses;
    int numCourses;
    FacultyNode* next;
};

class Faculty {
private:
    FacultyNode* head;

public:
    Faculty();  // Default constructor
    void createFaculty(const string& name, const string& initial, const string& designation, const string& email, const string& phoneNumber);
    void readFacultyList(const string& filename);
    void readFaculty(const string& name);
    void updateFaculty(const string& name, const string& newPhoneNumber);
    void deleteFaculty(const string& name);
    void printAllFaculties();
    void writeFacultyListToFile(const string& filename);

    FacultyNode* getHead() const {
        return head;
    }

    void setHead(FacultyNode* node) {
        head = node;
    }
};

#endif // FACULTY_H
