#include "Node.h"

int main(){
    Rubik *cube = new Rubik();
    Node *n1 = new Node(cube, 3);
    Node *n2 = new Node(cube->rotate(-1, 'D'), 15);
    n1->next = n2;

    std::cout << n1->code << std::endl;
    std::cout << n1->next->code << std::endl;
}