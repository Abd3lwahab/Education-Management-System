#include "authentication.h"

void signUp(int role) {
    Person info;
    string password;
	cout << "\nPlease enter the following information:\n";

	cout << "Full Name: ";
	getline(cin >> ws, info.fullName);

	cout << "E-mail: ";
	cin >> info.email;

	cout << "Username: ";
	cin >> info.username;

	cout << "Password: ";
	cin >> password;

    info.id = createID(role);
    info.hashpassword = sha256(password);

    // Check if this user already exist
    if (role == 1 && !verifyDoctorData(info.username, password)) {
        shared_ptr <Doctor> newDoctor = addUserInfo<Doctor>(info);
        doctors.push_back(newDoctor);
    }
    else if (role == 2 && !verifyStudentData(info.username, password)) {
        shared_ptr <Student> newStudent = addUserInfo<Student>(info);
        students.push_back(newStudent);
    } else {
        cout << "This user already exist\n";
        return;
    }
    
    // User created successfully
    loginMenu(role, info.username);
}

void signIn(int role) {
    string username, password;

	cout << "Username: ";
	cin >> username;

	cout << "Password: ";
	cin >> password;

    // Verify username and password
    if (role == 1 && verifyDoctorData(username, password)) {
        loginMenu(role, username);
    }
    else if (role == 2 && verifyStudentData(username, password)) {
        loginMenu(role, username);
    } else {
        cout << "Username or Password Incorect\n";
    }

}

// Search in doctors vector
bool verifyDoctorData(string username, string password) {
    for (auto doctor: doctors) {
        if (username == doctor->info.username && sha256(password) == doctor->info.hashpassword) {
            return true;
        }
    }
    return false;
}

// Search in students vector
bool verifyStudentData(string username, string password) {
    for (auto student: students) {
        if (username == student->info.username && sha256(password) == student->info.hashpassword) {
            return true;
        }
    }
    return false;
}

// Show login menu for cuurent user
void loginMenu(int role, string username) {
    cout << "\nWelcome " << username << " you are logged in\n";
	if (role == 1) 
		doctorMenu(getPointerDoctor(getIndex(role, username)));
	else if (role == 2) 
		studentMenu(getPointerStudent(getIndex(role, username)));
}