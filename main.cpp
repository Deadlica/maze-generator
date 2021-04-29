#include <iostream>
#include <unistd.h>
#include "maze.h"
#include "menu.h"

int main(int argc, char** argv) {
    if(argc > 1) {
        std::string argument;
        argument = argv[1];
        if(argument == "--animate") {
            maze::shouldAnimate = true;
        }
    }
    srand(time(0));
    system("clear"); // Clears terminal
    if(!isatty(STDIN_FILENO)) {
        std::string mazeRow;
        while(getline(std::cin, mazeRow)) {
            std::cout << mazeRow << std::endl;
        }
    }
    else {
        maze::shouldAnimate = true;
        printMenu(); // Print the menu
        while(menuChoice()) { ; }
    }

    return 0;
}