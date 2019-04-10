#include <vector>
#include <iostream>

class State{
    public:
    unsigned long long value;
    int zeroPosition;
    std::vector<State*> successors;

    std::vector<State*> generate_successors(State state, int puzzleSize);
};


class Node{
    int id;
    State state;
    int cost;
};


State fill_initial_state(unsigned long long initialState, char* argv[], int puzzleSize, int instance);


