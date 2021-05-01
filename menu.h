#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <ctype.h>
#include <vector>

void printMenu(); // Prints GUI menu
bool menuChoice(); // Menu options to execute
void GenerateMaze(); // Generates a maze
void DFSSolver(); // Generates and solves a maze with dfs
void BFSSOLVER(); // Generates and solves a maze with bfs

std::string userInput(); // Getting menu input from user
int getMazeSize(int check); // Gets size for maze to create
void resetGUI(); // Clears the GUI

#endif