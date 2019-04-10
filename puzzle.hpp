#include "graph.hpp"

State fill_initial_state(unsigned long long initialState, char* argv[], int puzzleSize, int instance);

std::vector<State*> generate_successors(State state, int puzzleSize);
