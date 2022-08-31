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