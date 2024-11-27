//
// Created by mattd on 2024-11-23.
//

#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include <vector>

using namespace std;

class StudentManager {
private:
 vector<Student*> students; //Vector of student pointers, for dynamic allocation
 double weightMidterm1 = 0.25, weightMidterm2 = 0.25, weightFinal = 0.50;

public:
  ~StudentManager();

    void addStudent(const Student &student);
    void printAllStudents() const;
    void saveToFile(const string &filename) const;
    void loadFromFile(const string &filename);
    void sortStudents();
    void removeStudent(const string &studentNumber);
    void clearAllStudents();
    void printStudentDetails(const string &studentNumber) const; //TODO - Check if name or student # is wanted
    void setGradeWeights(double weightMidterm1, double weightMidterm2, double weightFinal);
    const vector<Student*>& getStudents() const;
    void calculateGrades() const;
};



#endif //STUDENTMANAGER_H
