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
    static bool printToFile;

    void generate(int x, int y); // Generates grid
    void generateFromFile(int x, int y, std::vector<std::string> stringMaze);
    void pathGenerator(const bool generator); // Fills grid with paths
    void BfsGenerator(); // Fills grid with paths using bfs algorithm

    void DFS(); // Depth-first search solver
    void BFS(); // Breadth-first search solver

    void setWallsVisited(); // Checks all walls as visited
    void UnvisitAllCells(); // Unvisist paths, 'S', 'E'

    int randomYCoordinate(); // Returns a random cell Y coordinate
    int randomXCoordinate(); // Returns a random cell X coordinate
    int findStartCellX(); // Returns x coordinate of 'S'
    int findEndCellX(); // Returns x coordinate of 'E'

    int setStartCell(); // Sets a random start cell at top row
    int setEndCell(); // Sets a random end cell at bottom row
    int getMazeWidth(); // Returns maze width
    int getMazeHeight(); // Returns maze height

    void printBFS(); // Print BFS solution
    void print(); // Prints maze

private:
    struct coord { // Coordinate for nodes
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
    bool checkSubNeighbours(int x, int y);

    bool isVisitable(int x, int y); // Checks if cell is visitable
    bool isBorder(int x, int y); // Checks if cell is a border cell
    
    void openPathConnection(coord n, coord neighbour);

    std::vector<std::vector<node>> grid; // Container to store all the nodes
};

#endif