#include <iostream>
#include <fstream>
#include <string>
#include "Faculty.h"
#include "Course.h"
#include <set>

using namespace std;

Faculty readFacultyFile() {
    ifstream facultyFile("FacultyList.txt");
    if (!facultyFile) {
        cout << "Failed to open the faculty file." << endl;
        return Faculty(); // Return an empty Faculty object
    }

    Faculty facultyList;

    string facultyName;
    string facultyInitials;
    string facultyPosition;
    string facultyEmail;
    string facultyPhone;

    while (getline(facultyFile, facultyName) && getline(facultyFile, facultyInitials) && getline(facultyFile, facultyPosition) && getline(facultyFile, facultyEmail) && getline(facultyFile, facultyPhone)) {
        facultyList.createFaculty(facultyName, facultyInitials, facultyPosition, facultyEmail, facultyPhone);
    }

    facultyFile.close();

    return facultyList;
}


Course readCourseFile() {
    ifstream courseFile("CourseTimings.txt");
    if (!courseFile) {
        cout << "Failed to open the course file." << endl;
        return Course(); // Return an empty Course object
    }

    Course courseList;

    string courseName;
    double courseCredit;
    string facultyInitials;
    int day;
    int time;
    int section;

    while (courseFile >> courseName >> section >> courseCredit >> facultyInitials >> day >> time) {
        courseList.createCourse(courseName, courseCredit, facultyInitials, day, time, section);
    }

    courseFile.close();

    return courseList;
}


    int getRemainingCourseCount(const Course& courseList, const set<int>& assignedSections) {
    int count = 0;
    CourseNode* course = courseList.getHead();
    while (course != nullptr) {
        if (assignedSections.find(course->section) == assignedSections.end()) {
            count++;
        }
        course = course->next;
    }
    return count;
}

    FacultyNode* getNextFaculty(FacultyNode* currentFaculty, FacultyNode* facultyListHead) {
    // If the current faculty is nullptr or it's the last faculty in the list,
    // return the first faculty from the list
    if (currentFaculty == nullptr || currentFaculty->next == nullptr) {
        return facultyListHead;
    }

    // Otherwise, find the next faculty in the list based on the current faculty's initials
    FacultyNode* nextFaculty = facultyListHead;
    while(nextFaculty != nullptr){
        if (nextFaculty->initial == currentFaculty->initial) {
            return nextFaculty->next;
        }
        nextFaculty = nextFaculty->next;
    }

    // Return nullptr if the next faculty is not found
    return nullptr;
}

