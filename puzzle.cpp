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

unsigned long long generate_successors(unsigned long long state, int zeroPosition, int direction, int puzzleSize){
    unsigned long long temp, maskOnes, newState = 0xf;
    int switchPosition;
    if(puzzleSize == 9){
        switch(direction){
            case UP:
                if(zeroPosition < 6){ //not in position 8, 7 or 6
                    std::cout << "Able to move up" << std::endl;
                    switchPosition = zeroPosition + 3;
                    maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
                    newState = state & maskOnes; //Extracts value of the tile at the position
                    temp = state & (~maskOnes); //Replace tile value with zeros
                    newState = newState >> 12;
                    newState = temp | newState;
                }
                break;
            case DOWN:
                if(zeroPosition > 2){ //not in position 2, 1 or 0
                    std::cout << "Able to move down" << std::endl;
                    switchPosition = zeroPosition - 3;
                    maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
                    newState = state & maskOnes; //Extracts value of the tile at the position
                    temp = state & (~maskOnes); //Replace tile value with zeros
                    newState = newState << 12;
                    newState = temp | newState;
                }
                break;
            case RIGHT:
                if((zeroPosition % 3) != 0){ //not in position 6, 3 or 0
                    std::cout << "Able to move right" << std::endl;
                    switchPosition = zeroPosition - 1;
                    maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
                    newState = state & maskOnes; //Extracts value of the tile at the position
                    temp = state & (~maskOnes); //Replace tile value with zeros
                    newState = newState << 4;
                    newState = temp | newState;
                }
                break;
            case LEFT:
                if(((zeroPosition - 2) % 3) != 0){ //not in position 8, 5, or 2
                    std::cout << "Able to move left" << std::endl;
                    switchPosition = zeroPosition + 1;
                    maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
                    newState = state & maskOnes; //Extracts value of the tile at the position
                    temp = state & (~maskOnes); //Replace tile value with zeros
                    newState = newState >> 4;
                    newState = temp | newState;
                }
                break;
        }
    } else {
        std::cout << "15 PUZZLE!!!!\n";
        switch(direction){
            case UP:
                if(zeroPosition < 12){ //not in position 15, 14, 13 or 12
                    std::cout << "Able to move up" << std::endl;
                    switchPosition = zeroPosition + 4;
                    maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
                    newState = state & maskOnes; //Extracts value of the tile at the position
                    temp = state & (~maskOnes); //Replace tile value with zeros
                    newState = newState >> 16;
                    newState = temp | newState;
                }
                break;
            case DOWN:
                if(zeroPosition > 3){ //not in position 3, 2, 1 or 0
                    std::cout << "Able to move down" << std::endl;
                    switchPosition = zeroPosition - 4;
                    maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
                    newState = state & maskOnes; //Extracts value of the tile at the position
                    temp = state & (~maskOnes); //Replace tile value with zeros
                    newState = newState << 16;
                    newState = temp | newState;
                }
                break;
            case RIGHT:
                if((zeroPosition % 4) != 0){ //not in position 12, 8, 4 or 0
                    std::cout << "Able to move right" << std::endl;
                    switchPosition = zeroPosition - 1;
                    maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
                    newState = state & maskOnes; //Extracts value of the tile at the position
                    temp = state & (~maskOnes); //Replace tile value with zeros
                    newState = newState << 4;
                    newState = temp | newState;
                }
                break;
            case LEFT:
                if(((zeroPosition - 3) % 3) != 0){ //not in position 15, 11, 7 or 3
                    std::cout << "Able to move left" << std::endl;
                    switchPosition = zeroPosition + 1;
                    maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
                    newState = state & maskOnes; //Extracts value of the tile at the position
                    temp = state & (~maskOnes); //Replace tile value with zeros
                    newState = newState >> 4;
                    newState = temp | newState;
                }
                break;
        }
    }
    printf("Before: %llx | After: %llx\n",state,newState);
    //std::cout << "Before: " << state << " After: " << newState << std::endl;
}
