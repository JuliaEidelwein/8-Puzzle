#include <stdlib.h>
#include <stdio.h>
#include "puzzle.hpp"

unsigned long long fill_initial_state(unsigned long long initialState, char* argv[], int puzzleSize, int instance){
    int startPosition = (2 + instance*puzzleSize), endPosition = (2 + (1+instance)*puzzleSize);
    int i, j;
    for(i = startPosition, j = 0; i < endPosition - 1; i++, j++){
        //initialState[j] = atoi(argv[i]);
        initialState = initialState | atoi(argv[i]);
        printf("ATOI %llx\n",initialState);
        initialState = initialState << 4;
        printf("SHIFT %llx\n",initialState);
    }
    initialState = initialState | atoi(argv[i]);
    printf("ATOI %llx\n",initialState);
    return initialState;
}
