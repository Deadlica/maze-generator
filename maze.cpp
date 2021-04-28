#include "maze.h"

maze::maze() {
    s = nullptr;
    e = nullptr;
}

maze::~maze() {
    std::vector<std::vector<node>>::iterator row;
    std::vector<node>::iterator column;
    /*for(row = grid.end(); row != grid.begin(); row++) {
        for(column = row->end(); column != row->begin(); column++) {
            node* s = &(*column);
        }
    }  */
}

void maze::generate(int x, int y) {
    for(int i = 0; i < y; i++) { // Iterator through row
        std::vector<node> gridRow;
        for(int j = 0; j < x; j++) { // Iterate through columns
            node* n = new node;
            if(i == 0 || i == (y - 1) || j == 0 || j == (x - 1)) { //Checks if it's outer walls
                n->visited = true;
            }
            gridRow.push_back(*n);
        }
        grid.push_back(gridRow);
    }
    DfsGenerator(); // Grid done, now filling paths
    setEndCell(); // Sets goal cell
    setWallsVisited();
    system("clear");
    print();
}

void maze::DfsGenerator() {
    std::stack<coord> stack;
    std::vector<coord> neighbours;
    int x = setStartCell();
    s = &grid[0][x];
    s->graphic = 's';
    coord n;
    stack.push({x, 0});
    while(!stack.empty()) {
        n = stack.top();
        neighbours = getNeighbours(n.x, n.y, 1); //Gets visitable neighbour coords
        if(!neighbours.empty()) {
            int index = rand() % neighbours.size(); // Chooses a random neigbour
            coord neighbour = neighbours[index];
            // Updates the visited neighbours info
            grid[neighbour.y][neighbour.x].graphic = ' ';
            grid[neighbour.y][neighbour.x].visited = true;
            stack.push(neighbour);
            system("clear");
            print();
            system("sleep 0.01s");
        }
        else { // No visitable neighbours
            stack.pop();
        }
    }
}

void maze::setWallsVisited() {
    for(int y = 0; y < grid.size(); y++) {
        for(int x = 0; x < grid[0].size(); x++) {
            if(grid[y][x].graphic == '#') {
                grid[y][x].visited = true;
            }
        }
    }
}

void maze::DFS() {
    UnvisitAllCells();
    std::stack<coord> stack;
    std::vector<coord> neighbours;
    coord n;
    coord endCell;
    n.y = 0;
    n.x = findStartCellX();
    endCell.y = grid.size() - 1;
    endCell.x = findEndCellX();
    grid[endCell.y][endCell.x].visited = false;
    stack.push({n.x, n.y});
    while(!stack.empty()) {
        n = stack.top();
        grid[n.y][n.x].visited = true;
        if(n.x == endCell.x && n.y == endCell.y) {
            grid[endCell.y][endCell.x].graphic = '*';
            stack.push({n.x, n.y});
            break;
        }
        neighbours = getNeighbours(n.x, n.y, 0);
        if(!neighbours.empty()) {
            stack.push(n);
            for(int i = 0; i < neighbours.size(); i++) {
                stack.push(neighbours[i]);
            }
            grid[n.y][n.x].graphic = '*';
        }
        else {
            grid[n.y][n.x].graphic = ' ';
            stack.pop();
        }
        system("clear");
        print();
        system("sleep 0.01s");
    }
    system("clear");
    print();
    if(stack.empty()) {
        std::cout << "There are no solutions to this maze!" << std::endl;
    }
}

void maze::BFS() {

}

void maze::UnvisitAllCells() {
    for(int y = 0; y < grid.size(); y++) {
        for(int x = 0; x < grid[0].size(); x++) {
            if(grid[y][x].graphic == ' ' || grid[y][x].graphic == 's' || grid[y][x].graphic == 'e') {
                grid[y][x].visited = false;
            }
        }
    }
}

int maze::findStartCellX() {
    int x;
    for(x = 0; x < grid[0].size(); x++) {
        if(grid[0][x].graphic == 's') {
            return x;
        }
    }
    return x;
}

int maze::findEndCellX() {
    int x;
    for(x = 0; x < grid[0].size(); x++) {
        if(grid[grid.size() - 1][x].graphic == 'e') {
            return x;
        }
    }
    return x;
}

int maze::setStartCell() {
    int xCoord = 1 + rand() % (grid[0].size() - 2); // Generate random x-axis number of maze
    return xCoord;
}

void maze::setEndCell() { // Looks for a visited cell as close to bottom right corner as possible
    int y = grid.size() - 2;
    for(int x = grid[0].size() - 2; e == nullptr; x--) {
        if(grid[y][x].graphic == ' ') { // Finds visited cell
            // Sets end cell
            e = &grid[y + 1][x];
            e->visited = true;
            e->graphic = 'e';
        }
    }
}

std::vector<maze::coord> maze::getNeighbours(int x, int y, int check) {
    std::vector<coord> neighbours;

    // Checks if cell in all directions are visitable and also
    // if the neigbour has 3 or more visitable cells
    if(check == 1) {
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
    }
    else {
        if(isVisitable(x + 1, y)) {
            neighbours.push_back({x + 1, y});
        }
        if(isVisitable(x - 1, y)) {
            neighbours.push_back({x - 1, y});
        }
        if(isVisitable(x, y + 1) || grid[y + 1][x].graphic == 'e') {
            neighbours.push_back({x, y + 1});
        }
        if(isVisitable(x, y - 1)) {
            neighbours.push_back({x, y - 1});
        }
    }
    return neighbours;
}

bool maze::checkSubNeighbours(int x, int y) {
    int numVisitable = 0;

    // If subneighbours are all visited then the maze wouldnt
    // "maze" lookin walls.

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
    // If x or y coordinate is at border
    if(x == 0 || x == grid[0].size() - 1 || y == grid.size() - 1 || y == 0) {
        return true;
    }
    else { // Not border
        return false;
    }

}

bool maze::isVisitable(int x, int y) {
    // Checks if coords are outside of the maze
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

    graphic = '#';
}