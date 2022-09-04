#include "Node.h"

class LinkedList{
private:
    Node *head;
public:
    LinkedList();
    ~LinkedList();
    void insert(Rubik *cube, int code);
    bool isInList(Rubik *cube, int code);
    void print();
};
