# MAZE GENERATOR (Windows version)

This program generates mazes with either dfs or bfs algorithms. It can also solve them with either a depth-first search or a breadth-first search or you can solve it yourself.

## First time usage

To compile file for first time usage, type the following in the terminal

```bash
g++ -o maze main.cpp maze.cpp menu.cpp maze_txt.cpp
```

## Normal usage

To generates random mazes type this in terminal:

```bash
maze.exe
maze.exe --animate //Adds animation when generating
maze.exe --char //Removes graphical colors
```

The program also allows you to generate mazes and then solve them on your own

## Using your own mazes from .txt files

To solve you own maze that you have saved as a txt file type the following command in terminal:

```c++
maze.exe < <filename>.txt
```
Or you can type:

```c++
maze.exe < <filename>.txt > <solutionfile>.txt
```

To see the solution in a separate .txt file

## Rules for using your own .txt maze

* The width and height of maze must be of odd numbers.
* All walls are represented by non-whitespaces.
* All paths are represented by ' '.
* There must be a 'S' on the top row representing the start cell.
* There must be a 'E' on the bottom row representing the end cell.
* The start and end cell chars cannot be in a corner.
