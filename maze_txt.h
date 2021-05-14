/*
Samuel Greenberg
02/05/2021
DT019G
Labyrint Projekt
Siktar på betyget A
*/

#ifndef MAZETXT_H
#define MAZETXT_H

#include <iostream>
#include <vector>

bool checkMazeFile(const std::vector<std::string> tempMaze); // Validates the maze.txt file
bool checkMazeSize(const std::vector<std::string> tempMaze); // Validates the maze size
bool checkMazeBorder(const std::vector<std::string> tempMaze); // Validates the maze border graphics
bool checkMazeGraphics(const std::vector<std::string> tempMaze); // Validates the rest of the maze graphics
bool validWallChar(char graphic); // Compares a char to all allowed chars in a maze

int getMazeFileWidth(const std::vector<std::string> tempMaze); // Returns the maze width
int getMazeFileHeight(const std::vector<std::string> tempMaze); // Returns the maze height

#endif