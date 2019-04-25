# 8-Puzzle
Implementation of heurisitic search algorithms to solve 8-puzzle and 15-puzzle

### The puzzle
From [Wikipedia article](https://en.wikipedia.org/wiki/15_puzzle):
>The 15-puzzle is a sliding puzzle that consists of a frame of numbered square tiles in random order with one tile missing. The puzzle also exists in other sizes, particularly the smaller 8-puzzle. If the size is 3×3 tiles, the puzzle is called the 8-puzzle or 9-puzzle, and if 4×4 tiles, the puzzle is called the 15-puzzle or 16-puzzle named, respectively, for the number of tiles and the number of spaces. The object of the puzzle is to place the tiles in order by making sliding moves that use the empty space.

### Representation
The Puzzle is originally a 2D grid (the blank space is represented by the 0 tile).
At this project, we flatened this grid into a 1D vector.   
As we had to optimize our representation to use as least bits as possible (due to the huge size of the state space), we chose to use 4 bits for each tile (as we have at most 16 tiles, 4 bits are enough to represent all of them).  
Because C++ does not have a type with only 4 bits (_int_ has 8 bits), we used a single _unsigned long long_ (64 bits wide) instead of a vector, using 4 bits for each of the 16 tiles (4x16 = 64 bits).

<pre>
[0][1][2]  
[3][4][5]  --> 0 1 2 3 4 5 6 7 8 --> 0000 0001 0010 0011 0100 0101 0110 0111 1000  
[6][7][8]  

[ 0][ 1][ 2][ 3]  
[ 4][ 5][ 6][ 7] --> 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 --> 0000 0001 0010 0011 0100 0101 0110 0111...  
[ 8][ 9][10][11]                                           ...1000 1001 1010 1011 1100 1101 1110 1111     
[12][13][14][15]  
</pre>
Since we chose such a kind of representation, bitwise operations became needed to generate neighbor states and calculate the heuristic value of each state.   
We mark each position in the following order:
<pre>
[8][7][6]
[5][4][3] --> 8 7 6 5 4 3 2 1 0, which means the number of shifts needed to reach that position
[2][1][0]
</pre>
