#include <iostream>
#include <unistd.h>
#include "maze.h"
#include "menu.h"

int main() {
    srand(time(0));
    system("clear"); // Clears terminal
    if(!isatty(STDIN_FILENO)) {

        std::string mazeRow;
        while(getline(std::cin, mazeRow)) {
            std::cout << mazeRow << std::endl;
        }
    }
    else {
        printMenu(); // Print the menu
        while(menuChoice()) { ; }
    }

    return 0;
}