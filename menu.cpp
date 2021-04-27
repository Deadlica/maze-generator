#include "menu.h"
#include "maze.h"

void printMenu() { // Printing menu
    std::cout << "=====================================================" << std::endl <<
    "Maze Program" << std::endl <<
    "=====================================================" << std::endl <<
    "1. Generate Maze" << std::endl <<
    "2. DFS Solver" << std::endl <<
    "3. BFS Solver" << std::endl <<
    "4. Quit" << std::endl;
}

bool menuChoice() { // Menu system
    std::string choice = userInput(); // Makes sure userinput is a valid option

    if(choice == "1"){ // Generates a maze
        system("clear");
        std::cout << "=====================================================" << std::endl <<
        "Generate Maze" << std::endl << 
        "=====================================================" << std::endl;

        maze myMaze;
        int x = getMazeSize(0); // Gets width of maze from user
        int y = getMazeSize(1); // Gets height of maze from user
        std::cin.ignore();
        myMaze.generate(x, y); // Builds a grid of given width, height
        //myMaze.print(); // Prints maze


        //Makes user interface cleaner
        resetGUI();
    }

    else if(choice == "2"){ // Generates a maze and solves it with Depth-First search
        system("clear");
        std::cout << "=====================================================" << std::endl <<
        "DFS Solver" << std::endl << 
        "=====================================================" << std::endl;

        //Makes user interface cleaner
        resetGUI();
    }

    else if(choice == "3"){ // Generates a maze and solves it with Breadth-First search
        system("clear");
        std::cout << "=====================================================" << std::endl <<
        "BFS Solver" << std::endl << 
        "=====================================================" << std::endl;

        //Makes user interface cleaner
        resetGUI();
    }

    else if(choice == "4"){ // Terminates the program
        system("clear");
        std::cout << "Exiting Maze Program." << std::endl;
        return false;
    }

    return true;
}

void resetGUI() {
    std::cout << "Press ENTER to return to main menu... ";
    std::cin.get();
    system("clear");
    printMenu();
}

std::string userInput() { // Gets a user input for the menu options
    std::string choice;
    bool badInput = true;
    while(badInput) {
        getline(std::cin, choice); // Gets input
        if(choice == "1" || choice == "2" || choice == "3" || choice == "4") { // Checking if it's valid
            badInput = false;
        }
        else { // Bad input
            std::cerr << "Invalid menu command!" << std::endl <<
            "Try Again!" << std::endl;
        }
    }
    return choice;
}

int getMazeSize(int check) { // Get a size for maze width or height
    if(check == 0) { // Checks if it's asking for width or height to adjust the cout accordingly
    std::cout << "Please specify a width for the maze: ";
    }
    else {
        std::cout << "Please specify a height for the maze: ";
    }
    int x = 3; // Gives x a valid option to ignore the first if statement once
    do {
        if(x % 2 == 0 || x <= 1) { // Given number is invalid
            std::cerr << "Invalid size given, it needs to be an odd number greater than 1." << std::endl <<
            "Try again: ";
        }
        std::cin >> x;
        while(std::cin.fail()) { // Input isn't a number
            std::cerr << "ERROR" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> x;
        }
    } while(x % 2 == 0 || x <= 1); // Repeat if given number is invalid
    
    return x;
}