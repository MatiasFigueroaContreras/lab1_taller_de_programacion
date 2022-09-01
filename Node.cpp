#include "Node.h"

Node::Node(Rubik *cube, int code){
    this->cube = cube;
    this->code = code;
    this->next = nullptr;
}

Node::~Node()
{
}