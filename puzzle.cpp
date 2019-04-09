#include <stdlib.h>
#include <stdio.h>
#include <iostream>
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
            if(zeroPosition < 6){ //not in position 8, 7 or 6
                std::cout << zeroPosition << "Able to move up" << std::endl;
            } else {
                std::cout << zeroPosition << "UNABLE to move up" << std::endl;
            }
            break;
        case DOWN:
            if(zeroPosition > 2){ //not in position 2, 1 or 0
                std::cout << zeroPosition << "Able to move down" << std::endl;
            } else {
                std::cout << zeroPosition << "UNABLE to move down" << std::endl;
            }
            break;
        case RIGHT:
            if((zeroPosition % 3) != 0){ //not in position 6, 3 or 0
                std::cout << zeroPosition << "Able to move right" << std::endl;
            } else {
                std::cout << zeroPosition << "UNABLE to move right" << std::endl;
            }
            break;
        case LEFT:
            if(((zeroPosition - 2) % 3) != 0){ //not in position 8, 5, or 2
                std::cout << zeroPosition << "Able to move left" << std::endl;
            } else {
                std::cout << zeroPosition << "UNABLE to move left" << std::endl;
            }
            break;
    }
}
