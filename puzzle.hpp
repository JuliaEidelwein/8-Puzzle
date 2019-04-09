enum moves{UP, DOWN, LEFT, RIGHT};

unsigned long long fill_initial_state(unsigned long long initialState, char* argv[], int puzzleSize, int instance);

unsigned long long generate_successors(unsigned long long state, int zeroPosition, int direction);
