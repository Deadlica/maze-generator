#include "maze.h"

maze::maze() {
    s = nullptr;
    e = nullptr;
}

maze::~maze() {
    std::vector<std::vector<node>>::iterator row;
    std::vector<node>::iterator column;
    for(row = grid.begin(); row != grid.end(); row++) {
        for(column = row->begin(); column != row->end(); column++) {

        }
    }  
}

void maze::generate(int x, int y) {
    for(int i = 0; i < y; i++) {
        std::vector<node> gridRow;
        for(int j = 0; j < x; j++) {
            node* n = new node;
            gridRow.push_back(*n);
        }
        grid.push_back(gridRow);
    }
}

void maze::DFS() {
    std::stack<node*> stack;
    s = &(grid[0][1]);
    node* n = s;
    n->visited = true;
    stack.push(n);
    while(!stack.empty()) {
        n = stack.top();
        
    }
    
}

void maze::BFS() {

}

void maze::print() {
    std::vector<std::vector<node>>::iterator row;
    std::vector<node>::iterator column;
    for(row = grid.begin(); row != grid.end(); row++) {
        for(column = row->begin(); column != row->end(); column++) {
            std::cout << column->graphic;
        }
        std::cout << std::endl;
    }
}

maze::node::node() {
    visited = false;

    next = nullptr;

    graphic = '#';
}