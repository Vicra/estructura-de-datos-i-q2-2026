#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "node.h"

class LinkedList
{
public:
    // properties
    Node* head; // root
    Node* tail;

    // functions
    void insert(int newValue);
    void pushFront(int newValue);
    void print();
    void remove(int x);

    LinkedList();
};

#endif // LINKEDLIST_H
