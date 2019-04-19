#include <deque>
#include <set>
#include <stack>
#include <climits>
#include <queue>
#include <unordered_set>
#include "puzzle.hpp"

Output BFS_Graph(State *initialState);

Output IterativeDeepening_DFS(State *initialState);
Output depth_limited_search(State *state, int depth_limit, unsigned long long parent, Output *output);

Output Astar(State *initialState);

class AstarComparator{
    public:
    bool operator() (Node n1, Node n2);
};

Output Greedy_bestFirst_search(State *initialState);

class GreedyBFSComparator{
    public:
    bool operator() (Node n1, Node n2);
};

Output IDAstar(State *initialState);

std::pair <int, Output> ida_recursive_search(Node n, int f_limit, Output output, unsigned long long parent);
