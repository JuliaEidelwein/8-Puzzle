#include <stdlib.h>
#include <stdio.h>
#include "puzzle.hpp"

unsigned long long fill_initial_state(unsigned long long initialState, char* argv[], int puzzleSize, int instance){
    int startPosition = (2 + instance*puzzleSize), endPosition = (2 + (1+instance)*puzzleSize);
    int i, entry, shiftAmount = 0, zeroPosition = 0;
    for(i = startPosition; i < endPosition - 1; i++){
        //initialState[j] = atoi(argv[i]);
        entry = atoi(argv[i]);
        initialState = initialState | entry;
        if(entry == 0){
            zeroPosition = shiftAmount;
        }
        printf("ATOI %llx\n",initialState);
        initialState = initialState << 4;
        shiftAmount++;
        printf("SHIFT %llx\n",initialState);
    }
    entry = atoi(argv[i]);
    initialState = initialState | entry;
    if(entry == 0){
        zeroPosition = shiftAmount;
    }
    printf("ATOI %llx\n",initialState);
    zeroPosition = (puzzleSize - 1) - zeroPosition;
    printf("Zero esta na posicao %d\n",zeroPosition);
    return initialState;
}

unsigned long long generate_successors(unsigned long long state, int zeroPosition, int direction){
    unsigned long long newState;
    switch(direction){
        case UP:

        case DOWN:
        case LEFT:
        case RIGHT:
            break;
    }
}
