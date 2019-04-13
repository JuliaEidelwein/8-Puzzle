#include <stdio.h>
#include <stdlib.h>
#include "algorithms.hpp"

int main(int argc, char* argv[]){
    char* algorithmType;
    int puzzleSize = -1, numOfInstances = -1, i;

    if(argc > 2){
        algorithmType = argv[1];
        for(i = 2; i < argc; i++){
            if(argv[i][1] && argv[i][1] == ',' && puzzleSize == -1){
                puzzleSize = i - 1;
            }
        }
        if(puzzleSize == -1){
            puzzleSize = argc - 2;
        }
        numOfInstances = (argc - 2)/puzzleSize;
        //printf("argc: %d, puzzleSize: %d, numOfInstances: %d\n", argc, puzzleSize, numOfInstances);
    } else {
        printf("Incorrect number of arguments!\n");
        printf("Use: ./main -<algType> <instance>\n");
        return 0;
    }

    unsigned long long initialState = 0;
    State state;
    for(int i = 0; i < numOfInstances; i++){
        state = fill_initial_state(initialState, argv, puzzleSize, i);
        state.successors = state.generate_successors();
        //printf("Instance %d: %llx\n", numOfInstances, state.value);
        std::cout << BFS_Graph(state) << std::endl;
        std::cout << IterativeDeepening_DFS(state) << std::endl;
    }

    //state.successors = state.generate_successors();
    //std::cout << BFS_Graph(state) << std::endl;

    return 0;
}
