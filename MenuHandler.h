//
// Created by mattd on 2024-11-24.
//

#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include "StudentManager.h"
#include <iostream>
using namespace std;

class MenuHandler {
private:
    StudentManager &manager;

    void printAllStudents();
    void sortStudents();
    void addNewStudent();
    void calculateLetterGrades();
    void changeStudentInformation();
    void printSpecificStudent();
    void removeStudent();
    void deleteAllStudents();
    void changeGradingScheme();

public:
    MenuHandler(StudentManager &manager);
    void displayMenu();
};
#endif //MENUHANDLER_H
