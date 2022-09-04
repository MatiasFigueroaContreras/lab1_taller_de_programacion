#include "LinkedList.h"
/*
    Metodo: Constructor
    Descripcion: este metodo permite crear una lista enlazada.
    Retorno: La direccion del objeto creado.
*/
LinkedList::LinkedList(){
    head = nullptr;
}

/*
    Metodo: Destructor
    Descripcion: este metodo permite eliminar la  lista enlazada,
        liberando la memoria en donde se encuentra esta.
    Retorno: vacio.
*/
LinkedList::~LinkedList(){
    while (head != nullptr){
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

/*
    Metodo:
    Descripcion: este metodo permite agregar un nodo creado con 
        un cubo Rubik y su codigo asociado dado, al principio
        de la lista enlazada.
    Parametros:
        -cube: cubo Rubik que sera parte del nodo a agregar.
        -code: codigo asociado al cubo Rubik que sera parte del
            nodo a agregar.
    Retorno: vacio.
*/
void LinkedList::insert(Rubik *cube, int code){
    Node *node = new Node(cube, code);
    node->next = head;
    head = node;
}

/*
    Metodo:
    Descripcion: permite saber si el cubo dado con su codigo
        asociado esta en la lista enlazada.
    Parametros:
        -cube: cubo a revisar en la lista enlazada.
        -code: codigo asociado al cubo Rubik a revisar
            en la lista enlazada.
    Retorno:
        -true: si el cubo esta en la lista enlazada.
        -false: si el cubo no esta en la lista enlazada.
*/
bool LinkedList::isInList(Rubik *cube, int code){
    for(Node *current = head; current != nullptr; current = current->next){
        if(current->code == code && cube->equals(current->cube)){
            return true;
        }
    }
    return false;
}

/*
    Metodo:
    Descripcion: imprime los codigos de los nodos pertenecientes
        a la lista enlazada.
    Retorno: vacio.
*/
void LinkedList::print(){
    for (Node *current = head; current != nullptr; current = current->next){
        std::cout << current->code << std::endl;
    }
}
