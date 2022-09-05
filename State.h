#include "Rubik.h"

class State
{
private:
public:
    Rubik *cube;
    State *previous;
    int depth;
    char move;
    int cw;
    State(Rubik *cube, State *previous, int depth, char move, int cw);
    ~State();
    void printPath();
};
