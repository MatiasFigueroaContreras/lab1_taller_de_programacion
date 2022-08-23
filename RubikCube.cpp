#include "RubikCube.h"
#include "RubikSide.h"

RubikCube::RubikCube(){
    up = new RubikSide(0);
    down = new RubikSide(1);
    right = new RubikSide(2);
    left = new RubikSide(3);
    front = new RubikSide(4);
    back = new RubikSide(5);
}

void RubikCube::move(int direction, char side)
{
    switch (side)
    {
    case 'U':
        
        up->rotate(direction);
        break;
    case 'D':
        down->rotate(direction);
        break;
    case 'R':
        right->rotate(direction);
        break;
    case 'L':
        left->rotate(direction);
        break;
    case 'F':
        front->rotate(direction);
        break;
    case 'B':
        back->rotate(direction);
        break;

    default:
        break;
    }
}

void RubikCube::disarm(){

}

bool RubikCube::isArm(){
    return up->isSameColor() && down->isSameColor() && right->isSameColor() && left->isSameColor() && front->isSameColor() && back->isSameColor();
}