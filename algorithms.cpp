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
                //std::cout << nodeIdCounter << ',' << n1.cost;
                output.time = clock() - startTime;
                output.optimalSolutionSize = n1.cost;
                return output;
            }
            if(closed.find(s->value) == closed.end()){//https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key
                closed.insert(s->value);
                open.push_back(n1);
            }

        }
    }
    output.time = clock() - startTime;
    output.optimalSolutionSize = -1; //choosen representation for unsolvable
    return output;
}

Output IterativeDeepening_DFS(State initialState){
    Output output;
    output.heuristicInitialState = initialState.heuristicValue;
    time_t startTime = clock();
    for(int depth_limit = 0; depth_limit < 100; depth_limit++){
        Output output = depth_limited_search(initialState, depth_limit);
        //std::cout << "Profundidade " << depth_limit << std::endl;
        if(output.optimalSolutionSize != -1){
            output.time = clock() - startTime;
            return output;
        }
    }
}


//TO-DO: improve algorithm, it gets extremely slow after depth 14
Output depth_limited_search(State state, int depth_limit){
    Output output;
    output.optimalSolutionSize = -1;
    //std::cout << "Profundidade " << depth_limit << std::endl;
    if(state.isGoal()){
        output.optimalSolutionSize = 0;
        return output;
    }
    if(depth_limit > 0){
        for(auto s: state.generate_successors()){
            output = depth_limited_search(*s, depth_limit - 1);
            if(output.optimalSolutionSize != -1){
                output.optimalSolutionSize = depth_limit;
                output.heuristicInitialState = state.heuristicValue;
                return output;
            }
        }
    }
    return output;
}


/*
Output depth_limited_search(State state, int depth_limit){
    Output output;
    output.optimalSolutionSize = -1;
    std::stack<Node> open;
    open.push(Node(state, 0));
    //std::cout << "Profundidade " << depth_limit << std::endl;
    while(!open.empty()){
        Node n = open.top(); //gets first member, but does not take it out of the deque
        open.pop();
        if(n.state.isGoal()){
            output.optimalSolutionSize = 0;
            return output;
        }
        if(depth_limit > 0){
            for(auto s: state.generate_successors()){
                Node n1 = Node(*s, n.cost + 1);
                open.push(n1);
                output = depth_limited_search(*s, depth_limit - 1);
                if(output.optimalSolutionSize != -1){
                    output.optimalSolutionSize = depth_limit;
                    output.heuristicInitialState = state.heuristicValue;
                    return output;
                }
            }
        }
    }
    return output;
}
*/

//Priority: fValue > hValue > LIFO
bool AstarComparator::operator() (Node n1, Node n2){
    //First tries to tie with f
    int difference = (n1.state.heuristicValue + n1.cost) - (n2.state.heuristicValue + n2.cost);
    if(difference > 0)
        return true;
    else if(difference < 0)
        return false;
    //f is equal, tries with h
    difference = n1.state.heuristicValue - n2.state.heuristicValue;
    if(difference > 0)
        return true;
    else if(difference < 0)
        return false;
    //h is also equal, uses LIFO
    return n1.id < n2.id;
}


//Manhattan distance is admissible and consistent,
//so we implemented A* without reopening
Output Astar(State initialState){
    Output output;
    output.heuristicInitialState = initialState.heuristicValue;
    time_t startTime = clock();
    std::priority_queue<Node, std::vector<Node>, AstarComparator> open;
    if(initialState.heuristicValue < INT_MAX){
        open.push(Node(initialState, 0));
    }
    std::set<unsigned long long> closed;
    while(!open.empty()){
        Node n = open.top();
        open.pop();
        if(closed.find(n.state.value) == closed.end()){//https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key
            closed.insert(n.state.value);
            if(n.state.isGoal()){
                output.time = clock() - startTime;
                output.optimalSolutionSize = n.cost;
                return output;
            }
            output.expandedNodes++;
            for(auto s: n.state.generate_successors()){
                if(s->heuristicValue < INT_MAX){
                    Node n1 = Node(*s, n.cost + 1);
                    open.push(n1);
                }
            }
        }
    }
    output.time = clock() - startTime;
    output.optimalSolutionSize = -1; //choosen representation for unsolvable
    return output;
}
