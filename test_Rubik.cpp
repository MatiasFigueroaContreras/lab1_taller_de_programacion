#include "Rubik.h"

int main(){
    Rubik *cube = new Rubik();
    cube->print();
    Rubik *cube2 = cube->rotate(1, 'U');
    Rubik *cube3 = cube2->rotate(1, 'D');
    Rubik *cube4 = cube3->rotate(-1, 'F');
    Rubik *cube5 = cube4->rotate(1, 'B');
    Rubik *cube6 = cube5->rotate(-1, 'L');
    Rubik *cube7 = cube6->rotate(-1, 'R');
    cube7->print();
    Rubik *cubeCopy = cube->copy();
    cube->disarm();
    cube->print();
    std::cout << cube2->isSolved() << std::endl;
    std::cout << cubeCopy->isSolved() << std::endl;
    std::cout << cube5->getValue() << std::endl;
    std::cout << cube4->equals(cube2) << std::endl;
    std::cout << cube6->equals(cube7->rotate(1, 'R')) << std::endl;
}
