#include "files-operations.h"

// Pointer functions
void (*loadData) (vector <string> data);
void (*saveData) (fstream &file);

// Load data from files to memory
void importData() {
    readCSVfile("doctors.csv");
	readCSVfile("courses.csv");
	readCSVfile("students.csv");
	readCSVfile("solutions.csv");
    cout << "\nAll data has been loaded successfully....\n";
}

void readCSVfile(string filename) {
    fstream file;
    string fileReName = "./data/" + filename;

    // Open file with relative path
    file.open(fileReName, ios::in);
    if (!file.is_open()) {
        file.close();
        return;
    }

    string line, word, heading;
    vector <string> data;

    // Detect which file will be loaded
    if (filename == "doctors.csv") {
        loadData = &loadDoctor;
    } else if (filename == "courses.csv") {
        loadData = &loadCourse; 
    } else if (filename == "students.csv") {
        loadData = &loadStudent;
    } else if (filename == "solutions.csv") {
        loadData = &loadSolutions;
    }
    
    // Skip heading
    getline(file, heading);
    
    // Read until end of the file
    while(!file.eof()) {
        // Clear previous data
        data.clear();

        // Read line
        getline(file, line);
        stringstream words(line);

        // Sperete the line to strings by dilimiter
        while(getline(words, word, ',')) {
            data.push_back(word);
        }
        
        // Skip empty line
        if (data.size() == 0)
            continue;

        loadData(data);
    }

    file.close();
}

void loadDoctor(vector <string> data){
    // Store doctor info
    Person info = {stoi(data[0]), data[1], data[2], data[3], data[4]};
    shared_ptr <Doctor> newDoctor (new Doctor);
    newDoctor->info = info;

    // Store each course taught by this doctor
    for (int i = 5; i < data.size(); i++) {
        shared_ptr <Course> newCourse (new Course);
        newCourse->code = data[i];
        newCourse->lecturer = newDoctor;
        
        courses.push_back(newCourse);
        newDoctor->courses.push_back(newCourse);
    }

    // Add this doctor to doctors vector
    doctors.push_back(newDoctor);
}

void loadCourse(vector <string> data){
    // Searching for matches with current course code
    for (auto course: courses) {
        if (course->code == data[0]) {
            course->title = data[1];

            // Load assignments in this course
            for (int i = 2; i < data.size(); i += 2) {
                shared_ptr <Assignment> newAssignment (new Assignment);
                
                newAssignment->content = data[i];
                newAssignment->maxMark = stoi(data[i+1]);
                newAssignment->course = course;

                course->assignments.push_back(newAssignment);
            }
            break;
        }
    }
}

void loadStudent(vector <string> data){
    // Store student info
    Person info = {stoi(data[0]), data[1], data[2], data[3], data[4]};
    shared_ptr <Student> newStudent (new Student);
    newStudent->info = info;

    // Store all the courses in which this student is registered
    for (int i = 5; i < data.size(); i++) {
        for (auto course : courses) {
            if (course->code == data[i]) {
                newStudent->courses.push_back(course);
                course->registeredStudents.push_back(newStudent);
                break;
            }
        }
    }
    
    // Add this student to students vector
    students.push_back(newStudent);
}

void loadSolutions(vector <string> data) {
    // Empty pointer declared to point to current student
    shared_ptr <Student> thisStudent (nullptr);
    for (auto student : students) {
        if (stoi(data[0]) == student->info.id) {
            thisStudent = student;
            break;
        }
    }

    // Load solution data
    for (int i = 1; i < data.size(); i += 6) {
        shared_ptr <AssignmentSolution> newSolution (new AssignmentSolution);
        newSolution->student = thisStudent;
        newSolution->isMarked = stoi(data[i]);
        newSolution->solution = data[i+1];
        newSolution->mark = stoi(data[i+2]);
        newSolution->comment = data[i+3];
        // Serching for course assignmnet of this solution
        for (auto course : courses) {
            if (course->code == data[i+4]) {
                for (auto assignment : course->assignments) {
                    if (assignment->content == data[i+5])  {
                        newSolution->assignment = assignment;
                        assignment->assignmentSolutions.push_back(newSolution);
                        break;
                    }
                }
                break;
            }
        }
        // Store previous solution
        thisStudent->assignmentSolutions.push_back(newSolution);
    }
}

// Save data from memory to files
void exportData() {
	saveCSVfile("doctors.csv");
	saveCSVfile("courses.csv");
	saveCSVfile("students.csv");
	saveCSVfile("solutions.csv");
    cout << "\nAll data has been saved successfully....\n";
}

void saveCSVfile(string filename)
{
    fstream file;
    string fileReName = "./data/" + filename;
    
    // Open file with relative path
    file.open(fileReName, ios::out);
    if (!file.is_open()) {
        return;
    }

    // Detect which file will be saved
    if (filename == "doctors.csv") {
        saveData = &saveDoctors;
    } else if (filename == "courses.csv") {
        saveData = &saveCourses; 
    } else if (filename == "students.csv") {
        saveData = &saveStudents;
    } else if (filename == "solutions.csv") {
        saveData = &saveSolutions;
    }

    saveData(file);

    file.close();
}

void saveDoctors(fstream &file) {
    // Create heading
    file << "id,username,fullname,email,hashpassword,coursescode";

    // Save each doctor in doctors vector
    for (auto doctor : doctors) {
        file<< '\n' << doctor->info.id << "," 
            << doctor->info.username << ","
            << doctor->info.fullName << ","
            << doctor->info.email << ","
            << doctor->info.hashpassword;
        for (auto course : doctor->courses) {
            file<< "," << course->code;
        }
    }
}

void saveCourses(fstream &file) {
    // Creat heading
    file << "code,title,assignments,max-mark";

    // Save each course in courses vector
    for (auto course : courses) {
        file<< '\n' << course->code << ","
            << course->title;

        for (auto assignment : course->assignments) {
            file<< "," << assignment->content
                << "," << assignment->maxMark;
        }
    }
}

void saveStudents(fstream &file) {
    // Create heading
    file << "id,username,fullname,email,hashpassword,corsecode";

    // Save each student in students vector
    for (auto student : students) {
        file<< '\n' << student->info.id << ","
            << student->info.username << ","
            << student->info.fullName << ","
            << student->info.email << ","
            << student->info.hashpassword;
        for (auto course : student->courses) {
            file<< "," << course->code;
        }
    }
}

void saveSolutions(fstream &file) {
    // Create heading
    file << "studentID,isMarked,solution,mark,comment,coursecode,assignment";

    // Save solutions of assigments for each student
    for (auto student : students) {
        file<< '\n' << student->info.id;
        for (auto solution : student->assignmentSolutions) {
            file<< "," << solution->isMarked
                << "," << solution->solution
                << "," << solution->mark
                << "," << solution->comment
                << "," << solution->assignment->course->code
                << "," << solution->assignment->content;
        }
    }
}