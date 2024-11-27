//
// Created by mattd on 2024-11-24.
//

#include "MenuHandler.h"
#include <iomanip>
#include <limits>

MenuHandler::MenuHandler(StudentManager &manager) : manager(manager) {}

//Prints the main menu and takes user input
void MenuHandler::displayMenu() {
    int choice;
    do {
        cout << "---------------------------------------------" << endl;
        cout << "1) Print all Student data" << endl;
        cout << "2) Sort the list of students in alphabetical order of last name" << endl;
        cout << "3) Add a new student" << endl;
        cout << "4) Calculate the letter grade of all students" << endl;
        cout << "5) Change the information of a previous student" << endl;
        cout << "6) Print the data of a specific student" << endl;
        cout << "7) Remove a student from the list" << endl;
        cout << "8) Delete ALL student data" << endl;
        cout << "9) Change grading scheme" << endl;
        cout << "10) Exit" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 10." << endl;
            continue;
        }

        switch (choice) {
            case 1: printAllStudents(); break;
            case 2: sortStudents(); break;
            case 3: addNewStudent(); break;
            case 4: calculateLetterGrades(); break;
            case 5: changeStudentInformation(); break;
            case 6: printSpecificStudent(); break;
            case 7: removeStudent(); break;
            case 8: deleteAllStudents(); break;
            case 9: changeGradingScheme(); break;
            case 10: cout << "Exiting program."; exit(0);
            default: cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice !=10);
}

//Prints all students and their information
void MenuHandler::printAllStudents() {
    cout << "Printing all students: " << endl;
    manager.printAllStudents();
}

//Sorts students by last name, first name
void MenuHandler::sortStudents() {
    cout << "Sorting students by last name, first name..." << endl;
    manager.sortStudents();
    manager.saveToFile("students.txt");
    cout << "Students have been sorted." << endl;
}


//Add a new student with the specified information
void MenuHandler::addNewStudent() {
    string firstName, lastName, studentNumber;
    double midterm1, midterm2, finalExam;

    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;

    //Student number must be unique, check if it already exists
    while (true) {
        cout << "Enter student number: ";
        cin >> studentNumber;

        bool exists = false;
        for (const auto *student : manager.getStudents()) {
            if (student->studentNumber == studentNumber) {
                cout << "Error: A student with this number already exists." << endl;
                exists = true;
                break;
            }
        } if (!exists) {
            break;
        }
    }

    cout << "Enter midterm 1 grade: ";
    cin >> midterm1;
    cout << "Enter midterm 2 grade: ";
    cin >> midterm2;
    cout << "Enter final exam grade: ";
    cin >> finalExam;

    manager.addStudent(Student(firstName, lastName, studentNumber, midterm1, midterm2, finalExam));
    manager.saveToFile("students.txt");
    cout << "Student added successfully. Data Saved." << endl;
}

//Prints student info with letter grades
void MenuHandler::calculateLetterGrades() {
    cout << "Calculating grades of all students." << endl;
    manager.calculateGrades();
}

//Allows user to modify student grades
void MenuHandler::changeStudentInformation() {
    string studentNumber;
    cout << "Enter the student number of the student you wish to modify: ";
    cin >> studentNumber;

    Student* targetStudent = nullptr;
    for (auto* student : manager.getStudents()) {
        if (student->studentNumber == studentNumber) {
        targetStudent = student;
            break;
        }
    }

    if (!targetStudent) {
        cout << "Error: No student found with student number: " << studentNumber << endl;
        return;
    }

    cout << "Details of student: " << endl;
    manager.printStudentDetails(studentNumber);

    double newMidterm1, newMidterm2, newFinalExam;

    cout << "Enter midterm 1 grade: ";
    cin >> newMidterm1;
    cout << "Enter midterm 2 grade: ";
    cin >> newMidterm2;
    cout << "Enter final exam grade: ";
    cin >> newFinalExam;

    targetStudent->setMidterm1(newMidterm1);
    targetStudent->setMidterm2(newMidterm2);
    targetStudent->setFinalExam(newFinalExam);
    manager.saveToFile("students.txt");
    cout << "Modification successful.";
}

//Verifies student exists, prints student information
void MenuHandler::printSpecificStudent() {
    string studentNumber;
    while (true) {
        cout << "Enter student number: ";
        cin >> studentNumber;

        bool exists = false;
        for (const auto *student : manager.getStudents()) {
            if (student->studentNumber == studentNumber) {
                exists = true;
                break;
            }
        } if (exists) {
            manager.printStudentDetails(studentNumber);
            break;
        } cout << "Error: No student found with student number: " << studentNumber << endl; //Implicit else
    }

}

//Remove the specified student, by student number
void MenuHandler::removeStudent() {
    string studentNumber;
    char userConfirmation;
    cout << "Enter student number to remove: ";
    cin >> studentNumber;

    bool exists = false;
    for (const auto *student : manager.getStudents()) {
        if (student->studentNumber == studentNumber) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        cout << "Student not found." << endl;
        return;
    }

    manager.printStudentDetails(studentNumber);
    cout << "Are your sure you want to remove student #" << studentNumber << "? (y/n): ";
    cin >> userConfirmation;
    if (userConfirmation == 'y') {
        manager.removeStudent(studentNumber);
        manager.saveToFile("students.txt");
        cout << "Student removed successfully." << endl;
    } else {
        cout << "Operation canceled." << endl;
    }
}

//Clears all students from memory and saves a blank text file (overwrite student info file)
void MenuHandler::deleteAllStudents() {
    cout << "WARNING this will delete ALL student data." << endl;
    cout << "Are you sure you want to delete ALL student data? (y/n): ";
    char userConfirmation;
    cin >> userConfirmation;

    if (userConfirmation == 'y') {
        manager.clearAllStudents();
        manager.saveToFile("students.txt");
        cout << "Student data deleted successfully." << endl;
    } else {
        cout << "Operation canceled." << endl;
    }
}

//Allows the user to change the weights for grading
void MenuHandler::changeGradingScheme() {
    cout << "The default grading scheme is: " << endl
    << "Midterm 1: 25%, Midterm2: 25%, Final: 50%" << endl;

    cout << "Do you want to change the grading scheme? (y/n): ";
    char userConfirmation;
    cin >> userConfirmation;

    if (userConfirmation == 'y') {
        int weightM1, weightM2, weightFinal;
        cout << "Enter new weight for Midterm 1: ";
        cin >> weightM1;
        cout << "Enter new weight for Midterm 2: ";
        cin >> weightM2;
        cout << "Enter new weight for Final Exam: ";
        cin >> weightFinal;

        if (weightM1 + weightM2 + weightFinal == 100) {
            manager.setGradeWeights(weightM1 / 100.0, weightM2 / 100.0, weightFinal / 100.0);
            cout << "Grade weight changed successfully." << endl;
        } else {
            cout << "Error. Grading weights must sum to 100%. Please try again." << endl;
        }
    } else {
        cout << "Operation canceled." << endl;
    }
}