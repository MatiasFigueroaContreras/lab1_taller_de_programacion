#include "LinkedList.h"

int main(){
    LinkedList *ll = new LinkedList();
    
    Rubik *cube = new Rubik();
    ll->insert(cube, cube->getValue());

    Rubik *cube2 = cube->rotate(1, 'F');
    ll->insert(cube2, cube2->getValue());

    Rubik *cube3 = cube2->rotate(-1, 'R');
    ll->insert(cube3, cube3->getValue());

    std::cout << ll->isInList(cube, cube->getValue()) << std::endl;

    ll->print();

    delete ll;
    delete cube;
    delete cube2;
    delete cube3;
}
