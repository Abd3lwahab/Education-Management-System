#ifndef COURSE_H
#define COURSE_H

#include "helper.h"
#include "doctor.h"
#include "student.h"
#include "assignments.h"

struct Course
{
	string code;
	string title;
	shared_ptr <Doctor> lecturer;
	vector <shared_ptr <Student>> registeredStudents;
	vector <shared_ptr <Assignment>> assignments;
};

extern vector <shared_ptr <Course>> courses;

// Dector methods
void createCourse(shared_ptr <Doctor> thisDoctor);
void deleteCourse(shared_ptr <Course> thisCourse);

// Student method
void registerCourses(shared_ptr <Student> thisStudent);
void unregisterCourse(shared_ptr <Student> thisStudent, int courseIndex);
vector <shared_ptr <Course>> getUnregistedCourses(vector <shared_ptr <Course>> registedCourses);

// Common methods
void listCourses(vector <shared_ptr <Course>> myCourses);
int viewCourse(vector <shared_ptr <Course>> myCourses);

#endif
