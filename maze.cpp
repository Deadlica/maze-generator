/*
Samuel Greenberg
02/05/2021
DT019G
Labyrint Projekt
Siktar på betyget A
*/

#include <unistd.h>
#include "maze.h"

// PUBLIC

bool maze::shouldAnimate = false;
bool maze::printToFile = false;
bool maze::GUI = false;

void maze::generate(int x, int y) {
    for(int i = 0; i < y; i++) { // Iterate through row
        std::vector<node> gridRow;
        for(int j = 0; j < x; j++) { // Iterate through columns
            //node* n = new node;
            gridRow.push_back(node());
        }
        grid.push_back(gridRow);
    }
}

void maze::generateFromFile(int x, int y, std::vector<std::string> stringMaze) {
    generate(x, y);
    for(int y = 0; y < grid.size(); y++) {
        for(int x = 0; x < grid[0].size(); x++) {
            if(stringMaze[y][x] != ' ' && stringMaze[y][x] != 'S' && stringMaze[y][x] != 'E'){ // Sets all walls to '#'
                grid[y][x].graphic = '#';
            }
            else { // Sets paths to ' ' and start, goal to 'S', 'E'
                grid[y][x].graphic = stringMaze[y][x];
            }
        }
    }
    setWallsVisited();
}

void maze::pathGenerator(const bool generator) { // Generates paths in the grid matrix
    if(!generator) {
        BfsGenerator();
        return;
    }
    std::stack<coord> stack;
    std::vector<coord> neighbours;
    int x = setStartCell();
    coord n;
    // Sets a random start coordinate for generation
    n.x = randomXCoordinate();
    n.y = randomYCoordinate();
    grid[n.y][n.x].graphic = ' ';
    grid[n.y][n.x].visited = true;
    stack.push(n);
    while(!stack.empty()) {
        n = stack.top();

        // Gets visitable neighbours
        neighbours = getNeighbours(n.x, n.y, 1);
        if(!neighbours.empty()) {
            int index = rand() % neighbours.size(); // Chooses a random neigbour
            coord neighbour = neighbours[index];
            // Connect, visit neighbour
            openPathConnection(n, neighbour);
            grid[neighbour.y][neighbour.x].graphic = ' ';
            grid[neighbour.y][neighbour.x].visited = true;
            stack.push(neighbour);
            if(shouldAnimate) {
                system("clear");
                print();
                system("sleep 0.01s");
            }
        }
        else { // No visitable neighbours
                stack.pop();
        }
    }
    setEndCell(); // Sets goal cell
    setWallsVisited();
    system("clear");
    print();
}

void maze::BfsGenerator() {
    std::deque<coord> queue;
    std::vector<coord> neighbours;
    int x = setStartCell();
    coord n;

    // Sets a random start coordinate for generation
    n.x = randomXCoordinate();
    n.y = randomYCoordinate();
    grid[n.y][n.x].graphic = ' ';
    grid[n.y][n.x].visited = true;
    queue.push_back(n);
    while(!queue.empty()) {
        // Gets random cell from queue
        int randomElement = rand() % queue.size();
        n = queue.at(randomElement);
        queue.erase(queue.begin() + randomElement);

        // Gets visitable neighbours
        neighbours = getNeighbours(n.x, n.y, 1);
        for(int i = 0; i < neighbours.size();) {
            // Connects n with all neighbours in random order
            int g = rand() % neighbours.size();
            openPathConnection(n, neighbours[g]);
            grid[neighbours[g].y][neighbours[g].x].graphic = ' ';
            grid[neighbours[g].y][neighbours[g].x].visited = true;
            queue.push_back(neighbours[g]);
            neighbours.erase(neighbours.begin() + g);
            if(shouldAnimate) {
                system("clear");
                print();
                system("sleep 0.01s");
            }
        }
    }

    setEndCell(); // Sets goal cell
    setWallsVisited();
    system("clear");
    print();
}

