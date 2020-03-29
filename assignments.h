#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <map>
#include <tuple>

#include "course.h"
#include "doctor.h"

using std::tuple;
using std::map;
using std::istream;
using std::ws;
using std::to_string;

struct Assignment
{
	string content;
	int maxMark;
	shared_ptr <Course> course;
	vector <shared_ptr <AssignmentSolution>> assignmentSolutions;
};

struct AssignmentSolution
{
	bool isMarked = false;
	string solution;
	int mark = 0;
	string comment = "There is no comment";
	shared_ptr <Assignment> assignment;
	shared_ptr <Student> student;
};

// Doctor methods
void createAssignment(shared_ptr <Course> thisCourse);
void showSolutionInfo(shared_ptr <AssignmentSolution> thisSolution);
void setGrade(shared_ptr <AssignmentSolution> thisSolution);
void setComment(shared_ptr <AssignmentSolution> thisSolution);
void deleteAssignment(shared_ptr <Assignment> thisAssignment);

// Student methods
vector <tuple <int, string, string, int>> getAssignmentsStatus(shared_ptr <Student> thisStudent, int courseIndex);
vector <tuple<string, int, int, int, int>> getGradeReport(shared_ptr <Student> thisStudent);
void removeOldSolution(shared_ptr <Student> thisStudent, int assignmentIndex, int courseIndex);

// Common methods
void listAssignments(shared_ptr <Course> thisCourse);
int viewAssignment(shared_ptr <Course> thisCourse);

#endif

