#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <stack>

class maze {
public:
    maze(); // Constructor
    ~maze(); // Destructor

    void generate(int x, int y); // Generates grid
    void DFS(); 
    void BFS();
    void print(); // Prints maze
private:
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
    std::vector<std::vector<node>> grid; // Container to store all the nodes
    node* s; // Start cell
    node* e; // End cell
};

#endif