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
    void setWallsVisited(); // Checks all walls as visited

    void DFS(); // Depth-first search solver
    void BFS(); // Breadth-first search solver

    void UnvisitAllCells(); // Unvisist paths, 'S', 'E'
    int findStartCellX(); // Returns x coordinate of 'S'
    int findEndCellX(); // Returns x coordinate of 'E'
    int setStartCell(); // Sets a random start cell at top row
    void setEndCell(); // Sets a random end cell as close to bottom right corner

    void printBFS(); // Print BFS solution
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
        coord parent; // Coordinates of previous visited cell
    };

    std::vector<coord> getNeighbours(int x, int y, int check); // Fills vector with coordinates of visitable neighbours
    bool isVisitable(int x, int y); // Checks if cell is visitable
    bool checkSubNeighbours(int x, int y);
    bool isBorder(int x, int y); // Checks if cell is a border cell
    std::vector<std::vector<node>> grid; // Container to store all the nodes
    node* s; // Start cell
    node* e; // End cell
};

#endif