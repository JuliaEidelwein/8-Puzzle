#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "puzzle.hpp"


/* The puzzle is represented with a unsigned long long, using four bits per tile
                        [1][2][3]
1 2 3 4 5 6 7 8 0  -->  [4][5][6] --> 0001 0010 0011 0100 0101 0110 0111 1000 0000
                        [7][8][0]

                                             [ 1][ 2][ 3][ 4]
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0   -->  [ 5][ 6][ 7][ 8]  --> 0001 0010 0011 0100 0101 0110 0111 1000...
                                             [ 9][10][11][12]        ...1001 1010 1011 1100 1101 1110 1111 0000
                                             [13][14][15][ 0]

We mark each position in the following order:

[8][7][6]
[5][4][3] --> 8 7 6 5 4 3 2 1 0, which means the number of shifts needed to reach that position
[2][1][0]


*/

State fill_initial_state(unsigned long long initialState, char* argv[], int puzzleSize, int instance){
    int startPosition = (2 + instance*puzzleSize), endPosition = (2 + (1+instance)*puzzleSize);
    int i, entry, shiftAmount = 0, zeroPosition = 0;
    State newState;
    for(i = startPosition; i < endPosition - 1; i++){
        entry = atoi(argv[i]);
        initialState = initialState | entry;
        if(entry == 0){
            zeroPosition = shiftAmount;
        }
        initialState = initialState << 4;
        shiftAmount++;
    }
    entry = atoi(argv[i]);
    initialState = initialState | entry;
    if(entry == 0){
        zeroPosition = shiftAmount;
    }
    zeroPosition = (puzzleSize - 1) - zeroPosition;
    newState.value = initialState;
    newState.zeroPosition = zeroPosition;
    return newState;
}

std::vector<State*> State::generate_successors(State state, int puzzleSize){
    unsigned long long temp, maskOnes, newState = 0xf;
    int switchPosition;
    std::vector<State*> successors;
    if(puzzleSize == 9){ //8 puzzle
        if(state.zeroPosition < 6){ //not in position 8, 7 or 6
            switchPosition = state.zeroPosition + 3;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = state.value & maskOnes; //Extracts value of the tile at the position
            temp = state.value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 12;
            newState = temp | newState;
            State *upState = new State();
            upState->value = newState;
            upState->zeroPosition = switchPosition;
            successors.push_back(upState);
            newState = 0xf;
        }
        if(state.zeroPosition > 2){ //not in position 2, 1 or 0
            switchPosition = state.zeroPosition - 3;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = state.value & maskOnes; //Extracts value of the tile at the position
            temp = state.value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 12;
            newState = temp | newState;
            State *downState = new State();
            downState->value = newState;
            downState->zeroPosition = switchPosition;
            successors.push_back(downState);
            newState = 0xf;
        }
        if((state.zeroPosition % 3) != 0){ //not in position 6, 3 or 0
            switchPosition = state.zeroPosition - 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = state.value & maskOnes; //Extracts value of the tile at the position
            temp = state.value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 4;
            newState = temp | newState;
            State *rightState = new State();
            rightState->value = newState;
            rightState->zeroPosition = switchPosition;
            successors.push_back(rightState);
            newState = 0xf;
        }
        if(((state.zeroPosition - 2) % 3) != 0){ //not in position 8, 5, or 2
            switchPosition = state.zeroPosition + 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = state.value & maskOnes; //Extracts value of the tile at the position
            temp = state.value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 4;
            newState = temp | newState;
            State *leftState = new State();
            leftState->value = newState;
            leftState->zeroPosition = switchPosition;
            successors.push_back(leftState);
            newState = 0xf;
        }
    } else { //15 puzzle
        if(state.zeroPosition < 12){ //not in position 15, 14, 13 or 12
            switchPosition = state.zeroPosition + 4;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = state.value & maskOnes; //Extracts value of the tile at the position
            temp = state.value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 16;
            newState = temp | newState;
            State *upState = new State();
            upState->value = newState;
            upState->zeroPosition = switchPosition;
            successors.push_back(upState);
            newState = 0xf;
        }
        if(state.zeroPosition > 3){ //not in position 3, 2, 1 or 0
            switchPosition = state.zeroPosition - 4;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = state.value & maskOnes; //Extracts value of the tile at the position
            temp = state.value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 16;
            newState = temp | newState;
            State *downState = new State();
            downState->value = newState;
            downState->zeroPosition = switchPosition;
            successors.push_back(downState);
            newState = 0xf;
        }
        if((state.zeroPosition % 4) != 0){ //not in position 12, 8, 4 or 0
            switchPosition = state.zeroPosition - 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = state.value & maskOnes; //Extracts value of the tile at the position
            temp = state.value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 4;
            newState = temp | newState;
            State *rightState = new State();
            rightState->value = newState;
            rightState->zeroPosition = switchPosition;
            successors.push_back(rightState);
            newState = 0xf;
        }
        if(((state.zeroPosition - 3) % 3) != 0){ //not in position 15, 11, 7 or 3
            switchPosition = state.zeroPosition + 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = state.value & maskOnes; //Extracts value of the tile at the position
            temp = state.value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 4;
            newState = temp | newState;
            State *leftState = new State();
            leftState->value = newState;
            leftState->zeroPosition = switchPosition;
            successors.push_back(leftState);
            newState = 0xf;
        }
    }
    return successors;
}
