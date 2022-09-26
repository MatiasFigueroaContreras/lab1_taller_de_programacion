#include "RubikSolver.h"

int main()
{
    RubikSolver *rs = new RubikSolver();

    Rubik *cube = new Rubik();

    cube->disarm(1000);
    cube->print();
    //Resolucion Parcial 1, con su Heuristica y punto de parada asociado
    State *starting = new State(cube, nullptr, 0, ' ', 0);
    State *o = rs->partialSolve(starting, 1);
    o->printPath();
    o->cube->print();
    // Resolucion Parcial 2, con su Heuristica y punto de parada asociado
    State *o2 = rs->partialSolve(o, 2);
    o2->printPath();
    o2->cube->print();
    // Resolucion Parcial 3, con su Heuristica y punto de parada asociado
    State *o3 = rs->partialSolve(o2, 3);
    o3->printPath();
    o3->cube->print();
    // Resolucion Parcial 4, con su Heuristica y punto de parada asociado
    State *o4 = rs->partialSolve(o3, 4);
    o4->printPath();
    o4->cube->print();
    // Resolucion Parcial 5, con su Heuristica y punto de parada asociado
    State *o5 = rs->partialSolve(o4, 5);
    o5->printPath();
    o5->cube->print();
    // Resolucion Parcial 6, con su Heuristica y punto de parada asociado
    State *o6 = rs->partialSolve(o5, 6);
    o6->printPath();
    o6->cube->print();
    // Resolucion Parcial 7, con su Heuristica y punto de parada asociado
    State *o7 = rs->partialSolve(o6, 7);
    o7->printPath();
    o7->cube->print();
    // Resolucion Parcial 8, con su Heuristica y punto de parada asociado
    State *o8 = rs->partialSolve(o7, 8);
    o8->printPath();
    o8->cube->print();
    // Resolucion Parcial 9, con su Heuristica y punto de parada asociado
    State *o9 = rs->partialSolve(o8, 9);
    o9->printPath();
    o9->cube->print();
    // Resolucion Parcial 10, con su Heuristica y punto de parada asociado
    State *o10 = rs->partialSolve(o9, 10);
    o10->printPath();
    o10->cube->print();

    // Rubik *finalCube = new Rubik();
    // finalCube->disarm(1000);
    // rs->solve(finalCube);
}
