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
    unsigned long long value;
    int zeroPosition;
    int heuristicValue;
    std::vector<std::shared_ptr<State>> successors;

    std::vector<std::shared_ptr<State>> generate_successors();
    bool isGoal();
    int heuristicFunction();

};


class Node{
    public:
    unsigned long long id;
    State state;
    int cost;

    Node(State state, int cost);
};

class Output{
    public:
    unsigned long long expandedNodes = 1;
    int optimalSolutionSize = 0;
    time_t time;
    float averageHeuristicValue = 0;
    int heuristicInitialState;
};


State fill_initial_state(unsigned long long initialState, char* argv[], int puzzleSize, int instance);
std::ostream& operator<<(std::ostream& os, Output output);

int getGoalTilePosition(unsigned long long tile);
int getRow(int position);
int getColumn(int position);


