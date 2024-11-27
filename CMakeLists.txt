cmake_minimum_required(VERSION 3.29)
project(final_project_student_information_system_DeagleM902)

set(CMAKE_CXX_STANDARD 20)

add_executable(final_project_student_information_system_DeagleM902 main.cpp
        Student.cpp
        StudentManager.cpp
        MenuHandler.h
        MenuHandler.cpp)
