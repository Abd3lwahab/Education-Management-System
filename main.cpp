#include "helper.h"
#include "authentication.h"

int main() {
	cout <<"\n* Welcome in Educational Management System Project *\n";

	startMethod();
	mainMenu();
	exitMethod();
}

int mainMenu() {
	int role = -1;
	while (role) {
		vector <string> menu = {"Doctor", "Student", "Exit"};
		viewMenu(menu);

		role = getInt(0,2);
		if (role) userMethod(role);
	}
}

int userMethod(int role) {
	int method = -1;
	while (method) {
		vector <string> menu = {"Sign Up", "Sign In", "Back"};
		viewMenu(menu);

		method = getInt(0,2);
		if (method == 1)
			signUp(role);
		else if (method == 2)
			signIn(role);
	}
}