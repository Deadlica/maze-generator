/*
Samuel Greenberg
02/05/2021
DT019G
Labyrint Projekt
Siktar på betyget A
*/

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <stack>
#include <cstdlib>

class maze {
public:
    static bool shouldAnimate;
    maze(); // Constructor
    ~maze(); // Destructor

    void generate(int x, int y); // Generates grid
    void generateFromFile(int x, int y, std::vector<std::string> stringMaze);
    void DfsGenerator(); // Fills grid with paths
    void setWallsVisited();

    void DFS(); // Depth-first search solver
    void BFS(); // Breadth-first search solver

    void UnvisitAllCells();
    int findStartCellX();
    int findEndCellX();
    int setStartCell(); // Sets a random start cell at top row
    void setEndCell(); // Sets a random end cell as close to bottom right corner

    void printBFS();
    void print(); // Prints maze
private:
    struct coord {
        int x;
        int y;
    };

    struct node // A structure representing each cell in the maze
    {
        node();
        bool visited;
        char graphic;
        coord parent;
    };

    std::vector<coord> getNeighbours(int x, int y, int check);
    bool isVisitable(int x, int y);
    bool checkSubNeighbours(int x, int y);
    bool isBorder(int x, int y);
    std::vector<std::vector<node>> grid; // Container to store all the nodes
    node* s; // Start cell
    node* e; // End cell
};

#endif