#include <stdio.h>
#include <stdlib.h>
#include "puzzle.hpp"

int main(int argc, char* argv[]){
    char* algorithmType;
    int puzzleSize = -1, numOfInstances = -1, i, j;
    int *initialState;

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
    printf("Esse é um %d-Puzzle!\n", puzzleSize - 1);
    printf("Argc: %d\n", argc);

    initialState = (int*) malloc(puzzleSize*sizeof(int));
    for(i = 0; i < numOfInstances; i++){
        initialState = fill_initial_state(initialState, argv, puzzleSize, i);
        for(j = 0; j < puzzleSize; j++){
            printf("%d ", initialState[j]);
        }
    }

    return 0;
}
