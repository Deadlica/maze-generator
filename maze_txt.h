#ifndef MAZETXT_H
#define MAZETXT_H

#include <iostream>
#include <vector>

bool checkMazeFile(const std::vector<std::string> tempMaze);
bool checkMazeSize(const std::vector<std::string> tempMaze);
bool checkMazeBorder(const std::vector<std::string> tempMaze);
bool checkMazeGraphics(const std::vector<std::string> tempMaze);

int getMazeFileWidth(const std::vector<std::string> tempMaze);
int getMazeFileHeight(const std::vector<std::string> tempMaze);

#endif