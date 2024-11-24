//
// Created by mattd on 2024-11-23.
//

#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

struct Student {
    string firstName;
    string lastName;
    string studentNumber;
    double midterm1, midterm2, finalExam;

    Student(const string &firstName, const string &lastName, const string &studentNumber,
            double midterm1, double midterm2, double finalExam);
};



#endif //STUDENT_H
