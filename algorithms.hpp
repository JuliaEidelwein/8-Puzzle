#include <deque>
#include <set>
#include <stack>
#include <climits>
#include <queue>
#include "puzzle.hpp"

Output BFS_Graph(State initialState);

Output IterativeDeepening_DFS(State initialState);
Output depth_limited_search(State state, int depth_limit);

Output Astar(State initialState);

class AstarComparator{
    public:
    bool operator() (Node n1, Node n2);
};
