#include "course.h"

Course::Course() {
    head = nullptr;
}

void Course::createCourse(const string& name, double credit) {
    createCourse(name, credit, 0, 0);
}

void Course::createCourse(const string& name, double credit, int day, int time) {
    createCourse(name, credit, "TBA", day, time, 1); // Default section is 1, faculty initials is "TBA"
}

void Course::createCourse(const string& name, double credit, const string& facultyInitials, int day, int time, int section) {
    CourseNode* newNode = new CourseNode;
    newNode->courseName = name;
    newNode->courseCredit = credit;
    newNode->facultyInitials = facultyInitials; // Assign faculty initials
    newNode->day = day;
    newNode->time = time;
    newNode->section = section;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        CourseNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void Course::assignRandomTimes() {
    CourseNode* current = head;
    while (current != nullptr) {
        int randomDay = rand() % 2; // Assign random day: 0-4 for Sunday to Thursday
        int randomTime = rand() % 6; // Assign random time: 0-5 for the 6 time slots of each day

        // Check if the generated time slot clashes with any existing section of the same course
        CourseNode* temp = head;
        bool timeClash = false;
        while (temp != current) {
            if (temp->courseName == current->courseName && temp->day == randomDay && temp->time == randomTime) {
                timeClash = true;
                break;
            }
            temp = temp->next;
        }

        if (!timeClash) {
            current->day = randomDay;
            current->time = randomTime;
        }

        current = current->next;
    }
}

// Other member function implementations...

void Course::readCourse(const string& name) {
    if (head == nullptr) {
        cout << "No courses in the list." << endl;
        return;
    }

    CourseNode* current = head;
    while (current != nullptr) {
        if (current->courseName == name) {
            cout << "Course Name: " << current->courseName << endl;
            cout << "Section: " << current->section << endl;
            cout << "Credit: " << current->courseCredit << endl;
            cout << "Faculty Initials: " << current->facultyInitials << endl;
            cout << "Day: " << current->day << endl;
            cout << "Time: " << current->time << endl;
            return;
        }
        current = current->next;
    }

    cout << "Course not found." << endl;
}

void Course::updateCourse(const string& name, double credit, int day, int time) {
    if (head == nullptr) {
        cout << "No courses in the list." << endl;
        return;
    }

    CourseNode* current = head;
    while (current != nullptr) {
        if (current->courseName == name) {
            current->courseCredit = credit;
            current->day = day;
            current->time = time;
            cout << "Course updated successfully." << endl;
            return;
        }
        current = current->next;
    }

    cout << "Course not found." << endl;
}

void Course::deleteCourse(const string& name) {
    if (head == nullptr) {
        cout << "No courses in the list." << endl;
        return;
    }

    if (head->courseName == name) {
        CourseNode* temp = head;
        head = head->next;
        delete temp;
        cout << "Course deleted successfully." << endl;
        return;
    }

    CourseNode* current = head;
    while (current->next != nullptr) {
        if (current->next->courseName == name) {
            CourseNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Course deleted successfully." << endl;
            return;
        }
        current = current->next;
    }

    cout << "Course not found." << endl;
}

void Course::displayCourses() {
    if (head == nullptr) {
        cout << "No courses in the list." << endl;
        return;
    }

    CourseNode* current = head;
    cout << "Course Name\tSection\tCredit\tFaculty Initials\tDay\tTime" << endl;
    while (current != nullptr) {
        cout << current->courseName << "\t\t" << current->section << "\t" << current->courseCredit << "\t" << current->facultyInitials << "\t\t" << current->day << "\t" << current->time << endl;
        current = current->next;
    }
}

void Course::readCoursesFromFile(const string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile) {
        cout << "Failed to open the file." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string name;
        double credit;

        if (iss >> name >> credit) {
            createCourse(name, credit, "TBA", 0, 0, 1); // Default section is 1, faculty initials is "TBA"
        }
    }

    inputFile.close();
}

void Course::printCourseTimings() {
    if (head == nullptr) {
        cout << "No courses in the list." << endl;
        return;
    }

    CourseNode* current = head;
    cout << "Course Name\tSection\tCredit\tFaculty Initials\tDay\tTime" << endl;
    while (current != nullptr) {
        cout << current->courseName << "\t\t" << current->section << "\t" << current->courseCredit << "\t" << current->facultyInitials << "\t\t" << current->day << "\t" << current->time << endl;
        current = current->next;
    }
}

void Course::writeCourseTimingsToFile(const string& fileName) {
    ofstream outputFile(fileName);
    if (!outputFile) {
        cout << "Failed to create the output file." << endl;
        return;
    }

    CourseNode* current = head;
    while (current != nullptr) {
        outputFile << current->courseName << " " << current->section << " " << current->courseCredit << " " << current->facultyInitials << " " << current->day << " " << current->time << endl;
        current = current->next;
    }

    outputFile.close();
    cout << "Course timings have been written to " << fileName << "." << endl;
}

CourseNode* Course::findCourseBySection(int section) const {
    CourseNode* current = head;
    while (current != nullptr) {
        if (current->section == section) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