void generateRoutine() {
    Faculty facultyListNew = readFacultyFile();
    Course courseListNew = readCourseFile();

    // Print the faculty list
    cout << "Faculty List:" << endl;
    FacultyNode* facultyNode = facultyListNew.getHead();
    while (facultyNode != nullptr) {
        cout << "Name: " << facultyNode->name << endl;
        cout << "Initials: " << facultyNode->initial << endl;
        cout << "Position: " << facultyNode->designation << endl;
        cout << "Email: " << facultyNode->email << endl;
        cout << "Phone: " << facultyNode->phoneNumber << endl;
        cout << endl;
        facultyNode = facultyNode->next;
    }

    // Print the course list
    cout << "Course List:" << endl;
    CourseNode* courseNode = courseListNew.getHead();
    while (courseNode != nullptr) {
        cout << "Course Name: " << courseNode->courseName << endl;
        cout << "Section: " << courseNode->section << endl;
        cout << "Credit: " << courseNode->courseCredit << endl;
        cout << "Faculty Initials: " << courseNode->facultyInitials << endl;
        cout << "Day: " << courseNode->day << endl;
        cout << "Time: " << courseNode->time << endl;
        cout << endl;
        courseNode = courseNode->next;
    }

    // Create an output file stream to write the routine to a file
    ofstream outputFile("Routine.txt");
    if (!outputFile) {
        cout << "Failed to create the output file." << endl;
        return;
    }

    // Get the head of the faculty linked list
    FacultyNode* faculty = facultyListNew.getHead();

    // Get the head of the course linked list
    CourseNode* courseHead = courseListNew.getHead();

    // Calculate the number of faculties and courses
    int numFaculties = 0;
    int numCourses = 0;

    FacultyNode* facultyNodeCount = faculty;
    while (facultyNodeCount != nullptr) {
        numFaculties++;
        facultyNodeCount = facultyNodeCount->next;
    }

    CourseNode* courseNodeCount = courseHead;
    while (courseNodeCount != nullptr) {
        numCourses++;
        courseNodeCount = courseNodeCount->next;
    }

    // Create arrays to store the assigned courses and their corresponding faculty members
    string* assignedCourseNames = new string[numCourses];
    FacultyNode** assignedFaculties = new FacultyNode*[numCourses];

    // Iterate over the courses and assign them to faculties
    CourseNode* course = courseHead;
        for (int i = 0; i < numCourses; i++) {
    assignedCourseNames[i] = course->courseName;
    assignedFaculties[i] = faculty;

    // Check if adding the course's credit will exceed the available credits for the faculty
        if (faculty->availableCredits - course->courseCredit < 0) {
        // Credits will exceed the limit, so you can handle this case accordingly
        // For example, you can skip assigning this course to the faculty or perform any necessary actions
        // Here, I will print a warning message and continue to the next course
            cout << "Warning: Adding course '" << course->courseName << "' will exceed faculty '" << faculty->name << "'s available credits." << endl;
            course = (course->next != nullptr) ? course->next : courseHead;
    }
    if((faculty->availableCredits-=course->courseCredit)<0){
    // Move to the next faculty
        faculty = getNextFaculty(faculty, facultyListNew.getHead());
        faculty->availableCredits -= course->courseCredit;
        course = (course->next != nullptr) ? course->next : courseHead;
    }
    else
    {
    // Add the course's credit to the faculty's available credits
        faculty->availableCredits -= course->courseCredit;
        course = (course->next != nullptr) ? course->next : courseHead;
    }
}

    // Print the assigned faculties and courses for debugging
    for (int i = 0; i < numCourses; i++) {
        cout << "Assigned Faculty: " << assignedFaculties[i]->name << ", Course: " << assignedCourseNames[i] << endl;
    }

    // Iterate over the assigned courses and write the routine to the output file
    for (int i = 0; i < numCourses; i++) {
    const string& courseName = assignedCourseNames[i];
    FacultyNode* assignedFaculty = assignedFaculties[i];

    outputFile << "Faculty: " << assignedFaculty->name << endl;
    outputFile << "Course: " << courseName << endl;

    // Find the corresponding course for the assigned course name
    CourseNode* assignedCourse = courseListNew.getHead();
    while (assignedCourse != nullptr) {
        if (assignedCourse->courseName == courseName) {
            // Convert day and time slot values to their respective strings
            string dayStr;
            string timeSlotStr;

            switch (assignedCourse->day) {
                case 0:
                    dayStr = "ST";
                    break;
                case 1:
                    dayStr = "MW";
                    break;
                case 2:
                    dayStr = "RA";
                    break;
                default:
                    dayStr = "Invalid Day";
            }

            switch (assignedCourse->time) {
                case 0:
                    timeSlotStr = "8:00-9:30";
                    break;
                case 1:
                    timeSlotStr = "9:40-11:10";
                    break;
                case 2:
                    timeSlotStr = "11:20-12:50";
                    break;
                case 3:
                    timeSlotStr = "1:00-2:30";
                    break;
                case 4:
                    timeSlotStr = "2:40-4:10";
                    break;
                case 5:
                    timeSlotStr = "4:20-5:50";
                    break;
                default:
                    timeSlotStr = "Invalid Time Slot";
            }

            outputFile << "Day: " << dayStr << endl;
            outputFile << "Time: " << timeSlotStr << endl;
            outputFile << "Section: " << assignedCourse->section << endl;
            outputFile << endl;
            break;
        }
        assignedCourse = assignedCourse->next;
    }
}

    // Close the output file
    outputFile.close();

    // Deallocate the dynamically allocated arrays
    delete[] assignedCourseNames;
    delete[] assignedFaculties;

    cout << "Routine has been written to Routine.txt." << endl;
}
