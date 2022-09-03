#include "RubikSolver.h"

int main(){
    RubikSolver *rs = new RubikSolver();

    Rubik *cube = new Rubik();
    rs->solve(cube);

    Rubik *cube2 = cube->rotate(-1, 'U');
    rs->solve(cube2);

    Rubik *cube3 = cube2->rotate(1, 'F');
    rs->solve(cube3);

    Rubik *cube4 = cube3->rotate(1, 'L');
    rs->solve(cube4);
}
