#include "algorithms.hpp"

int globalPuzzleSize;
unsigned long long nodeIdCounter;

int BFS_Graph(State initialState){
    if(initialState.isGoal()){
        return 1;
    }
    std::deque<Node> open;
    open.push_back(Node(initialState, 0));
    std::set<unsigned long long> closed; //Hash set
    closed.insert(initialState.value);
    while(!open.empty()){
        Node n = open.front(); //gets first member, but does not take it out of the deque
        open.pop_front(); //pop_front() only deletes the first member, returning void
        for(auto s: n.state.generate_successors()){
            Node n1 = Node(*s, n.cost + 1);
            if(s->isGoal()){
                std::cout << nodeIdCounter << ',' << n.cost;
                return 1;
            }
            if(closed.find(s->value) == closed.end()){//https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key
                closed.insert(s->value);
                open.push_back(n1);
            }

        }
    }
    return 0;
}
