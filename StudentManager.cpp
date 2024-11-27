//
// Created by mattd on 2024-11-23.
//

#include "StudentManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

//Destructor method to free allocated memory
StudentManager::~StudentManager() {
    for (auto student : students) {
      delete student; //Free memory
    }
}

//Simply adds a student to the end of the students vector
void StudentManager::addStudent(const Student &student) {
  students.push_back(new Student(student));
}

//Retrieves and prints all student details
void StudentManager::printAllStudents() const{
  for (const auto *student : students) {
    cout << "Name: " << student -> lastName << ", " << student -> firstName << endl
    << "Student Number: " << student -> studentNumber << endl
    << "Grades: Midterm 1: " << student -> midterm1 << ", Midterm 2: " << student -> midterm2
    << ", Final: " << student -> finalExam << endl
    << "Final Grade: " << (student -> midterm1 * weightMidterm1) + (student -> midterm2 * weightMidterm2) + (student -> finalExam * weightFinal) << endl << endl;
  }
}

//File is CSV .txt file, data is comma separated with one student per line
void StudentManager::saveToFile(const string &filename) const {
  try {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
      throw ios_base::failure("File could not be opened for writing");
    }

    for (const auto *student : students) {
      outFile << student->firstName << "," << student->lastName << "," << student->studentNumber << ","
      << student->midterm1 << "," << student->midterm2 << "," << student->finalExam << endl;
    }
    outFile.close();
    cout << "Saved file successfully." << endl;
  } catch (const ios_base::failure &e) {
      cerr << "File operation failed: " << e.what() << endl;
  }catch (const exception &e) {
    cerr << "Unexpected error has occurred: " << e.what() << endl;
  }
}

//Reads data from CSV text file, then creates student objects in the students array
void StudentManager::loadFromFile(const string &filename) {
  try {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
      throw ios_base::failure("File could not be opened for reading");
    }

    clearAllStudents();

    string line;
    while (getline(inFile, line)) {
      istringstream lineStream(line);
      string firstName, lastName, studentNumber;
      double midterm1, midterm2, finalExam;

      //Parse the line using commas as delimiter
      if (getline(lineStream, firstName, ',') &&
          getline(lineStream, lastName, ',') &&
          getline(lineStream, studentNumber, ',') &&
          lineStream >> midterm1 && lineStream.ignore(1, ',') &&
          lineStream >> midterm2 && lineStream.ignore(1, ',') &&
          lineStream >> finalExam) {
        addStudent(Student(firstName, lastName, studentNumber, midterm1, midterm2, finalExam));
          } else {
            cerr << "Error parsing line: " << line << "\n";
          }
    }
    inFile.close();
  } catch (const ios_base::failure &e) {
    cerr << "File operation failed: " << e.what() << endl;
  } catch (const exception &e) {
    cerr << "Unexpected error has occurred: " << e.what() << endl;
  }
}

//Sorts students by last name, then first name.
void StudentManager::sortStudents() {
  sort(students.begin(), students.end(), [](const Student *s1, const Student *s2) {
    if (s1->lastName < s2->lastName) {
      return s1->firstName < s2->firstName;
    }
    return s1->lastName < s2->lastName;
  });
}

//Removes the student by student number if it is present.
void StudentManager::removeStudent(const string &studentNumber) {
  auto it = remove_if(students.begin(), students.end(), [&studentNumber](const Student *student) {
    if (student->studentNumber == studentNumber) {
      delete student;
      return true;
    }
    return false;
  });

  students.erase(it, students.end());
}

//Removes all data from the students vector
void StudentManager::clearAllStudents() {
  for (auto student : students) {
    delete student;
  }
  students.clear();
}

//Prints the information for a student, specified by student number.
void StudentManager::printStudentDetails(const string &studentNumber) const {
  auto it = find_if(students.begin(), students.end(), [&studentNumber](const Student *student) {
    return student->studentNumber == studentNumber;
  });
  if (it != students.end()) {
    const auto *student = *it;
    cout << "Name: " << student->lastName << ", " << student->firstName << endl
    << "Student Number: " << student->studentNumber << endl
    << "Grades: Midterm 1: " << student -> midterm1 << ", Midterm 2: " << student -> midterm2
    << ", Final: " << student -> finalExam << endl
    << "Final Grade: " << (student -> midterm1 * weightMidterm1) + (student -> midterm2 * weightMidterm2) + (student -> finalExam * weightFinal) << endl;
  } else {
    cout << "Student not found." << endl;
  }
}


//Default grade weights, allows them to be changed
//Consider saving this in a file, for persistence
double weightMidterm1 = 0.25;
double weightMidterm2 = 0.25;
double weightFinalExam = 0.5;
void StudentManager::setGradeWeights(double w1, double w2, double wFinal) {
  weightMidterm1 = w1;
  weightMidterm2 = w2;
  weightFinal = wFinal;
}

//Get method, used for changeStudentInformation()
const vector<Student *> &StudentManager::getStudents() const {
  return students;
}

//Prints all students name, #, final grade and letter grade.
void StudentManager::calculateGrades() const{
  for (const auto *student : students) {
    double finalGrade = (student -> midterm1 * weightMidterm1) + (student -> midterm2 * weightMidterm2) + (student -> finalExam * weightFinal);

    char letterGrade;
    if (finalGrade > 90) {
      letterGrade = 'A';
    } else if (finalGrade > 80) {
      letterGrade = 'B';
    } else if (finalGrade > 70) {
      letterGrade = 'C';
    } else if (finalGrade > 60) {
      letterGrade = 'D';
    } else {
      letterGrade = 'F';
    }

    cout << "Name: " << student -> lastName << ", " << student -> firstName << endl
    << "Student Number: " << student -> studentNumber << endl
    << "Final Grade: " << finalGrade << endl
    << "Letter Grade: " << letterGrade << endl << endl;
  }
}