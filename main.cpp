#include <iostream>
#include "maze.h"
#include "menu.h"

int main() {
    system("clear"); // Clears terminal
    printMenu(); // Print the menu
    while(menuChoice()) { ; }

    return 0;
}