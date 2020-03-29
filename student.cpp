#include "student.h"

vector <shared_ptr <Student>> students;

// Return pointer to current student
shared_ptr <Student> getPointerStudent(int index) {
    shared_ptr <Student> thisStudent (new Student);
    thisStudent = students[index];

    return thisStudent;
}

// Student main menu
void studentMenu(shared_ptr <Student> thisStudent) {
    int operation = -1;
    while (operation) {
        vector <string> menu = {"Register in course", "List My Courses", "View Course", "Grades Report", "Log out"};
		viewMenu(menu);

        operation = getInt(0, 4);
        switch (operation) {
            case 1:
                registerCourses(thisStudent);
                break;
            case 2:
                listStudentCourses(thisStudent);
                break;
            case 3:
                viewCourseStudent(thisStudent);
                break;
            case 4:
                studentGradeReport(thisStudent);
                break;
        }
    }   
}

void listStudentCourses(shared_ptr <Student> thisStudent) {
    int n = thisStudent->courses.size();
    cout << "\nYou registerd in " << n << " courses\n";

    listCourses(thisStudent->courses);
}

void viewCourseStudent(shared_ptr <Student> thisStudent) {
    // Check if student courses empty
    if (!(thisStudent->courses.size())) {
        cout << "\nThere is no Courses to view\n";
        return;
    }

    int courseIndex = viewCourse(thisStudent->courses);
    viewCourseStudentMenu(thisStudent, courseIndex);
}

void studentGradeReport(shared_ptr <Student> thisStudent) {
    int n = thisStudent->courses.size();
    cout<< "\nYou registerd in " << n << " courses, and submittied "<< thisStudent->assignmentSolutions.size()
        << " solutions\n";

    // Get report of student submtions grade
    vector <tuple<string, int, int, int, int>> report = getGradeReport(thisStudent);
    if (report.size() == 0)
        cout << "There are no submissions yet\n";

    for (auto info: report) {
        cout<<"Course Code: " << get<0>(info) << ", Total submittied: " << get<1>(info) << "/" << get<2>(info)
            << ", Grade: " << get<3>(info) << "/" << get<4>(info) <<"\n";
    }
}

void viewCourseStudentMenu(shared_ptr <Student> thisStudent, int courseIndex) {
    shared_ptr <Course> thisCourse = thisStudent->courses[courseIndex];

    cout<< "\nCourse: " << thisCourse->title 
        << ", Code: " << thisCourse->code
        << ", The lecturer: Dr." << thisCourse->lecturer->info.fullName << "\n";

    int operation = -1;
    while(operation) {
        vector <string> menu = {"List Assignments", "View Assignment", "Show Assignments Status", "Unregister from course", "Back"};
		viewMenu(menu);

        operation = getInt(0, 4);
        switch (operation) {
            case 1:
                listAssignments(thisStudent->courses[courseIndex]);
                break;
            case 2:
                AssignmentStudentMenu(thisStudent, courseIndex);
                break;
            case 3:
                viewAssignmentsStatus(thisStudent, courseIndex);
                break;
            case 4:
                unregisterCourse(thisStudent, courseIndex);
                operation = 0;
                break;
        }
    }
}

void AssignmentStudentMenu(shared_ptr <Student> thisStudent, int courseIndex) {
    // Check if course assignment empty
    if (!thisStudent->courses[courseIndex]->assignments.size()) {
        cout << "\nThere is no assignment to view\n";
        return;
    }

    int assignmentIndex = viewAssignment(thisStudent->courses[courseIndex]);
    viewAssignmentStudentMenu(thisStudent, assignmentIndex, courseIndex);
}

void viewAssignmentStudentMenu(shared_ptr <Student> thisStudent, int assignmentIndex, int courseIndex) {
    int operation = -1;
    while(operation) {
        vector <string> menu = {"Show Assignment info", "Submit assignment solution", "Back"};
		viewMenu(menu);

        operation = getInt(0, 2);
        switch (operation) {
            case 1:
                showAssignmentInfo(thisStudent->courses[courseIndex]->assignments[assignmentIndex]);
                break;
            case 2:
                submitSolution(thisStudent, assignmentIndex, courseIndex);
                operation = 0;
                break;
        }
    }
}

void submitSolution(shared_ptr <Student> thisStudent, int assignmentIndex,  int courseIndex) {
    // Student can only have one solution to the same assignment
    removeOldSolution(thisStudent, assignmentIndex, courseIndex);

    shared_ptr <AssignmentSolution> newSolution (new AssignmentSolution);
    cout << "Enter the Solution: \n";
    getline(cin >> ws, newSolution->solution);

    newSolution->student = thisStudent;
    newSolution->assignment = thisStudent->courses[courseIndex]->assignments[assignmentIndex];

    thisStudent->assignmentSolutions.push_back(newSolution);
    thisStudent->courses[courseIndex]->assignments[assignmentIndex]->assignmentSolutions.push_back(newSolution);

    cout << "\nSoultion submited successfully\n";
}

void viewAssignmentsStatus(shared_ptr <Student> thisStudent, int courseIndex) {
    // Get report of this course assignmnets status
    vector <tuple <int, string, string, int>> report = getAssignmentsStatus(thisStudent, courseIndex);
    for (auto info : report) {
        cout<<"Assginment " << get<0>(info) << ", " << get<1>(info) << ", Mark: " << get<2>(info)
            << "/" << get<3>(info) <<"\n";
    }
}