#include "HashTable.h"

HashTable::HashTable(int initialMaxLength){
    table = (LinkedList **)malloc(initialMaxLength * sizeof(LinkedList *));
    for (int i = 0; i < initialMaxLength; i++)
    {
        table[i] = new LinkedList();
    }
    length = initialMaxLength;
}

HashTable::~HashTable()
{
    for (int i = 0; i < length; i++)
    {
        delete table[i];
    }
    free(table);
}

int HashTable::hashFunction(int key)
{
    return key % length;
}

void HashTable::increaseSpace(){

}

void HashTable::add(Rubik *cube){
    int code = cube->getValue();
    int i = hashFunction(code);
    table[i]->insert(cube, code);
}

bool HashTable::isInTable(Rubik *cube){
    int code = cube->getValue();
    int i = hashFunction(code);
    return table[i]->isInList(cube, code);
}
