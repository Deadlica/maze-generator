/*
Samuel Greenberg
02/05/2021
DT019G
Labyrint Projekt
Siktar på betyget A
*/

#include "maze_txt.h"

bool checkMazeFile(const std::vector<std::string> tempMaze) {

    if(tempMaze.empty()) {
        return false;
    }
    if(!checkMazeSize(tempMaze)) { // Checks that maze width is okay
        return false;
    }
    if(!checkMazeBorder(tempMaze)) {
        return false;
    }
    if(!checkMazeGraphics(tempMaze)) {
        return false;
    }
    return true;
}

bool checkMazeSize(const std::vector<std::string> tempMaze) {
    size_t rowLength = tempMaze[0].length();
    if(tempMaze.size() % 2 == 0 || tempMaze.size() < 3 || rowLength % 2 == 0 || rowLength < 3) { // Size is even number
    std::cout << "Invalid maze size" << std::endl;
        return false;
    }

    for(auto it : tempMaze) {
        if(it.length() != rowLength) {
            std::cout << "Maze width is invalid" << std::endl;
            return false;
        }
    }
    return true;
}

bool checkMazeBorder(const std::vector<std::string> tempMaze) {
    int E = 0, S = 0;
    for(int i = 1; i < tempMaze[0].length() - 1; i++) { // Looks for s in top row
        if(tempMaze[0][i] == 'S') {
            S++;
        }
    }
    for(int i = 1; i < tempMaze[tempMaze.size() - 1].length() - 1; i++) { // Looks for e in bottom row
        if(tempMaze[tempMaze.size() - 1][i] == 'E') {
            E++;
        }
    }
    if(E == 0 || E > 1 || S == 0 || S > 1) { // if there's no or multiple starts/ends
        return false;
    }
    S = 0;
    E = 0;
    for(int i = 0; i < tempMaze.size(); i++) { // Checks maze border graphics
        if(i == 0 || i == tempMaze.size() - 1) { // Checks top and bottom row
            for(int j = 0; j < tempMaze[i].size(); j++) {
                if(!validWallChar(tempMaze[i][j]) && tempMaze[i][j] != 'S' && tempMaze[i][j] != 'E' || E > 1 || S > 1) {
                    return false;
                }
                if(tempMaze[i][j] == 'E') {
                    E++;
                }
                if(tempMaze[i][j] == 'S') {
                    S++;
                }

            }
        }
        else { // Checks other rows
            if(!validWallChar(tempMaze[i][0]) || !validWallChar(tempMaze[i][tempMaze[i].size() - 1])) {
                return false;
            }
        }
    }
    return true;
}

bool checkMazeGraphics(const std::vector<std::string> tempMaze) {
    for(int y = 1; y < tempMaze.size() - 1; y++) {
        for(int x = 1; x < tempMaze[y].length() - 1; x++) {
            if(!validWallChar(tempMaze[y][x]) && tempMaze[y][x] != ' ') {
                return false;
            }
        }
    }
    return true;
}

int getMazeFileWidth(const std::vector<std::string> tempMaze) {
    return tempMaze[0].length();
}

int getMazeFileHeight(const std::vector<std::string> tempMaze) {
    return tempMaze.size();
}

bool validWallChar(char graphic) {
    if(graphic >= '!' && graphic < 'E' || graphic > 'E' && graphic < 'S' || graphic > 'S' && graphic <= '~') {
        return true;
    }
    return false;
}