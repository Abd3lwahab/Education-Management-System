#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <limits>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::fstream;
using std::shared_ptr;
using std::numeric_limits;
using std::streamsize;

// Forward declaration
struct Person;
struct Doctor;
struct Student;
struct Course;
struct Assignment;
struct AssignmentSolution;

struct Person
{
	int id;
	string username;
	string fullName;
	string email;
	string hashpassword;
};

// Main Functions
int mainMenu();
int userMethod(int role);
void startMethod();
void exitMethod();

// Comman Functions
int getIndex(int role, string username);
int createID(int role);
int getInt(int from, int to);
void viewMenu(vector <string> menu);

#endif