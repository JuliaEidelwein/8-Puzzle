#include <iostream>
#include <stdlib.h>
#include "puzzle.hpp"

int * fill_initial_state(int initialState[], char* argv[], int puzzleSize, int instance){
    int startPosition = (2 + instance*puzzleSize), endPosition = (2 + (1+instance)*puzzleSize);
    int i, j;
    for(i = startPosition, j = 0; i < endPosition; i++, j++){
        initialState[j] = atoi(argv[i]);
    }
    return initialState;
}
