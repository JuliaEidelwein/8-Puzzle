all: main clean
main: puzzle.o main.o 
	g++ -o main puzzle.o main.o
puzzle.o: puzzle.cpp
	g++ -o puzzle.o -c puzzle.cpp -W -Wall -ansi -pedantic
main.o: main.cpp puzzle.hpp
	g++ -o main.o -c main.cpp -W -Wall -ansi -pedantic
clean:
	rm -rf *.o
mrproper: clean
	rm -rf main
