#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <iostream>

#ifndef __puzzle_h__
#define __puzzle_h__
extern int globalPuzzleSize;
extern unsigned long long nodeIdCounter;
#endif

const unsigned long long GOAL8 = 0x12345678;
const unsigned long long GOAL15 = 0x123456789abcdef;

class State{
    public:
    State();
    State(unsigned long long value, int zeroPosition);
    unsigned long long value;
    int zeroPosition;
    int heuristicValue;
    std::vector<State*> successors;

    std::vector<State*> generate_successors();
    std::vector<State*> generate_successors(unsigned long long parent);
    bool isGoal();
    int heuristicFunction();

};


class Node{
    public:
    unsigned long long id;
    State *state;
    int cost;

    Node(State *state, int cost);
};

class Output{
    public:
    unsigned long long expandedNodes = 0;
    int optimalSolutionSize = 0;
    time_t time;
    float averageHeuristicValue = 0;
    int heuristicInitialState;
    unsigned long long generatedNodes = 0;
    unsigned long long heuristicSum = 0;
};


State fill_initial_state(unsigned long long initialState, char* argv[], int puzzleSize, int instance);
std::ostream& operator<<(std::ostream& os, Output output);

int getGoalTilePosition(unsigned long long tile);
int getRow(int position);
int getColumn(int position);


