#include "State.h"
/*
    Descripcion de la clase State:
    Esta clase representa el estado de un cubo rubik
    teniendo informacion relevante para este, como
    el estado anterior, el movimiento con el que
    se llego al cubo actual y el sentido de la rotacion
    de este, la profundidad del movimiento (que tan
    lejos esta del estado inicial), y el cubo resultante.
    Por otra parte, la clase permite imprimir los movimientos
    realizados desde el estado inicial para llegar al estado
    actual.
*/

/*
    Metodo: Constructor
    Descripcion: este metodo permite crear un estado con el
        cubo Rubik, el estado previo, la profundidad, el movimiento,
        y el sentido de este movimiento para llegar al cubo.
    Parametros:
        -cube: Rubik que contendra el estado.
        -previus: estado previo.
        -depth: profundidad del estado.
        -move: movimiento realizado para llegar a el estado actual.
        -clockWise: sentido del movimiento realizado.
    Retorno: La direccion del objeto creado.
*/
State::State(Rubik *cube, State *previous, int depth, char move, int clockWise)
{
    this->cube = cube;
    this->previous = previous;
    this->depth = depth;
    this->move = move;
    this->cw = clockWise;
}

State::~State()
{
}

/*
    Metodo:
    Descripcion: este metodo permite imprimir por consola
        los movimientos necesarios para llegar al estado actual.
    Retorno: vacio.
*/
void State::printPath()
{
    for (State *current = this; current != nullptr; current = current->previous)
    {
        std::cout << current->move;
        if (current->cw == -1)
        {
            std::cout << "'";
        }
        std::cout << std::endl;
    }
}
