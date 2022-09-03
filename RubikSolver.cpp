#include "RubikSolver.h"

RubikSolver::RubikSolver(){

}

RubikSolver::~RubikSolver(){

}

void RubikSolver::solve(Rubik *startingCube){
    State *current, *neighborState;
    char faces[6] = {'U', 'D', 'L', 'R', 'F', 'B'};
    int cws[2] = {1, -1};
    Rubik *end = new Rubik();
    MinHeap *open = new MinHeap(10000);
    HashTable *closed = new HashTable(10000);

    State *startingState = new State(startingCube, nullptr, 0, ' ', 0);
    open->insert(0, startingState);
    while (!open->isEmpty())
    {
        current = open->pull();

        if(current->cube->isSolved()){
            current->printPath();
            return;
        }

        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 2; j++){
                if (current->move != faces[i] || current->cw == cws[j])
                {
                    Rubik *neighborCube = current->cube->rotate(cws[j], faces[i]);
                    if (!closed->isInTable(neighborCube))
                    {
                        neighborState = new State(neighborCube, current, current->depth + 1, faces[i], cws[j]);
                        open->insert(current->depth + 1, neighborState); //Falta agregarle el valor heuristico
                    }
                    else{
                        delete neighborCube;
                    }
                }
            }
        }
        closed->add(current->cube);
    }
}