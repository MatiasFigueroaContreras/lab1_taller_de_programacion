#include "State.h"

int main(){
    Rubik *cube = new Rubik();
    State *s1 = new State(cube, nullptr, 0, '-', 0);
    Rubik *cube2 = cube->rotate(-1, 'R');
    State *s2 = new State(cube2, s1, 1, 'R', -1);
    State *s3 = new State(cube2->rotate(1, 'F'), s2, 2, 'F', 1);

    s3->printPath();
}
