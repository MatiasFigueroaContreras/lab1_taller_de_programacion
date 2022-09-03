#include "LinkedList.h"

LinkedList::LinkedList(){
    head = nullptr;
}

LinkedList::~LinkedList(){
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
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

void LinkedList::print(){
    for (Node *current = head; current != nullptr; current = current->next)
    {
        std::cout << current->code << std::endl;
    }
}