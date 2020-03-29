#ifndef FILESOPERATIONS_H
#define FILESOPERATIONS_H

#include <fstream>
#include <sstream>

#include "helper.h"
#include "doctor.h"
#include "student.h"
#include "course.h"

using std::ios;
using std::stringstream;

// Load Data functions
void importData();
void readCSVfile(string filename);
void loadDoctor(vector <string> data);
void loadCourse(vector <string> data);
void loadStudent(vector <string> data);
void loadSolutions(vector <string> data);

// Save Data functions
void exportData();
void saveCSVfile(string filename);
void saveDoctors(fstream &file);
void saveCourses(fstream &file);
void saveStudents(fstream &file);
void saveSolutions(fstream &file);

#endif
