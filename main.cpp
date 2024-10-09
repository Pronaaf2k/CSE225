#include <iostream>
#include "Course.cpp"
#include "Faculty.cpp"
#include "RoutineList.cpp"

using namespace std;

int main() {


    Course course;
    course.readCoursesFromFile("CourseList.txt");
    course.assignRandomTimes();
    course.printCourseTimings();
    course.writeCourseTimingsToFile("CourseTimings.txt");

    Faculty faculty;
    faculty.readFacultyList("FacultyList.txt");
    faculty.writeFacultyListToFile("Faculties.txt");

    Faculty facultyList;
    Course courseList;

    // Generate the routine
    generateRoutine();

    return 0;


}
