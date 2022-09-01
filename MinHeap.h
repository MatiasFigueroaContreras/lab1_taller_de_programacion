#include <iostream>
#include "State.h"

class MinHeap
{
private:
    State **cubesState;
    int *scores;
    int maxLength;
    int length;

    int leftChildIndex(int i);
    int rightChildIndex(int i);
    int parentIndex(int i);
    int minChildIndex(int i);
    void swap(int i, int j);
    void increaseSpace();
    void printAux(int i, int c);
public:
    MinHeap(int initialMaxLength);
    ~MinHeap();
    void insert(int score, State *state);
    State *pull();
    bool isEmpty();
    void print();
};
