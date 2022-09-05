#include "RubikSolver.h"
/*
    Descripcion de la clase RubikSolver:
    Esta clase busca resolver un cubo Rubik mediante
    el algoritmo A* de una forma eficiente.
*/

RubikSolver::RubikSolver()
{
}

RubikSolver::~RubikSolver()
{
}

/*
    Metodo:
    Descripcion: este metodo permite resolver un cubo Rubik dado,
        aplicando el algoritmo A*, y imprimiendo por consola los
        pasos que tomo para resolverlo.
    Parametros:
        -startingCube: Rubik a resolver.
    Retorno: vacio.
*/
void RubikSolver::solve(Rubik *startingCube)
{
    State *current, *neighborState;
    char faces[6] = {'U', 'D', 'L', 'R', 'F', 'B'};
    int cws[2] = {1, -1};                     // Sentidos del reloj para los movimientos.
    MinHeap *open = new MinHeap(10000);       // Heap del cual se obtendran los estados de cubo Rubik más cercanos a la solucion.
    HashTable *closed = new HashTable(10000); // Tabla de Hash en la cual se consultaran los cubos Rubik ya visitados.
    State *startingState = new State(startingCube, nullptr, 0, ' ', 0);
    open->insert(0, startingState);
    while (!open->isEmpty())
    {
        current = open->pull();

        if (current->cube->isSolved())
        {
            current->printPath();
            return;
        }

        for (int i = 0; i < 6; i++)
        {
            // Se iteran los posibles movimientos
            for (int j = 0; j < 2; j++)
            {
                // Se itera el sentido de los movimientos
                if (current->move != faces[i] || current->cw == cws[j])
                {
                    Rubik *neighborCube = current->cube->rotate(cws[j], faces[i]);
                    if (!closed->isInTable(neighborCube))
                    {
                        neighborState = new State(neighborCube, current, current->depth + 1, faces[i], cws[j]);
                        open->insert(current->depth + 1, neighborState); // Falta agregarle el valor heuristico
                    }
                    else
                    {
                        delete neighborCube;
                    }
                }
            }
        }
        closed->add(current->cube);
    }
}
