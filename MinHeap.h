#include <iostream>
#include "Rubik.h"

class MinHeap
{
private:
    Rubik **rubiks;
    int *scores;
    int maxLength;
    int length;

    int leftChildIndex(int i);
    int rightChildIndex(int i);
    int parentIndex(int i);
    int minChildIndex(int i);
    void swap(int i, int j);
    void increaseSpace();
public:
    MinHeap(int initialMaxLength);
    ~MinHeap();
    void insert(int score, Rubik *r);
    Rubik *getMinRubik();
};
