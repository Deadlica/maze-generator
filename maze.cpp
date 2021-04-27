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
            if(i == 0 || i == (y - 1) || j == 0 || j == (x - 1)) {
                n->graphic = '#';
                n->visited = true;
            }
            gridRow.push_back(*n);
        }
        grid.push_back(gridRow);
    }
    DFS();
}

void maze::DFS() {
    std::stack<coord> stack;
    std::vector<coord> neighbours;
    coord n;
    stack.push({0, 1});
    while(!stack.empty()) {
        n = stack.top();
        neighbours = getNeighbours(n.x, n.y);
        if(!neighbours.empty()) {
            int index = rand() % neighbours.size();
            coord neighbour = neighbours[index];
            grid[neighbour.y][neighbour.x].graphic = ' ';
            grid[neighbour.y][neighbour.x].visited = true;
            stack.push(neighbour);
            system("clear");
            print();
            system("sleep 0.01s");
        }
        else {
            stack.pop();
        }
    }
    
}

void maze::BFS() {

}

std::vector<maze::coord> maze::getNeighbours(int x, int y) {
    std::vector<coord> neighbours;
    if(isVisitable(x + 1, y) && checkSubNeighbours(x + 1, y)) {
        neighbours.push_back({x + 1, y});
    }
    if(isVisitable(x - 1, y) && checkSubNeighbours(x - 1, y)) {
        neighbours.push_back({x - 1, y});
    }
    if(isVisitable(x, y + 1) && checkSubNeighbours(x, y + 1)) {
        neighbours.push_back({x, y + 1});
    }
    if(isVisitable(x, y - 1) && checkSubNeighbours(x, y - 1)) {
        neighbours.push_back({x, y - 1});
    }
    return neighbours;
}

bool maze::checkSubNeighbours(int x, int y) {
    int numVisitable = 0;
    if(isVisitable(x + 1, y) || isBorder(x + 1, y)) {
        numVisitable++;
    }
    if(isVisitable(x - 1, y) || isBorder(x - 1, y)) {
        numVisitable++;
    }
    if(isVisitable(x, y + 1) || isBorder(x, y + 1)) {
        numVisitable++;
    }
    if(isVisitable(x, y - 1) || isBorder(x, y - 1)) {
        numVisitable++;
    }
    return numVisitable > 2;
}

bool maze::isBorder(int x, int y) {
    if(x == 0 || x == grid[0].size() - 1 || y == grid.size() - 1 || y == 0) {
        return true;
    }
    else {
        return false;
    }

}

bool maze::isVisitable(int x, int y) {
    if(x <= 0 || x >= grid[0].size() - 1 || y <= 0 || y >= grid.size() - 1) {
            return false;
    }
    else if(grid[y][x].visited) {
        return false;
    }
    return true;
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

    graphic = '*';
}