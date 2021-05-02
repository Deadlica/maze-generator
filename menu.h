/*
Samuel Greenberg
02/05/2021
DT019G
Labyrint Projekt
Siktar på betyget A
*/

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <ctype.h>
#include <vector>

void printMenu(); // Prints GUI menu
bool menuChoice(); // Menu options to execute
void GenerateMaze(); // Generates a maze
void DFSSOLVER(); // Generates and solves a maze with dfs
void BFSSOLVER(); // Generates and solves a maze with bfs

std::string sizeOptions();
std::string userInput(); // Getting menu input from user
int getMazeSize(int check); // Gets size for maze to create
void resetGUI(); // Clears the GUI

#endif