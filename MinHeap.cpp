#include "MinHeap.h"

MinHeap::MinHeap(int initialMaxLength)
{
    maxLength = initialMaxLength;
    length = 0;
    *rubiks = new Rubik[maxLength];
    scores = new int[maxLength];
}

MinHeap::~MinHeap()
{
    delete rubiks;
    delete scores;
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
    int r = leftChildIndex(i);

    if(l < length){
        return i;
    }
    if(r < length || scores[l] < scores[r]){
        return l;
    }
    else{
        return r;
    }
}

void MinHeap::swap(int i, int j){
    Rubik* rTemp = rubiks[i];
    rubiks[i] = rubiks[j];
    rubiks[j] = rTemp;

    int sTemp = scores[i];
    scores[i] = scores[j];
    scores[j] = sTemp;
}

void MinHeap::increaseSpace(){
    maxLength *= 2;
    scores = (int *)realloc(scores, maxLength);
    rubiks = (Rubik **)realloc(rubiks, maxLength);
}

void MinHeap::insert(int score, Rubik *r)
{
    if(length == maxLength){
        increaseSpace();
    }

    rubiks[length] = r;
    scores[length] = score;
    
    for(int i = length; i > 0 && scores[parentIndex(i)] > scores[i]; i = parentIndex(i)){
        swap(i, parentIndex(i));
    }

    length++;
}

Rubik *MinHeap::getMinRubik(){
    if(length = 0){
        return nullptr;
    }
    Rubik *min = rubiks[0];
    length--;
    rubiks[0] = rubiks[length];
    scores[0] = scores[length];

    for (int i = 0; i < length && scores[minChildIndex(i)] > scores[i]; i = minChildIndex(i))
    {
        swap(i, minChildIndex(i));
    }

    return rubiks[0];
}
