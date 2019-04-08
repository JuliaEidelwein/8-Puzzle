#include <iostream>
#include "puzzle.hpp"

int main(int argc, char* argv[]){
    char* algorithmType;
    int puzzleSize = -1;
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
    } else {
        std::cout << "Incorrect number of arguments!" << std::endl;
        std::cout << "Use: ./main -<algType> <instance>" << std::endl;
        return 0;
    }
    std::cout << "Esse é um " << puzzleSize - 1 << "-Puzzle!" << std::endl;
    std::cout << argc << std::endl;
    return 0;
}
