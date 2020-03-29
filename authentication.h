#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "doctor.h"
#include "student.h"
#include "./sha256/sha256.h"


void signUp(int role);
void signIn(int role);

void loginMenu(int role, string username);

bool verifyDoctorData(string username, string password);
bool verifyStudentData(string username, string password);

// Create a user based on his type and return pointer to his data
template <typename Type>
shared_ptr <Type> addUserInfo(Person info) {
    shared_ptr <Type> newUser (new Type);
    newUser->info = info;
    return newUser;
}

#endif