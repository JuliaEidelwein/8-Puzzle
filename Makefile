all: main clean
main: algorithms.o puzzle.o main.o 
	g++ -o main algorithms.o puzzle.o main.o -std=c++11
puzzle.o: puzzle.cpp
	g++ -o puzzle.o -c puzzle.cpp -W -Wall -ansi -pedantic -std=c++11
algorithm.o: algorithms.cpp puzzle.hpp
	g++ -o algorithms.o -c algorithms.cpp -W -Wall -ansi -pedantic -std=c++11
main.o: main.cpp algorithms.hpp
	g++ -o main.o -c main.cpp -W -Wall -ansi -pedantic -std=c++11
clean:
	rm -rf *.o
mrproper: clean
	rm -rf main
