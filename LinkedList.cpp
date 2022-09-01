#include "LinkedList.h"

LinkedList::LinkedList(){
    head = nullptr;
}

LinkedList::~LinkedList(){
    while (head != nullptr)
    {
        Node *temp = head->next;
        delete head;
        head = temp;
    }
}

void LinkedList::insert(Rubik *cube, int code){
    Node *node = new Node(cube, code);
    node->next = head;
    head = node;
}

bool LinkedList::isInList(Rubik *cube, int code)
{
    for(Node *current = head; current != nullptr; current = current->next){
        if(current->code == code && cube->equals(current->cube)){
            return true;
        }
    }
    return false;
}