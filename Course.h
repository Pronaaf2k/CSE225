#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

struct CourseNode {
    string courseName;
    double courseCredit;
    string facultyInitials; // Added field to store faculty initials
    int day;
    int time;
    int section;
    CourseNode* next;
};

class Course {
private:
    CourseNode* head;

public:
    Course();

    CourseNode* findCourseBySection(int section) const;
    void createCourse(const string& name, double credit);
    void createCourse(const string& name, double credit, int day, int time);
    void createCourse(const string& name, double credit, const string& facultyInitials, int day, int time, int section); // Updated function signature

    void assignRandomTimes();

    void readCourse(const string& name);
    void updateCourse(const string& name, double credit, int day, int time);
    void deleteCourse(const string& name);

    void displayCourses();
    void readCoursesFromFile(const string& fileName);
    void printCourseTimings();
    void writeCourseTimingsToFile(const string& fileName);

    CourseNode* getHead() const {
        return head;
    }
    void setHead(CourseNode* node) {
        head = node;
    }
};

#endif // COURSE_H
