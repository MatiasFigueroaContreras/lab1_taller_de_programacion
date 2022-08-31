#include <iostream>

#include "MinHeap.h"

int main()
{
    // Rubik *r = new Rubik();
    // r->print();

    // r = r->rotate(1, 'U');
    // r->print();

    // r = r->rotate(1, 'U');
    // r->print();

    // r = r->rotate(1, 'D');
    // r->print();

    // r = r->rotate(1, 'F');
    // r->print();

    // r = r->rotate(1, 'F');
    // r->print();

    // r = r->rotate(1, 'R');
    // r->print();

    // r = r->rotate(1, 'L');
    // r->print();
    // std::cout << "\033[1;31m[ ]\033[0m\n";
    // delete r;

    // int a = 1/2;
    // std::cout << a << std::endl;
    // MinHeap *heap = new MinHeap(5);
    // Rubik *r15 = new Rubik();
    // heap->insert(15, r15);

    // Rubik *r12 = r15->rotate(1, 'B');
    // heap->insert(12, r12);

    // Rubik *r28 = r12->rotate(1, 'R');
    // heap->insert(28, r28);

    // Rubik *r33 = r28->rotate(1, 'U');
    // heap->insert(33, r33);

    // Rubik *r6 = r33->rotate(1, 'R');
    // heap->insert(6, r6);

    // heap->print();

    // Rubik *r31 = r6->rotate(1, 'B');
    // heap->insert(31, r31);

    // Rubik *r22 = r31->rotate(1, 'L');
    // heap->insert(22, r22);

    // heap->print();
    // Rubik *min = heap->getMinRubik();
    // min->print();
    

    // min = heap->getMinRubik();
    // heap->print();
    // min->print();

    // delete r12;
    // delete r15;
    // delete r22;
    // delete r28;
    // delete r31;
    // delete r33;
    // delete r6;
    // delete heap;

    // int *arr = new int[15];
    // arr[0] = 15;
    // arr[1] = 10;
    // arr[2] = 1;
    // delete[] arr;
    Rubik *r = new Rubik();
    Rubik *r2 = r->rotate(-1, 'U');
    Rubik *r3 = r2->rotate(-1, 'R');
    Rubik *r4 = r3->rotate(-1, 'R');
    Rubik *r5 = r4->rotate(-1, 'D');

    // r2->print();
    r3->print();
    // r4->print();
    // r5->print();

}

