#include "algorithms.hpp"

int globalPuzzleSize;
unsigned long long nodeIdCounter;

Output BFS_Graph(State *initialState){
    Output output;
    output.heuristicInitialState = initialState->heuristicValue;
    time_t startTime = clock();
    if(initialState->isGoal()){
        output.time = clock() - startTime;
        output.optimalSolutionSize = 0;
        return output;
    }
    std::deque<Node> open;
    open.push_back(Node(initialState, 0));
    std::set<unsigned long long> closed; //Hash set
    closed.insert(initialState->value);
    while(!open.empty()){
        Node n = open.front(); //gets first member, but does not take it out of the deque
        open.pop_front(); //pop_front() only deletes the first member, returning void
        output.expandedNodes++;
        for(State* s: n.state->generate_successors()){
            Node n1 = Node(s, n.cost + 1);
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

Output IterativeDeepening_DFS(State *initialState){
    Output output;
    output.heuristicInitialState = initialState->heuristicValue;
    time_t startTime = clock();
    for(int depth_limit = 0; depth_limit < 100; depth_limit++){
        output = depth_limited_search(initialState, depth_limit, 0, &output);
        //std::cout << "Profundidade " << depth_limit << std::endl;
        if(output.optimalSolutionSize != -1){
            output.time = clock() - startTime;
            return output;
        }
    }
}


Output depth_limited_search(State *state, int depth_limit, unsigned long long parent, Output *output){
    //std::cout << "Profundidade " << depth_limit << std::endl;
    if(state->isGoal()){
        output->optimalSolutionSize = 0;
        return *output;
    }
    if(depth_limit > 0){
        output->expandedNodes++;
        for(State* s: state->generate_successors(parent)){
            *output = depth_limited_search(s, depth_limit - 1, state->value, output);
            if(output->optimalSolutionSize != -1){
                output->optimalSolutionSize = depth_limit;
                output->heuristicInitialState = state->heuristicValue;
                return *output;
            }
        }
    }
    output->optimalSolutionSize = -1;
    return *output;
}


//Priority: fValue > hValue > LIFO
bool AstarComparator::operator() (Node n1, Node n2){
    //First tries to tie with f
    int n1Value = (n1.state->heuristicValue + n1.cost);
    int n2Value = (n2.state->heuristicValue + n2.cost);
    if(n1Value > n2Value)
        return true;
    else if(n1Value < n2Value)
        return false;
    //f is equal, tries with h
    n1Value = n1.state->heuristicValue;
    n2Value = n2.state->heuristicValue;
    if(n1Value > n2Value)
        return true;
    else if(n1Value < n2Value)
        return false;
    //h is also equal, uses LIFO
    return n1.id < n2.id;
}


//Manhattan distance is admissible and consistent,
//so we implemented A* without reopening
Output Astar(State *initialState){
    //unsigned long long parent = 0;
    Output output;
    output.heuristicInitialState = initialState->heuristicValue;
    time_t startTime = clock();
    std::priority_queue<Node, std::vector<Node>, AstarComparator> open;
    if(initialState->heuristicValue < INT_MAX){
        open.push(Node(initialState, 0));
        output.generatedNodes++;
        output.heuristicSum = output.heuristicSum + initialState->heuristicValue;
    }
    std::unordered_set<unsigned long long> closed;
    while(!open.empty()){
        Node n = open.top();
        open.pop();
        if(closed.find(n.state->value) == closed.end()){//https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key
            closed.insert(n.state->value);
            if(n.state->isGoal()){
                output.time = clock() - startTime;
                output.averageHeuristicValue = (float)output.heuristicSum/output.generatedNodes;
                output.optimalSolutionSize = n.cost;
                return output;
            }
            output.expandedNodes++;

            for(State* s: n.state->generate_successors()){
                if(s->heuristicValue < INT_MAX){
                    output.heuristicSum = output.heuristicSum + s->heuristicValue;
                    Node n1 = Node(s, n.cost + 1);
                    output.generatedNodes++;
                    open.push(n1);
                }
            }
            //parent = n.state->value;
        }
    }
    output.time = clock() - startTime;
    output.averageHeuristicValue = (float)output.heuristicSum/output.generatedNodes;
    output.optimalSolutionSize = -1; //choosen representation for unsolvable
    return output;
}

//Priority: hValue > LIFO
bool GreedyBFSComparator::operator() (Node n1, Node n2){
    int n1Value = n1.state->heuristicValue;
    int n2Value = n2.state->heuristicValue;
    //Uses heuristic value
    if(n1Value > n2Value)
        return true;
    else if(n1Value < n2Value)
        return false;
    //If they are equal, uses LIFO
    return n1.id < n2.id;
}

Output Greedy_bestFirst_search(State *initialState){
    //unsigned long long parent = 0;
    Output output;
    output.heuristicInitialState = initialState->heuristicValue;
    time_t startTime = clock();
    std::priority_queue<Node, std::vector<Node>, GreedyBFSComparator> open;
    if(initialState->heuristicValue < INT_MAX){
        open.push(Node(initialState, 0));
        output.heuristicSum = output.heuristicSum + initialState->heuristicValue;
        output.generatedNodes++;
    }
    std::set<unsigned long long> closed;
    while(!open.empty()){
        Node n = open.top();
        open.pop();
        if(closed.find(n.state->value) == closed.end()){//https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key
            closed.insert(n.state->value);
            if(n.state->isGoal()){
                output.time = clock() - startTime;
                output.averageHeuristicValue = (float)output.heuristicSum/output.generatedNodes;
                output.optimalSolutionSize = n.cost;
                return output;
            }
            output.expandedNodes++;
            for(State* s: n.state->generate_successors()){
                if(s->heuristicValue < INT_MAX){
                    output.heuristicSum = output.heuristicSum + s->heuristicValue;
                    Node n1 = Node(s, n.cost + 1);
                    output.generatedNodes++;
                    open.push(n1);
                }
            }
            //parent = n.state->value;
        }
    }
    output.time = clock() - startTime;
    output.averageHeuristicValue = output.heuristicSum/output.generatedNodes;
    output.optimalSolutionSize = -1; //choosen representation for unsolvable
    return output;
}



Output IDAstar(State *initialState){
    Output output;
    time_t startTime = clock();
    output.heuristicInitialState = -1;
    Node n0 = Node(initialState, 0);
    output.heuristicSum = output.heuristicSum + n0.state->heuristicValue;
    output.generatedNodes++;
    output.heuristicInitialState = n0.state->heuristicValue;
    int f_limit = n0.state->heuristicValue;
    while(f_limit < INT_MAX){
        std::pair <int, Output> idaPair = ida_recursive_search(n0,f_limit, &output, 0);
        f_limit = idaPair.first;
        if(idaPair.second.optimalSolutionSize != -1){
            idaPair.second.time = clock() - startTime;
            idaPair.second.averageHeuristicValue = (float)idaPair.second.heuristicSum/idaPair.second.generatedNodes;
            return idaPair.second;
        }
    }
    output.time = clock() - startTime;
    output.optimalSolutionSize = -1;
    return output;
}

std::pair <int, Output> ida_recursive_search(Node n, int f_limit, Output *output, unsigned long long parent){
    int fn = n.cost + n.state->heuristicValue;
    if(fn > f_limit){
        output->optimalSolutionSize = -1;
        return std::make_pair(fn, *output);
    }
    if(n.state->isGoal()){
        output->optimalSolutionSize = n.cost;
        return std::make_pair(-1, *output);
    }
    int next_limit = INT_MAX;
    output->expandedNodes++;
    for(State* s: n.state->generate_successors(parent)){
        if(s->heuristicValue < INT_MAX){
            Node n1 = Node(s, n.cost + 1);
            output->heuristicSum = output->heuristicSum + n1.state->heuristicValue;
            output->generatedNodes++;
            std::pair <int, Output> idaPair = ida_recursive_search(n1,f_limit, output, n.state->value);
            if(idaPair.second.optimalSolutionSize != -1){
                return std::make_pair(-1, idaPair.second);
            }
            next_limit = std::min(next_limit,idaPair.first);
        }

    }
    output->optimalSolutionSize = -1;
    return std::make_pair(next_limit, *output);
}
