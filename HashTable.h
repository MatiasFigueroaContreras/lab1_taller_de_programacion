#include "LinkedList.h"

class HashTable
{
private:
    int length;
    LinkedList **table;
    int hashFunction(int key);

public:
    HashTable(int maxLenght);
    ~HashTable();
    void add(Rubik *cube);
    bool isInTable(Rubik *cube);
};
