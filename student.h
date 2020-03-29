#ifndef STUDENT_H
#define STUDENT_H

#include "course.h"
#include "assignments.h"
#include "helper.h"

using std::get;
using std::ostream;

struct Student
{
	Person info;
	vector <shared_ptr <Course>> courses;
	vector <shared_ptr <AssignmentSolution>> assignmentSolutions;
};

extern vector <shared_ptr <Student>> students;


shared_ptr <Student> getPointerStudent(int index);

// Student menus funtions
void studentMenu(shared_ptr <Student> thisStudent);
void viewCourseStudentMenu(shared_ptr <Student> thisStudent, int CourseIndex);
void viewAssignmentStudentMenu(shared_ptr <Student> thisStudent, int assignmentIndex, int courseIndex);
void AssignmentStudentMenu(shared_ptr <Student> thisStudent, int courseIndex);

// Course methods
void listStudentCourses(shared_ptr <Student> thisStudent);
void viewCourseStudent(shared_ptr <Student> thisStudent);

// Assignment methods
void studentGradeReport(shared_ptr <Student> thisStudent);
void submitSolution(shared_ptr <Student> thisStudent, int assignmentIndex,  int courseIndex);
void viewAssignmentsStatus(shared_ptr <Student> thisStudent, int courseIndex);

#endif