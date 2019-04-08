#include <iostream>
#include <cstdlib>
#include "puzzle.hpp"

int main(int argc, char* argv[]){
    char* algorithmType;
    int puzzleSize = -1, numOfInstances = -1;
    if(argc > 2){
        algorithmType = argv[1];
        for(int i = 2; i < argc; i++){
            std::cout << argv[i] << std::endl;
            if(argv[i][1]){
                puzzleSize = i - 1;
            }
        }
        if(puzzleSize == -1){
            puzzleSize = argc - 2;
        }
        numOfInstances = (argc - 2)/puzzleSize;
    } else {
        std::cout << "Incorrect number of arguments!" << std::endl;
        std::cout << "Use: ./main -<algType> <instance>" << std::endl;
        return 0;
    }
    std::cout << "Esse é um " << puzzleSize - 1 << "-Puzzle!" << std::endl;
    std::cout << argc << std::endl;

    int *initialState;
    initialState = (int*) malloc(puzzleSize*sizeof(int));
    for(int i = 0; i < numOfInstances; i++){
        initialState = fill_initial_state(initialState, argv, puzzleSize, i);
        for(int i = 0; i < puzzleSize; i++){
            std::cout << initialState[i];
        }
    }

    return 0;
}
