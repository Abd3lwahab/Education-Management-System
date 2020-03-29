#include "course.h"

vector <shared_ptr <Course>> courses;

// Create new course
void createCourse(shared_ptr <Doctor> thisDoctor)
{
    shared_ptr <Course> newCourse (new Course);

    cout << "\nPlease enter the following information:\n";
    cout << "Title: ";
    getline(cin >> ws, newCourse->title);

    cout << "Code: ";
    cin >> newCourse->code;

    newCourse->lecturer = thisDoctor;
    
    courses.push_back(newCourse);
    thisDoctor->courses.push_back(courses.back());

    cout << "Course created successfully\n";
}

// List courses of this doctor
void listCourses(vector <shared_ptr <Course>> myCourses) {
    cout << '\n';
    for (int i = 0; i < myCourses.size(); i++) {
        cout<< "["<< i + 1<< "] Course: "<<  myCourses[i]->title  << ", Code: " 
            << myCourses[i]->code << "\n";
    }
}

// Return index of which course want to viewd
int viewCourse(vector <shared_ptr <Course>> myCourses) {
    listCourses(myCourses);

    int courseIndex = 0;
    cout << "\nEnter index of course to view [1:"<< myCourses.size() << "]: ";
    courseIndex = getInt(1, myCourses.size());
    return courseIndex - 1;
}

// Register course for this student
void registerCourses(shared_ptr <Student> thisStudent) {
    vector <shared_ptr <Course>> unregistedCourses = getUnregistedCourses(thisStudent->courses);

    int n = unregistedCourses.size();
    cout << "\nThere is " << n << " Courses available: \n";
    if (!n) return;
    
    listCourses(unregistedCourses);

    int index;
    cout << "\nEnter index of course to register [1:" << n << "]: ";
    index = getInt(1, n) - 1;

    thisStudent->courses.push_back(unregistedCourses[index]);
    unregistedCourses[index]->registeredStudents.push_back(thisStudent);
    cout << "Course registered successfully\n";
}

// Get vector of courses and return the rest of courses
vector <shared_ptr <Course>> getUnregistedCourses(vector <shared_ptr <Course>> registedCourses) {
    vector <shared_ptr <Course>> unregistedCourses;

    for (int i = 0; i < courses.size(); i++) {
        bool found= false;
        for (int j = 0; j < registedCourses.size(); j++) {
            if (registedCourses[j]->title == courses[i]->title) {
                found = true;
                break;
            }
        }
        if (!found)
            unregistedCourses.push_back(courses[i]);
    }

    return unregistedCourses;
}

// Unregister course for this student
void unregisterCourse(shared_ptr <Student> thisStudent, int courseIndex) {
    int allCourseIndex, thisStudentIndex;
    bool found = false;
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i] == thisStudent->courses[courseIndex]) {
            for (int j = 0; j < courses[i]->registeredStudents.size(); j++) {
                if (courses[i]->registeredStudents[j] == thisStudent) {
                    found = true;
                    allCourseIndex = i;
                    thisStudentIndex = j;
                    break;
                }
            }
        }
        if (found) break;
    }
    // Remove this student from course registered students vector
    courses[allCourseIndex]->registeredStudents.erase(courses[allCourseIndex]->registeredStudents.begin() + thisStudentIndex);
    
    // Remove this course from student courses
    thisStudent->courses.erase(thisStudent->courses.begin() + courseIndex);

    cout << "Course unregistered successfully\n";
}

void deleteCourse(shared_ptr <Course> thisCourse) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i] == thisCourse) {
            // Delete course from doctor courses
            for (int j = 0; j < thisCourse->lecturer->courses.size(); j++) {
                if (thisCourse->lecturer->courses[j] == thisCourse) {
                    thisCourse->lecturer->courses.erase(thisCourse->lecturer->courses.begin() + j);
                    break;
                }
            }

            // Delete course from each registered students
            for (auto student : thisCourse->registeredStudents) {
                // Delete course from each student courses vevtor
                for (int j = 0; j < student->courses.size(); j++) {
                    if (student->courses[j] == thisCourse) {
                        student->courses.erase(student->courses.begin() + j);
                        break;
                    }
                }

                // Delete all assignment solution from each student on this Course
                for (int j = 0; j < student->assignmentSolutions.size(); j++) {
                    if (student->assignmentSolutions[j]->assignment->course == thisCourse) {
                        student->assignmentSolutions.erase(student->assignmentSolutions.begin() + j);
                        j--;
                    }
                }
            }
            
            // Delete all assignment on this course
            while (thisCourse->assignments.size()){
                thisCourse->assignments.pop_back();
            }
            
            // Delete course from courses vector
            courses.erase(courses.begin() + i);
            break;
        }
    }
    cout << "Course Deleted sucssessfully\n";
}