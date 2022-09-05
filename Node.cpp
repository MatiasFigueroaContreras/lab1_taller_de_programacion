#include "Node.h"
/*
    Descripcion de la clase Node:
    Esta clase representa un nodo el cual contendra
    el puntero a la direccion de un cubo Rubik y un
    codigo que estara asociado a este cubo Rubik de
    alguna manera, ademas permitira vincular a un
    nodo proximo mediante un puntero a este.
*/

/*
    Metodo: Constructor
    Descripcion: este metodo permite crear un nodo con el
        cubo Rubik y su respectivo codigo asociado
    Parametros:
        -cube: Rubik que contendra el nodo.
        -code: codigo asociado al cubo Rubik que contendra
            el nodo.
    Retorno: La direccion del objeto creado.
*/
Node::Node(Rubik *cube, int code)
{
    this->cube = cube;
    this->code = code;
    this->next = nullptr;
}

Node::~Node()
{
}
