#include <iostream>
#include <vector>
#include <queue>


class State{
    unsigned long long value;
    int zeroPosition;
    std::vector<State*> successors;
};


class Node{
    int id;
    State state;
    int cost;
};
