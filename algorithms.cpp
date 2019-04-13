#include "algorithms.hpp"

int globalPuzzleSize;
unsigned long long nodeIdCounter;

Output BFS_Graph(State initialState){
    Output output;
    output.heuristicInitialState = initialState.heuristicValue;
    time_t startTime = clock();
    if(initialState.isGoal()){
        output.time = clock() - startTime;
        output.optimalSolutionSize = 0;
        return output;
    }
    std::deque<Node> open;
    open.push_back(Node(initialState, 0));
    std::set<unsigned long long> closed; //Hash set
    closed.insert(initialState.value);
    while(!open.empty()){
        Node n = open.front(); //gets first member, but does not take it out of the deque
        open.pop_front(); //pop_front() only deletes the first member, returning void
        output.expandedNodes++;
        for(auto s: n.state.generate_successors()){
            Node n1 = Node(*s, n.cost + 1);
            if(s->isGoal()){
                output.expandedNodes++;
                std::cout << nodeIdCounter << ',' << n1.cost;
                output.time = clock() - startTime;
                output.optimalSolutionSize = n1.cost;
                return output;
            }
            if(closed.find(s->value) == closed.end()){//https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key
                output.expandedNodes++;
                closed.insert(s->value);
                open.push_back(n1);
            }

        }
    }
    output.time = clock() - startTime;
    output.optimalSolutionSize = -1; //choosen representation for unsolvable
    return output;
}
