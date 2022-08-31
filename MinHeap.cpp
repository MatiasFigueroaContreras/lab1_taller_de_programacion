#include "MinHeap.h"

MinHeap::MinHeap(int initialMaxLength)
{
    maxLength = initialMaxLength;
    length = 0;
    cubesState = (State **)malloc(maxLength * sizeof(State *));
    scores = (int*) malloc(maxLength*sizeof(int));
}

MinHeap::~MinHeap()
{
    free(cubesState);
    free(scores);
}

int MinHeap::leftChildIndex(int i)
{
    return 2*i + 1;
}

int MinHeap::rightChildIndex(int i)
{
    return 2 * i + 2;
}

int MinHeap::parentIndex(int i)
{
    return (i-1)/2;
}

int MinHeap::minChildIndex(int i)
{
    int l = leftChildIndex(i);
    int r = rightChildIndex(i);

    if(l > length){
        return i;
    }
    if(r > length || scores[l] < scores[r]){
        return l;
    }
    else{
        return r;
    }
}

void MinHeap::swap(int i, int j){
    State* rTemp = cubesState[i];
    cubesState[i] = cubesState[j];
    cubesState[j] = rTemp;

    int sTemp = scores[i];
    scores[i] = scores[j];
    scores[j] = sTemp;
}

void MinHeap::increaseSpace(){
    maxLength *= 2;
    scores = (int *)realloc(scores, maxLength*sizeof(int));
    cubesState = (State **)realloc(cubesState, maxLength * sizeof(State *));
}

void MinHeap::insert(int score, State *state)
{
    if(length == maxLength){
        increaseSpace();
    }

    cubesState[length] = state;
    scores[length] = score;
    
    for(int i = length; i > 0 && scores[parentIndex(i)] > scores[i]; i = parentIndex(i)){
        swap(i, parentIndex(i));
    }

    length++;
}

State *MinHeap::pull(){
    if(length == 0){
        return nullptr;
    }
    State *min = cubesState[0];
    length--;
    cubesState[0] = cubesState[length];
    scores[0] = scores[length];

    int j;
    for (int i = 0; i < length && scores[minChildIndex(i)] != scores[i]; i = j)
    {
        j = minChildIndex(i);
        swap(i, j);
    }

    return min;
}

void MinHeap::printAux(int i, int c){
    if (i >= length)
    {
        return;
    }

    c += 10;
    printAux(rightChildIndex(i), c);
    std::cout << std::endl;
    for(int i = 10; i < c; i++){
        std::cout << " ";
    }

    std::cout << scores[i] << "\n";
    printAux(leftChildIndex(i), c);
}

void MinHeap::print(){
    std::cout << "-----------HEAP-----------" << std::endl;
    printAux(0, 0);
    std::cout << "--------------------------" << std::endl;
}
