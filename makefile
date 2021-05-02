#Samuel Greenberg
#02/05/2021
#DT019G
#Labyrint Projekt
#Siktar på betyget A

program: main.cpp maze.cpp menu.cpp maze_txt.cpp
	g++ -o maze main.cpp maze.cpp menu.cpp maze_txt.cpp -g

run: program
	./maze

del: program
	rm maze
