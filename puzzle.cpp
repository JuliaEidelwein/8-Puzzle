#include "puzzle.hpp"

/* The puzzle is represented with a unsigned long long, using four bits per tile
                        [0][1][2]
0 1 2 3 4 5 6 7 8  -->  [3][4][5] --> 0000 0001 0010 0011 0100 0101 0110 0111 1000
                        [6][7][8]

                                             [ 0][ 1][ 2][ 3]
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15   -->  [ 4][ 5][ 6][ 7]  -->      0000 0001 0010 0011 0100 0101 0110 0111...
                                             [ 8][ 9][10][11]        ...1000 1001 1010 1011 1100 1101 1110 1111
                                             [12][13][14][15]

We mark each position in the following order:

[8][7][6]
[5][4][3] --> 8 7 6 5 4 3 2 1 0, which means the number of shifts needed to reach that position
[2][1][0]


*/

State fill_initial_state(unsigned long long initialState, char* argv[], int puzzleSize, int instance){
    int startPosition = (2 + instance*puzzleSize), endPosition = (2 + (1+instance)*puzzleSize);
    int i, entry, shiftAmount = 0, zeroPosition = 0;
    globalPuzzleSize = puzzleSize;
    nodeIdCounter = 0;
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
    State newState = State(initialState, zeroPosition);
    return newState;
}

State::State(){
}

State::State(unsigned long long value, int zeroPosition){
    this->value = value;
    this->zeroPosition = zeroPosition;
    this->heuristicValue = this->heuristicFunction();
}

std::vector<State*> State::generate_successors(){
    unsigned long long temp, maskOnes, newState = 0xf;
    int switchPosition;
    std::vector<State*> successors;
    if(globalPuzzleSize == 9){ //8 puzzle
        //UP
        if(this->zeroPosition < 6){ //not in position 8, 7 or 6
            switchPosition = this->zeroPosition + 3;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 12;
            newState = temp | newState;
            State* upState = new State(newState, switchPosition);
            successors.push_back(upState);
            newState = 0xf;
        }
        //LEFT
        if(((this->zeroPosition - 2) % 3) != 0){ //not in position 8, 5, or 2
            switchPosition = this->zeroPosition + 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 4;
            newState = temp | newState;
            State* leftState = new State(newState, switchPosition);
            successors.push_back(leftState);
            newState = 0xf;
        }
        //RIGHT
        if((this->zeroPosition % 3) != 0){ //not in position 6, 3 or 0
            switchPosition = this->zeroPosition - 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 4;
            newState = temp | newState;
            State* rightState = new State(newState, switchPosition);
            successors.push_back(rightState);
            newState = 0xf;
        }
        //DOWN
        if(this->zeroPosition > 2){ //not in position 2, 1 or 0
            switchPosition = this->zeroPosition - 3;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 12;
            newState = temp | newState;
            State* downState = new State(newState, switchPosition);
            successors.push_back(downState);
            newState = 0xf;
        }
    } else { //15 puzzle
        //UP
        if(this->zeroPosition < 12){ //not in position 15, 14, 13 or 12
            switchPosition = this->zeroPosition + 4;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 16;
            newState = temp | newState;
            State* upState = new State(newState, switchPosition);
            successors.push_back(upState);
            newState = 0xf;
        }
        //LEFT
        if(((this->zeroPosition - 3) % 4) != 0){ //not in position 15, 11, 7 or 3
            switchPosition = this->zeroPosition + 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 4;
            newState = temp | newState;
            State* leftState = new State(newState, switchPosition);
            successors.push_back(leftState);
            newState = 0xf;
        }
        //RIGHT
        if((this->zeroPosition % 4) != 0){ //not in position 12, 8, 4 or 0
            switchPosition = this->zeroPosition - 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 4;
            newState = temp | newState;
            State* rightState = new State(newState, switchPosition);
            successors.push_back(rightState);
            newState = 0xf;
        }
        //DOWN
        if(this->zeroPosition > 3){ //not in position 3, 2, 1 or 0
            switchPosition = this->zeroPosition - 4;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 16;
            newState = temp | newState;
            State* downState = new State(newState, switchPosition);
            successors.push_back(downState);
            newState = 0xf;
        }
    }
    return successors;
}

