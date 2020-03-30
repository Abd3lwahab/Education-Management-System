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
	password = getPassword();

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
	cout << "\nPlease enter the following information:\n";

	cout << "Username: ";
	cin >> username;

	cout << "Password: ";
	password = getPassword();

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
    cout << "\n\nWelcome " << username << " you are logged in\n";
	if (role == 1) 
		doctorMenu(getPointerDoctor(getIndex(role, username)));
	else if (role == 2) 
		studentMenu(getPointerStudent(getIndex(role, username)));
}

// Prevent display password on the screen
// It works correctly on Linux not tested on Windows
string getPassword()
{
    // Clear previously entered
    cin.ignore();
    cin .clear();

    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    string password;
    getline(cin, password);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return password;
}