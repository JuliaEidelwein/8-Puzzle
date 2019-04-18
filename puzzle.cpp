#include "puzzle.hpp"

/* The puzzle is represented with a unsigned long long, using four bits per tile
                        [0][1][2]
0 1 2 3 4 5 6 7 8  -->  [3][4][5] --> 0001 0010 0011 0100 0101 0110 0111 1000 0000
                        [6][7][8]

                                             [ 0][ 1][ 2][ 3]
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15   -->  [ 4][ 5][ 6][ 7]  --> 0001 0010 0011 0100 0101 0110 0111 1000...
                                             [ 8][ 9][10][11]        ...1001 1010 1011 1100 1101 1110 1111 0000
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
    //printf("STATE: %llx ", this->value);
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
            //printf("| UP: %llx ", upState->value);
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
            //printf("| LEFT: %llx ", leftState->value);
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
            //printf("| RIGHT: %llx ", rightState->value);
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
            //printf("| DOWN: %llx ", downState->value);
            newState = 0xf;
        }
    }
    //printf("\n");
    //std::cin.ignore();
    return successors;
}

std::vector<State*> State::generate_successors(unsigned long long parent){
    unsigned long long temp, maskOnes, newState = 0xf;
    int switchPosition;
    std::vector<State*> successors;
    //printf("STATE: %llx ", this->value);
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
                //printf("%llx not equal to %llx\n", newState, parent);
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
                //printf("%llx not equal to %llx\n", newState, parent);
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
                //printf("%llx not equal to %llx\n", newState, parent);
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
                //printf("%llx not equal to %llx\n", newState, parent);
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
            //printf("| UP: %llx ", upState->value);
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
            //printf("| LEFT: %llx ", leftState->value);
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
            //printf("| RIGHT: %llx ", rightState->value);
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
            //printf("| DOWN: %llx ", downState->value);
            newState = 0xf;
        }
    }
    //printf("\n");
    //std::cin.ignore();
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
            //std::cout << "Tile at " << i << " has Row " << getRow(i) << " and Column " <<  getColumn(i) << std::endl;
            //std::cout << "Goal tile at " << goalPosition << " has Row " << getRow(goalPosition)<< " and Column " <<  getColumn(goalPosition) << std::endl;
            //std::cout << "Distance: " << std::abs(getRow(i) - getRow(goalPosition)) << " + " << std::abs(getColumn(i) - getColumn(goalPosition)) << std::endl;
            //std::cin.ignore();
        }
    }
    //std::cout << "Total: " << manhattanDist << std::endl;
    return manhattanDist;
}

//Determines tile position in goal state
int getGoalTilePosition(unsigned long long tile){
    int j = 0;
    unsigned long long mask = 0xf;
    //printf("Tile came as %llx\n", tile);
    //std::cout << tile << std::endl;
    if(globalPuzzleSize == 9){
        /*switch(tile){
        case 0:
            return 8;
            printf("tile 0 fica na posicao 8\n");
            break;
        case 1:
            return 7;
            printf("tile 1 fica na posicao 7\n");
            break;
        case 2:
            return 6;
            printf("tile 2 fica na posicao 6\n");
            break;
        case 3:
            return 5;
            printf("tile 3 fica na posicao 5\n");
            break;
        case 4:
            return 4;
            printf("tile 4 fica na posicao 4\n");
            break;
        case 5:
            return 3;
            printf("tile 5 fica na posicao 3\n");
            break;
        case 6:
            return 2;
            printf("tile 6 fica na posicao 2\n");
            break;
        case 7:
            return 1;
            printf("tile 7 fica na posicao 1\n");
            break;
        case 8:
            return 0;
            printf("tile 8 fica na posicao 0\n");
            break;
        default:
            printf("Deu ruim aqui no 8\n");
        }*/
        while((GOAL8 & mask) != tile){
            j++;
            tile = tile << 4;
            mask = mask << 4;
        }
    } else {
        /*switch(tile){
        case 0:
            return 15;
            printf("tile 0 fica na posicao 15\n");
            break;
        case 1:
            return 14;
            printf("tile 1 fica na posicao 14\n");
            break;
        case 2:
            return 13;
            printf("tile 2 fica na posicao 13\n");
            break;
        case 3:
            return 12;
            printf("tile 3 fica na posicao 12\n");
            break;
        case 4:
            return 11;
            printf("tile 4 fica na posicao 11\n");
            break;
        case 5:
            return 10;
            printf("tile 5 fica na posicao 10\n");
            break;
        case 6:
            return 9;
            printf("tile 6 fica na posicao 9\n");
            break;
        case 7:
            return 8;
            printf("tile 7 fica na posicao 8\n");
            break;
        case 8:
            return 7;
            printf("tile 8 fica na posicao 7\n");
            break;
        case 9:
            return 6;
            printf("tile 9 fica na posicao 6\n");
            break;
        case 10:
            return 5;
            printf("tile 10 fica na posicao 5\n");
            break;
        case 11:
            return 4;
            printf("tile 11 fica na posicao 4\n");
            break;
        case 12:
            return 3;
            printf("tile 12 fica na posicao 3\n");
            break;
        case 13:
            return 2;
            printf("tile 13 fica na posicao 2\n");
            break;
        case 14:
            return 1;
            printf("tile 14 fica na posicao 1\n");
            break;
        case 15:
            return 0;
            printf("tile 15 fica na posicao 0\n");
        }*/

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
        os << std::fixed << "expandidos: " << output.expandedNodes << ',' << "solucao: " << output.optimalSolutionSize << ','
            << "tempo: "<< (double)output.time/CLOCKS_PER_SEC << ',' << "mediaHeur: " << output.averageHeuristicValue << ','<< "inicialHeur: "
            << output.heuristicInitialState;
    } else {
        os << "-,-,-,-,-";
    }
    return os;
}
