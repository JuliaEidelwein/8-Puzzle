all: main clean
main: puzzle.o main.o 
	gcc -o main puzzle.o main.o
puzzle.o: puzzle.c
	gcc -o puzzle.o -c puzzle.c -W -Wall -ansi -pedantic
main.o: main.c puzzle.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic
clean:
	rm -rf *.o
mrproper: clean
	rm -rf main
