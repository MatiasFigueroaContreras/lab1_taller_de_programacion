#include "HashTable.h";

HashTable::HashTable(int initialMaxLength){
    table = (LinkedList **)malloc(initialMaxLength * sizeof(LinkedList *));
}

HashTable::~HashTable()
{
}

int HashTable::hashCode(Rubik *cube)
{
    int u = 0, d = 0, l = 0, r = 0, f = 0, b = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            u += cube->U[i][j];
            d += cube->D[i][j];
            l += cube->L[i][j];
            r += cube->R[i][j];
            f += cube->F[i][j];
            b += cube->B[i][j];
        }
    }
    return u * 1 + d * 2 + l * 3 + r * 4 + f * 5 + b * 6;
}

int HashTable::hashFunction(int key)
{
    return key % length;
}

void HashTable::increaseSpace(){

}

void HashTable::add(Rubik *cube){
    int code = hashCode(cube);
    int i = hashFunction(code);
    table[i]->insert(cube, code);
}

bool HashTable::isInTable(Rubik *cube){
    int code = hashCode(cube);
    int i = hashFunction(code);
    return table[i]->isInList(cube, code);
}