std::vector<State*> State::generate_successors(unsigned long long parent){
    unsigned long long temp, maskOnes, newState = 0xf;
    int switchPosition;
    std::vector<State*> successors;
    if(globalPuzzleSize == 9){ //8 puzzle
        //UP
        if(this->zeroPosition < 6){ //not in position 8, 7 or 6
            switchPosition = this->zeroPosition + 3;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 12;
            newState = temp | newState;
            if(newState != parent){
                State* upState = new State(newState, switchPosition);
                successors.push_back(upState);
            }
            newState = 0xf;
        }
        //LEFT
        if(((this->zeroPosition - 2) % 3) != 0){ //not in position 8, 5, or 2
            switchPosition = this->zeroPosition + 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 4;
            newState = temp | newState;
            if(newState != parent){
                State* leftState = new State(newState, switchPosition);
                successors.push_back(leftState);
            }
            newState = 0xf;
        }
        //RIGHT
        if((this->zeroPosition % 3) != 0){ //not in position 6, 3 or 0
            switchPosition = this->zeroPosition - 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 4;
            newState = temp | newState;
            if(newState != parent){
                State* rightState = new State(newState, switchPosition);
                successors.push_back(rightState);
            }
            newState = 0xf;
        }
        //DOWN
        if(this->zeroPosition > 2){ //not in position 2, 1 or 0
            switchPosition = this->zeroPosition - 3;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 12;
            newState = temp | newState;
            if(newState != parent){
                State* downState = new State(newState, switchPosition);
                successors.push_back(downState);
            }
            newState = 0xf;
        }
    } else { //15 puzzle
        //UP
        if(this->zeroPosition < 12){ //not in position 15, 14, 13 or 12
            switchPosition = this->zeroPosition + 4;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 16;
            newState = temp | newState;
            if(newState != parent){
                State* upState = new State(newState, switchPosition);
                successors.push_back(upState);
            }
            newState = 0xf;
        }
        //LEFT
        if(((this->zeroPosition - 3) % 4) != 0){ //not in position 15, 11, 7 or 3
            switchPosition = this->zeroPosition + 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState >> 4;
            newState = temp | newState;
            if(newState != parent){
                State* leftState = new State(newState, switchPosition);
                successors.push_back(leftState);
            }
            newState = 0xf;
        }
        //RIGHT
        if((this->zeroPosition % 4) != 0){ //not in position 12, 8, 4 or 0
            switchPosition = this->zeroPosition - 1;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 4;
            newState = temp | newState;
            if(newState != parent){
                State* rightState = new State(newState, switchPosition);
                successors.push_back(rightState);
            }
            newState = 0xf;
        }
        //DOWN
        if(this->zeroPosition > 3){ //not in position 3, 2, 1 or 0
            switchPosition = this->zeroPosition - 4;
            maskOnes = newState << 4*switchPosition;//Gets mask with ones only at the position the blank must go
            newState = this->value & maskOnes; //Extracts value of the tile at the position
            temp = this->value & (~maskOnes); //Replace tile value with zeros
            newState = newState << 16;
            newState = temp | newState;
            if(newState != parent){
                State* downState = new State(newState, switchPosition);
                successors.push_back(downState);
            }
            newState = 0xf;
        }
    }
    return successors;
}

//Calculate manhattan distance to goal position
int State::heuristicFunction(){
    int manhattanDist = 0;
    unsigned long long stateIter = this->value, mask = 0xf;
    for(int i = 0; i < globalPuzzleSize; i++){
        unsigned long long currentTile = stateIter & mask;
        stateIter = stateIter >> 4;
        if(currentTile != 0){
            int goalPosition = getGoalTilePosition(currentTile);
            manhattanDist = manhattanDist + std::abs(getRow(i) - getRow(goalPosition));
            manhattanDist = manhattanDist + std::abs(getColumn(i) - getColumn(goalPosition));
        }
    }
    return manhattanDist;
}

//Determines tile position in goal state
int getGoalTilePosition(unsigned long long tile){
    int j = 0;
    unsigned long long mask = 0xf;
    if(globalPuzzleSize == 9){
        while((GOAL8 & mask) != tile){
            j++;
            tile = tile << 4;
            mask = mask << 4;
        }
    } else {
        while((GOAL15 & mask) != tile){
            j++;
            tile = tile << 4;
            mask = mask << 4;
        }

    }
    return j;
}

int getRow(int position){
    if(globalPuzzleSize == 9){
        if(position >= 6)
            return 0;
        if(position >= 3)
            return 1;
        return 2;
    } else {
        if(position >= 12)
            return 0;
        if(position >= 8)
            return 1;
        if(position >= 4)
            return 2;
        return 3;
    }
}


int getColumn(int position){
    if(globalPuzzleSize == 9){
        if(position % 3 == 0)
            return 2;
        if((position - 1) % 3 == 0)
            return 1;
        return 0;
    } else {
        if(position % 4 == 0)
            return 3;
        if((position - 1) % 4 == 0)
            return 2;
        if((position - 2) % 4 == 0)
            return 1;
        return 0;
    }
}

bool State::isGoal(){
    if(globalPuzzleSize == 9){
        return ((unsigned long long)this->value == (unsigned long long)GOAL8);
    } else {
        return ((unsigned long long)this->value == (unsigned long long)GOAL15);
    }
}

Node::Node(State *state, int cost){
    this->id = nodeIdCounter;
    this->state = state;
    this->cost = cost;
    nodeIdCounter++;
}

std::ostream& operator<<(std::ostream& os, Output output){
    if(output.optimalSolutionSize != -1){
        os << std::fixed << output.expandedNodes << ',' << output.optimalSolutionSize << ','
            << (double)output.time/CLOCKS_PER_SEC << ',' << output.averageHeuristicValue << ','
            << output.heuristicInitialState;
    } else {
        os << "-,-,-,-,-";
    }
    return os;
}
