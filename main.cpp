#include <iostream>
#include <unistd.h>
#include "maze.h"
#include "menu.h"
#include "maze_txt.h"

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
        std::vector<std::string> tempMaze;
        std::string mazeRow;
        while(getline(std::cin, mazeRow)) { // Get all maze rows
            tempMaze.push_back(mazeRow);
        }

        if(checkMazeFile(tempMaze)) {
            int x = getMazeFileWidth(tempMaze);
            int y = getMazeFileHeight(tempMaze);
            maze myMaze;
            myMaze.generateFromFile(x, y, tempMaze);
            myMaze.BFS();
            myMaze.printBFS();
        }
        else {
            std::cout << "Invalid maze file given" << std::endl;
        }
    }
    else {
        printMenu(); // Print the menu
        while(menuChoice()) { ; }
    }

    return 0;
}