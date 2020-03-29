#include "helper.h"
#include "student.h"
#include "doctor.h"
#include "files-operations.h"
#include "authentication.h"

void startMethod() {
	vector <string> menu = {"Load Data", "Start New"};
	viewMenu(menu);
	if (getInt(0,1) == 1) 
		importData();
}

void exitMethod() {
	vector <string> menu = {"Save and Exit", "Exit without Saving"};
	viewMenu(menu);
	if (getInt(0,1) == 1)
		exportData();
}

// Return index of this username
int getIndex(int role, string username) {
    if (role == 1) {
        for (int i = 0; i < doctors.size(); i++) {
            if (doctors[i]->info.username == username)
                return i;
        }
    } else if (role == 2) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i]->info.username == username)
                return i;
        }
    }

	return -1;
}

// Create ID for each user based on his role by the ASCII of the first and second letters
int createID(int role) {
	if (role == 1)
		return 415000 + doctors.size();
	else if (role == 2)
		return 192000 + students.size();

	return false;
}

// Return integer in range (from:to)
int getInt(int from, int to) {
	int choice;
	cin >> choice;
	int tryNum = 0;
	while (cin.fail() || choice < from || choice > to) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout<< "\nERROR: Out of range, Try again\n"
			<< "Your choice: ";
		cin >> choice;
		
		// Return '0' (Back) if the user input is wrong 4 times
		tryNum++;
		if (tryNum > 3) {
			cout << "\nToo many wrong attempts\n";
			return 0;
		}
	}
	return choice;
}

void viewMenu(vector <string> menu) {
	cout << "\nPlease enter a choice: \n";
	for (int i = 0; i < menu.size(); i++) {
		if (i + 1 != menu.size()) 
			cout << "\t[" << i + 1 << "] ";
		else
			cout << "\t[0] ";
		cout << menu[i] << '\n';
	}
	cout << "Your choice: ";
}