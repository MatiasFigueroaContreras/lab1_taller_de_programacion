#include <iostream>
#include "LinkedList.h"

class HashTable
{
private:
    int length;
    LinkedList **table;
    int hashFunction(int key);
    void increaseSpace();
public:
    HashTable(int initialMaxLength);
    ~HashTable();
    void add(Rubik *cube);
    bool isInTable(Rubik *cube);
};
