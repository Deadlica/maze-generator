#include <iostream>
#include "maze.h"
#include "menu.h"

int main() {
    srand(time(0));
    system("clear"); // Clears terminal
    printMenu(); // Print the menu
    while(menuChoice()) { ; }

    return 0;
}