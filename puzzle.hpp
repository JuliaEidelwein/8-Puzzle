#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#ifndef __puzzle_h__
#define __puzzle_h__
extern int globalPuzzleSize;
extern unsigned long long nodeIdCounter;
#endif

const unsigned long long GOAL8 = 0x123456780;
const unsigned long long GOAL15 = 0x123456789abcdef0;

class State{
    public:
    unsigned long long value;
    int zeroPosition;
    std::vector<State*> successors;

    std::vector<State*> generate_successors();
    bool isGoal();
};


class Node{
    public:
    unsigned long long id;
    State state;
    int cost;

    Node(State state, int cost);
};

class Output{
    unsigned long long expandedNodes;
    int optimalSolutionSize;
    time_t time;
    float averageHeuristicValue;
    int heuristicInitialState;
};


State fill_initial_state(unsigned long long initialState, char* argv[], int puzzleSize, int instance);


