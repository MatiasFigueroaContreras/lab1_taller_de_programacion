#include "RubikSolver.h"

int main()
{
    RubikSolver *rs = new RubikSolver();

    Rubik *cube = new Rubik();
    rs->solve(cube);

    Rubik *cube2 = cube->rotate(-1, 'U');
    rs->solve(cube2);

    Rubik *cube3 = cube2->rotate(1, 'F');
    rs->solve(cube3);

    Rubik *cube4 = cube3->rotate(1, 'L');
    rs->solve(cube4);

    cube->disarm();
    cube->print();
    State *starting = new State(cube, nullptr, 0, ' ', 0);
    State *o = rs->partialSolve(starting, 1);
    o->printPath();
    o->cube->print();
    State *o2 = rs->partialSolve(o, 2);
    o2->printPath();
    o2->cube->print();
}
