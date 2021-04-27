program: main.cpp maze.cpp menu.cpp
	g++ -o maze main.cpp maze.cpp menu.cpp -g

run: program
	./maze

del: program
	rm maze
