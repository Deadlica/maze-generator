# MAZE GENERATOR

This program generates mazes with either dfs or bfs algorithms. It can also solve them with either a depth-first search or a breadth-first search.

## Normal usage

To generates random mazes type this in terminal:

```bash
./maze
./maze --animate //Adds animation when generating
```

## Using your own mazes from .txt files

To solve you own maze that you have saved as a txt file type the following command in terminal:

```c++
./maze < <filename>.txt
```
Or you can type:

```c++
./maze < <filename>.txt > <solutionfile>.txt
```

To see the solution in a separate .txt file

## Rules for using your own .txt maze

* The width and height of maze must be of odd numbers.
* All walls are represented by non-whitespaces.
* All paths are represented by ' '.
* There must be a 'S' on the top row representing the start cell.
* There must be a 'E' on the bottom row representing the end cell.
* The start and end cell chars cannot be in a corner.
