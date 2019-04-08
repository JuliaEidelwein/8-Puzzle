#include <iostream>
#include "puzzle.hpp"

int main(int argc, char* argv[]){
    std::cout << argc << std::endl;
    if(argc > 1){
        std::cout << argv[1] << std::endl;
    }
    return 0;
}