void maze::DFS() { // Finds a solution with depth-first search
    UnvisitAllCells();
    std::stack<coord> stack;
    std::vector<coord> neighbours;
    coord n;
    coord endCell;
    n.y = 0;
    n.x = findStartCellX();
    endCell.y = grid.size() - 1;
    endCell.x = findEndCellX();
    stack.push(n);
    while(!stack.empty()) {
        n = stack.top();
        grid[n.y][n.x].visited = true;
        if(n.x == endCell.x && n.y == endCell.y) { // Reached end
            grid[endCell.y][endCell.x].graphic = '*';
            stack.push(n);
            break;
        }
        neighbours = getNeighbours(n.x, n.y, 0); // Gets visitable neighbours
        if(!neighbours.empty()) {
            stack.push(n);
            for(int i = 0; i < neighbours.size(); i++) { // Adds them to the stack
                stack.push(neighbours[i]);
            }
            grid[n.y][n.x].graphic = '*';
        }
        else {
            grid[n.y][n.x].graphic = ' '; // When backtracking
            stack.pop();
        }
        if(shouldAnimate) {
            system("clear");
            print();
            system("sleep 0.01s");
        }
    }
    system("clear");
    print();
    if(stack.empty()) {
        std::cout << "There are no solutions to this maze!" << std::endl;
    }
}

