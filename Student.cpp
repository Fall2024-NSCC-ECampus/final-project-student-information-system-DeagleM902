//
// Created by mattd on 2024-11-23.
//

#include "Student.h"

using namespace std;

Student::Student(const string &firstName, const string &lastName, const string &studentNumber,
                 double midterm1, double midterm2, double finalExam)
    : firstName(firstName), lastName(lastName), studentNumber(studentNumber), midterm1(midterm1), midterm2(midterm2), finalExam(finalExam) {}

