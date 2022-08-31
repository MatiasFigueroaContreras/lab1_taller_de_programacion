#include "Rubik.h"

class State
{
private:
    Rubik *cube;
    State *previous;
    int depth;
    char move;
    int cw;
public:
    State(Rubik *cube, State *previous, int depth, char move, int cw);
    ~State();
};

