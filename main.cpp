#include <iostream>

#include "MenuHandler.h"
#include "StudentManager.h"

int main() {
    StudentManager manager;
    MenuHandler menu(manager);

    //Student info is loaded once upon application start
    manager.loadFromFile("students.txt");
    menu.displayMenu();

    return 0;
}
