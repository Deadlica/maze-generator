#Samuel Greenberg
#02/05/2021
#DT019G
#Labyrint Projekt
#Siktar på betyget A

program: main.cpp maze.cpp menu.cpp maze_txt.cpp
	g++ -o maze main.cpp maze.cpp menu.cpp maze_txt.cpp -g -lncurses

run: program
	./maze

animate: program
	./maze --animate

char: program
	./maze --char

charAnimate: program
	./maze --char --animate

file: program
	clear
	./maze < maze.txt

file2: program
	./maze < maze.txt > solution.txt

del: program
	rm maze
