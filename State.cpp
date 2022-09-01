#include "State.h"

State::State(Rubik *cube, State *previous, int depth, char move, int clockWise)
{
    this->cube = cube;
    this->previous = previous;
    this->depth = depth;
    this->move = move;
    this->cw = clockWise;
}

State::~State(){

}

void State::printPath(){
    for(State *current = this; current != nullptr; current = current->previous){
        std::cout << current->move;
        if(current->cw == -1){
            std::cout << "'";
        }
        std::cout << std::endl;
    }
}