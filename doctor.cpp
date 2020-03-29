#include "doctor.h"

vector <shared_ptr <Doctor>> doctors;

// Return pointer to current doctor
shared_ptr <Doctor> getPointerDoctor(int index) {
    shared_ptr <Doctor> thisDoctor (new Doctor);
    thisDoctor = doctors[index];

    return thisDoctor;
}

// Doctor main menu
void doctorMenu(shared_ptr <Doctor> thisDoctor) {
    int operation = -1;
    while (operation) {
        vector <string> menu = {"List Courses", "Create course", "View Course", "Log out"};
		viewMenu(menu);

        operation = getInt(0, 3);
        switch (operation) {
            case 1:
                listDoctorCourses(thisDoctor);
                break;
            case 2:
                createCourse(thisDoctor);
                break;
            case 3:
                viewDoctorCourse(thisDoctor);
                break;
        }
    }
}

void listDoctorCourses(shared_ptr <Doctor> thisDoctor) {
    int n = thisDoctor->courses.size();
    cout << "\nDoctor " << thisDoctor->info.fullName << " Teach " << n << " courses.\n";

    listCourses(thisDoctor->courses);
}

void viewDoctorCourse(shared_ptr <Doctor> thisDoctor) {
    // Check if doctor courses empty
    if (!(thisDoctor->courses.size())) {
        cout << "\nThere is no Courses to view\n";
        return;
    }

    int courseIndex = viewCourse(thisDoctor->courses);
    viewCourseMenu(thisDoctor->courses[courseIndex]);
}

void viewCourseMenu(shared_ptr <Course> thisCourse) {
    int operation = -1;
    while (operation) {
        vector <string> menu = {"List Assignments", "Create Assignment", "View Assignment", "Delete Course","Back"};
		viewMenu(menu);

        operation = getInt(0, 4);
        switch (operation) {
            case 1:
                listAssignments(thisCourse);
                break;
            case 2:
                createAssignment(thisCourse);
                break;
            case 3:
                viewAssignmentsDoctor(thisCourse);
                break;
            case 4:
                deleteCourse(thisCourse);
                operation = 0;
                break;
        } 
    }
}

void viewAssignmentsDoctor(shared_ptr <Course> thisCourse) {
    // Check if course assignment empty
    if (!thisCourse->assignments.size()) {
        cout << "\nThere is no assignment to view\n";
        return;
    }

    int assignmentIndex = viewAssignment(thisCourse);
    viewAssignmentMenu(thisCourse->assignments[assignmentIndex]);
}

void viewAssignmentMenu(shared_ptr <Assignment> thisAssignment) {
    int operation = -1;
    while (operation) {
        vector <string> menu = {"Show Info", "Show Grades Report", "List Solutions", "View Solution", "Delete Assignment", "Back"};
		viewMenu(menu);
        
        operation = getInt(0, 5);
        switch (operation) {
            case 1:
                showAssignmentInfo(thisAssignment);
                break;
            case 2:
                showGradesReport(thisAssignment);
                break;
            case 3:
                listSolutions(thisAssignment);
                break;
            case 4:
                viewSolution(thisAssignment);
                break;
            case 5:
                deleteAssignment(thisAssignment);
                operation = 0;
                break;
        } 
    }
}

void showGradesReport(shared_ptr <Assignment> thisAssignment) {
    int sum = 0, n = thisAssignment->assignmentSolutions.size();
    if (n == 0) {
        cout <<"\nThere is no submissions yet\n"; 
        return;
    }

    // Get pointer to solution contain max and min mark
    shared_ptr <AssignmentSolution> max = thisAssignment->assignmentSolutions[0];
    shared_ptr <AssignmentSolution> min = thisAssignment->assignmentSolutions[0];

    for (auto solution : thisAssignment->assignmentSolutions){
        sum += solution->mark;
        if (solution->mark > max->mark)
            max = solution;
        else if (solution->mark < min->mark)
            min = solution;
    }

    cout<< "\nThere is " << n << " submissions\n" <<"Average Of marks: " << sum / n 
    <<"\nMax mark: "<< max->mark << ", Students: " << max->student->info.fullName 
    <<"\nMin mark: "<< min->mark << ", Students: " << min->student->info.fullName << "\n";
}

void listSolutions(shared_ptr <Assignment> thisAssignment) {
    int  n = thisAssignment->assignmentSolutions.size();
    cout << "\nThere is " << n << " solutions\n";
    
    for (int i = 0; i < n; i++) {
        cout<< "[" << i + 1 << "]"  << " Solution: " << thisAssignment->assignmentSolutions[i]->solution
            << " Mark: " <<thisAssignment->assignmentSolutions[i]->mark
            << " Student Name: " <<thisAssignment->assignmentSolutions[i]->student->info.fullName << "\n";
    }
}

void viewSolution(shared_ptr <Assignment> thisAssignment) {
    listSolutions(thisAssignment);

    // Check if there is no solution fot this assignment
    int n = thisAssignment->assignmentSolutions.size();
    if (!n) return;

    int indexSolution;
    cout<< "\nEnter index of solution to view [1:" << n << "]: ";
    indexSolution = getInt(1, n) - 1;

    viewSolutionMenu(thisAssignment->assignmentSolutions[indexSolution]);
}

void viewSolutionMenu(shared_ptr <AssignmentSolution> thisSolution) {
    int operation = -1;
    while (operation) {
        vector <string> menu = {"Show Info", "Set Grade", "Set a Comment", "Back"};
		viewMenu(menu);

        operation = getInt(0, 3);
        switch (operation) {
            case 1:
                showSolutionInfo(thisSolution);
                break;
            case 2:
                setGrade(thisSolution);
                break;
            case 3:
                setComment(thisSolution);
                break;
        } 
    }
}