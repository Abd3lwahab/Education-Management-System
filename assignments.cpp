#include "assignments.h"

// Create new assignment
void createAssignment(shared_ptr <Course> thisCourse) {
    shared_ptr <Assignment> newAssignment (new Assignment);

    cout << "\nPlease enter the following information:\n";

    cout << "Content: ";
    getline(cin >> ws, newAssignment->content);

    cout << "Max Mark: ";
    cin >> newAssignment->maxMark;

    newAssignment->course = thisCourse;

    thisCourse->assignments.push_back(newAssignment);

    cout << "Assignment created successfully\n";
}

// List assignments on this course
void listAssignments(shared_ptr <Course> thisCourse) {
    int n = thisCourse->assignments.size();
    
    cout << "\nThere is "<< n << " assignments for this course.\n";

    for (int i = 0; i < n; i++) {
        cout<< "[" << i + 1 << "] Assignment " << i + 1
            << ", Max mark: " << thisCourse->assignments[i]->maxMark
            << ", Submissions count: " <<thisCourse->assignments[i]->assignmentSolutions.size() << '\n';
    }
}

// Return index of which assignment to view
int viewAssignment(shared_ptr <Course> thisCourse) {
    listAssignments(thisCourse);

    int assignmentIndex = 0;
    cout << "\nEnter index of assignment to view [1:"<< thisCourse->assignments.size() << "]: ";
    assignmentIndex = getInt(1, thisCourse->assignments.size()) - 1;

    return assignmentIndex;
}

void showAssignmentInfo(shared_ptr <Assignment> thisAssignment) {
    cout<< "\nContent: " << thisAssignment->content
        << "\nMax mark: " <<  thisAssignment->maxMark 
        << "\nSubmissions count: " <<thisAssignment->assignmentSolutions.size() << '\n';
}

void showSolutionInfo(shared_ptr <AssignmentSolution> thisSolution) {
    cout<< "\nStudent Name: " << thisSolution->student->info.fullName
        << "\nSolution: " << thisSolution->solution
        << "\nMark: " << thisSolution->mark
        << "\nMax Mark: "<< thisSolution->assignment->maxMark
        << "\nComment: "<< thisSolution->comment << "\n";
}

void setGrade(shared_ptr <AssignmentSolution> thisSolution) {
    cout << "\nEnter mark: ";
    cin >> thisSolution->mark;
    thisSolution->isMarked = true;
    cout << "Mark set successfully\n";
}

void setComment(shared_ptr <AssignmentSolution> thisSolution) {
    cout << "\nEnter Comment: ";
    cin >> thisSolution->comment;
    cout << "Comment set successfully\n";
}

// Check if there is old solution and delete it
void removeOldSolution(shared_ptr <Student> thisStudent, int assignmentIndex, int courseIndex) {
    vector <shared_ptr<AssignmentSolution>> &oldSolutions = thisStudent->assignmentSolutions;
    vector <shared_ptr<AssignmentSolution>> &allSolutions = thisStudent->courses[courseIndex]->assignments[assignmentIndex]->assignmentSolutions;
    
    for (int i = 0; i < oldSolutions.size() ;i++) {
        if (oldSolutions[i]->assignment == thisStudent->courses[courseIndex]->assignments[assignmentIndex]) {
            for (int j = 0; j < allSolutions.size(); j++) {
                if (allSolutions[j] == oldSolutions[i]) {
                    allSolutions.erase(allSolutions.begin() + j);
                    break;
                }
            }
            oldSolutions.erase(oldSolutions.begin() + i);
            break;
        }
    }
}

vector <tuple<string, int, int, int, int>> getGradeReport(shared_ptr <Student> thisStudent) {
    /**
     * Create tuple for each course
     * Each tuple contain  "course code", "number of submited", "number of assignment", "total marks of submited", "total max marks of submited"
    **/
    vector <tuple<string, int, int, int, int>> report;

    // Map from course code to number of submited on this course assignments
    map <string, int> codeToSubmitedCount;

    // Map from course code to number of assignment on this course assignments
    map <string, int> codeToAssignmentsCount;

    // Map from course code to total marks of submited assignments of this course
    map <string, int> codeToTotalMarks;

    // Map from course code to total max marks of submited assignments of this course
    map <string, int> codeToTotalMaxMarks;

    for (auto thisSolution : thisStudent->assignmentSolutions) {
        string code = thisSolution->assignment->course->code;
        if (thisSolution->isMarked)
            codeToTotalMarks[code] += thisSolution->mark;
        codeToTotalMaxMarks[code] += thisSolution->assignment->maxMark;
        codeToSubmitedCount[code]++;
        codeToAssignmentsCount[code] = thisSolution->assignment->course->assignments.size();
    }

    for (auto codeValue: codeToSubmitedCount) {
        string code = codeValue.first;
        tuple<string, int, int, int, int> info (code, codeToSubmitedCount[code], codeToAssignmentsCount[code],codeToTotalMarks[code], codeToTotalMaxMarks[code]);

        report.push_back(info);
    }

    return report;
}

vector <tuple <int, string, string, int>> getAssignmentsStatus(shared_ptr <Student> thisStudent, int courseIndex) {
    /** 
     * Create tuple for each assignment 
     * Each tuple contain "assignment index", "status of this assignment", "mark if submited", "max mark"
    **/
    vector <tuple <int, string, string, int>> report;

    // Map from assignment index to submition status
    map <int, string> indexToStatus;

    // Map from assignment index to mark of solution
    map <int, string> indexToMark;

    // Map from assignment index to max mark
    map <int, int> IndexToMaxMark;

    int i = 1;
    for (auto assignment : thisStudent->courses[courseIndex]->assignments) {
        for (auto solution : thisStudent->assignmentSolutions) {
            if (solution->assignment == assignment) {
                indexToStatus[i] = "Submited";
                if (solution->isMarked)
                    indexToMark[i] = to_string(solution->mark);
                else
                    indexToMark[i] = "NA";
                break;
            }
        }
        if (indexToStatus[i] != "Submited") {
            indexToStatus[i] = "Not Submited";
            indexToMark[i] = "NA";
        }
        IndexToMaxMark[i] = assignment->maxMark;
        i++;
    }

    for (auto element : indexToStatus) {
        int index = element.first;
        tuple <int, string, string, int> info(index, indexToStatus[index], indexToMark[index], IndexToMaxMark[index]);
        report.push_back(info);
    }

    return report;
}

void deleteAssignment(shared_ptr <Assignment> thisAssignment) {
    // Delete Solutions of this Assignment from student solution
    for (auto solution : thisAssignment->assignmentSolutions) {
        for (int i = 0; i < solution->student->assignmentSolutions.size(); i++) {
            if (solution->student->assignmentSolutions[i]->assignment == thisAssignment) {
                solution->student->assignmentSolutions.erase(solution->student->assignmentSolutions.begin() + i);
                break;
            }
        }
    }

    // Delete All solutions from this assignment
    while(thisAssignment->assignmentSolutions.size()) {
        thisAssignment->assignmentSolutions.pop_back();
    }
    
    // Delete Assignment
    for (int i = 0; i < thisAssignment->course->assignments.size(); i++){
        if (thisAssignment->course->assignments[i] == thisAssignment) {
            thisAssignment->course->assignments.erase(thisAssignment->course->assignments.begin() + i);
            break;
        }
    }

    cout << "Assignment deleted successfully\n";
}