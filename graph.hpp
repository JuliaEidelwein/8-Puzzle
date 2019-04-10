#include <iostream>
#include <vector>
#include <queue>


class State{
    std::vector<State*> successors;

    public:
    unsigned long long value;
    int zeroPosition;
};


class Node{
    int id;
    State state;
    int cost;
};
