#include <stdio.h>
#include <stdlib.h>
#include "puzzle.hpp"
#include "graph.hpp"

int main(int argc, char* argv[]){
    char* algorithmType;
    int puzzleSize = -1, numOfInstances = -1, i, j;

    if(argc > 2){
        algorithmType = argv[1];
        for(i = 2; i < argc; i++){
            printf("%s\n", argv[i]);
            if(argv[i][1]){
                puzzleSize = i - 1;
            }
        }
        if(puzzleSize == -1){
            puzzleSize = argc - 2;
        }
        numOfInstances = (argc - 2)/puzzleSize;
    } else {
        printf("Incorrect number of arguments!\n");
        printf("Use: ./main -<algType> <instance>\n");
        return 0;
    }
    std::cout << "Esse é um " << puzzleSize - 1 << "-Puzzle!" << std::endl;
    //std::cout << argc << std::endl;

    unsigned long long initialState = 0;
    for(int i = 0; i < numOfInstances; i++){
        initialState = fill_initial_state(initialState, argv, puzzleSize, i);
        printf("%llx\n",initialState);
    }

    for(int i = 0; i < puzzleSize; i++){
        generate_successors(initialState, i, UP);
        generate_successors(initialState, i, DOWN);
        generate_successors(initialState, i, LEFT);
        generate_successors(initialState, i, RIGHT);
    }

    return 0;
}
