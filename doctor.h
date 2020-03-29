#ifndef DOCTOR_H
#define DOCTOR_H

#include "helper.h"
#include "student.h"
#include "course.h"
#include "assignments.h"

struct Doctor
{
	Person info;
	vector <shared_ptr <Course>> courses;
};

extern vector <shared_ptr <Doctor>> doctors;

shared_ptr <Doctor> getPointerDoctor(int index);

// Doctor menus funtions
void doctorMenu(shared_ptr <Doctor> thisDoctor);
void viewSolutionMenu(shared_ptr <AssignmentSolution> thisSolution);
void viewCourseMenu(shared_ptr <Course> thisCourse);
void viewAssignmentMenu(shared_ptr <Assignment> thisAssignment);

// Course methods
void viewDoctorCourse(shared_ptr <Doctor> thisDoctor);
void listDoctorCourses(shared_ptr <Doctor> thisDoctor);

// Assignment methods
void viewAssignmentsDoctor(shared_ptr <Course> thisCourse);
void showAssignmentInfo(shared_ptr <Assignment> thisAssignment);
void showGradesReport(shared_ptr <Assignment> thisAssignment);
void listSolutions(shared_ptr <Assignment> thisAssignment);
void viewSolution(shared_ptr <Assignment> thisAssignment);


#endif