void maze::BFS() {
    UnvisitAllCells();
    std::deque<coord> queue;
    std::vector<coord> neighbours;
    coord n;
    coord endCell;
    n.y = 0;
    n.x = findStartCellX();
    grid[n.y][n.x].visited = true;
    endCell.y = grid.size() - 1;
    endCell.x = findEndCellX();
    queue.push_back(n);
    while(!queue.empty()) {
        n = queue.front();
        queue.pop_front();
        if(n.x == endCell.x && n.y == endCell.y) { // Reached end
            break;
        }
        neighbours = getNeighbours(n.x, n.y, 0); // Gets visitable neighbours
        for(int i = 0; i < neighbours.size(); i++) { // Add them to the queue, remembers its parent coordinates
            grid[neighbours[i].y][neighbours[i].x].visited = true;
            (grid[neighbours[i].y][neighbours[i].x]).parent = n;
            queue.push_back(neighbours[i]);
        }
    }

    if(grid[endCell.y][endCell.x].parent.x == 0 && grid[endCell.y][endCell.x].parent.y == 0) { // End cell has no parent coords
        std::cout << "There's no solution to this maze." << std::endl;
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

void maze::UnvisitAllCells() { // Unvisits all paths including 'S' and 'E'
    for(int y = 0; y < grid.size(); y++) {
        for(int x = 0; x < grid[0].size(); x++) {
            if(grid[y][x].graphic == ' ' || grid[y][x].graphic == 'S' || grid[y][x].graphic == 'E') {
                grid[y][x].visited = false;
            }
        }
    }
}

int maze::randomYCoordinate() {
    int coordinate = 2;
    while(coordinate % 2 == 0) {
        coordinate = (rand() + 1) % (getMazeHeight() - 1);
    }
    return coordinate;
}

int maze::randomXCoordinate() {
    int coordinate = 2;
    while(coordinate % 2 == 0) {
        coordinate = (rand() + 1) % (getMazeWidth() - 1);
    }
    return coordinate;
}

int maze::findStartCellX() { // Finds the x coordinate of 'S'
    int x;
    for(x = 0; x < grid[0].size(); x++) {
        if(grid[0][x].graphic == 'S') {
            return x;
        }
    }
    return x;
}

int maze::findEndCellX() { // Finds the x coordinate of 'E'
    int x;
    for(x = 0; x < grid[0].size(); x++) {
        if(grid[grid.size() - 1][x].graphic == 'E') {
            return x;
        }
    }
    return x;
}

int maze::setStartCell() { // Set end cell on random position on bottom row
    int xCoord = 1 + rand() % (grid[0].size() - 2); // Generate random x-axis number of maze
    while(xCoord % 2 == 0) {
        xCoord = 1 + rand() % (grid[0].size() - 2);
    }
    grid[0][xCoord].graphic = 'S';
    grid[0][xCoord].visited = true;
    return xCoord;
}

int maze::setEndCell() { // Set end cell on random position on bottom row
    int xCoord = 1 + rand() % (grid[0].size() - 2); // Generate random x-axis number of maze
    while(xCoord % 2 == 0) {
        xCoord = 1 + rand() % (grid[0].size() - 2);
    }
    grid[grid.size() - 1][xCoord].graphic = 'E';
    grid[grid.size() - 1][xCoord].visited = true;
    return xCoord;
}

int maze::getMazeWidth() {
    return grid[0].size();
}

int maze::getMazeHeight() {
    return grid.size();
}

void maze::printBFS() {
    coord cell;
    coord oldCoords;
    int counter = 1; // Counts steps
    cell.x = findEndCellX();
    cell.y = grid.size() - 1;
    if(!(grid[cell.y][cell.x].parent.x == 0 && grid[cell.y][cell.x].parent.y == 0)) {
        while(grid[cell.y][cell.x].graphic != 'S') { // Going backwards in maze till cell is at 'S' cell
            grid[cell.y][cell.x].graphic = '*'; // Change graphic
            counter++;
            oldCoords = cell;
            // Change cell to parent coords
            cell.x = (grid[oldCoords.y][oldCoords.x]).parent.x;
            cell.y = (grid[oldCoords.y][oldCoords.x]).parent.y;
            if(shouldAnimate) {
                system("clear");
                print();
                system("sleep 0.04s");
            }
        }
        grid[cell.y][cell.x].graphic = '*'; // Change S as well
        if(isatty(STDIN_FILENO)){
            system("clear");
        }
        print();
        std::cout << "Shortest path is " << counter<< " cells." << std::endl;
    }
}

void maze::print() {
    for(int y = 0; y < grid.size(); y++) {
        for(int x = 0; x < grid[0].size(); x++) {
            if(printToFile || GUI) {
                std::cout << grid[y][x].graphic;
            }
            else {
                if(grid[y][x].graphic == '#') {
                    printf("\033[42m \033[m");
                }
                else if(grid[y][x].graphic == '*') {
                    printf("\033[41m \033[m");
                }
                else if(grid[y][x].graphic == ' ') {
                    printf("\033[107m \033[m");
                }
                else{
                    std::cout << grid[y][x].graphic;
                }
            }
        }
        std::cout << std::endl;
    }
}

// PRIVATE

std::vector<maze::coord> maze::getNeighbours(int x, int y, int check) {
    std::vector<coord> neighbours;

    // Checks if neighbours left, right, top, bot are visitable
    if(check == 1) { // When generating paths
        if(isVisitable(x + 2, y)) {
            neighbours.push_back({x + 2, y});
        }
        if(isVisitable(x - 2, y)) {
            neighbours.push_back({x - 2, y});
        }
        if(isVisitable(x, y + 2)) {
            neighbours.push_back({x, y + 2});
        }
        if(isVisitable(x, y - 2)) {
            neighbours.push_back({x, y - 2});
        }
    }
    else { // When finding solution path
        if(isVisitable(x + 1, y)) {
            neighbours.push_back({x + 1, y});
        }
        if(isVisitable(x - 1, y)) {
            neighbours.push_back({x - 1, y});
        }
        if(isVisitable(x, y + 1) || grid[y + 1][x].graphic == 'E') {
            neighbours.push_back({x, y + 1});
        }
        if(isVisitable(x, y - 1)) {
            neighbours.push_back({x, y - 1});
        }
    }
    return neighbours;
}

bool maze::checkSubNeighbours(int x, int y) { //Function is useless :/
    int numVisitable = 0;

    // If subneighbours are all visited then the maze wouldn't have "maze" looking walls.

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

bool maze::isBorder(int x, int y) { //Another useless function :/
    // If x or y coordinate is at border
    if(x == 0 || x == grid[0].size() - 1 || y == grid.size() - 1 || y == 0) {
        return true;
    }
    else { // Not border
        return false;
    }

}

void maze::openPathConnection(coord n, coord neighbour) {
    if(n.x != neighbour.x) {
        if(n.x < neighbour.x) { // Neighbour is to right
            grid[n.y][n.x + 1].graphic = ' ';
            grid[n.y][n.x + 1].visited = true;
        }
        else { // Neighbour is to left
            grid[n.y][n.x - 1].graphic = ' ';
            grid[n.y][n.x - 1].visited = true;
        }
    }
    else {
        if(n.y < neighbour.y) { // Neighbour is down
            grid[n.y + 1][n.x].graphic = ' ';
            grid[n.y + 1][n.x].visited = true;
        }
        else { // Neighbour is up
            grid[n.y - 1][n.x].graphic = ' ';
            grid[n.y - 1][n.x].visited = true;
        }
    }
}

maze::node::node() {
    visited = false;
    graphic = '#';
    parent.x = 0;
    parent.y = 0;
}