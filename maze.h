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
    maze(); // Constructor
    ~maze(); // Destructor

    void generate(int x, int y); // Generates grid
    void DFS(); 
    void BFS();
    void print(); // Prints maze
private:
    bool isVisitable(int x, int y);

    struct node // A structure representing each cell in the maze
    {
        node();
        bool visited;
        bool bot;
        bool right;
        bool top;
        bool left;

        node* next;

        char graphic;
    };

    struct coord {
        int x;
        int y;
    };
    std::vector<coord> getNeighbours(int x, int y);
    bool checkSubNeighbours(int x, int y);
    bool isBorder(int x, int y);
    std::vector<std::vector<node>> grid; // Container to store all the nodes
    node* s; // Start cell
    node* e; // End cell
};

#endif