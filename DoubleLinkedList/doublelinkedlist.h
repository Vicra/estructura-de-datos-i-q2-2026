#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "node.h"

class DoubleLinkedList
{
public:
    DoubleLinkedList();

    // props
    Node* head;
    Node* tail;
    int size;

    // operations
    void insert(string val);// push back
    void deleteByIndex(int pos);
    void print();
    void pushFront(string x);
    bool searchBackwards(string x);
};

#endif // DOUBLELINKEDLIST_H
