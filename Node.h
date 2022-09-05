#include "Rubik.h"

class Node
{
public:
    Rubik *cube;
    int code;
    Node *next;
    Node(Rubik *cube, int code);
    ~Node();
};
