#include "Node.h"
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
Node::Node(Rubik *cube, int code){
    this->cube = cube;
    this->code = code;
    this->next = nullptr;
}

Node::~Node(){
    
}
