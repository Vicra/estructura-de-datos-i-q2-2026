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
    void insert(string val);
    void deleteByIndex(int pos);
    void print();
};

#endif // DOUBLELINKEDLIST_H
