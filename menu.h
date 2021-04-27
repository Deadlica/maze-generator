#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <ctype.h>

void printMenu(); // Prints GUI menu
bool menuChoice(); // Menu options to execute
std::string userInput(); // Getting menu input from user
int getMazeSize(int check); // Gets size for maze to create
void resetGUI(); // Clears the GUI

#endif