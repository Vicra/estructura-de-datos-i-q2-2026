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

    // TODO: terminar delete by index
    void deleteByIndex(int pos);
    void print();
    void pushFront(string x);
    bool searchBackwards(string x);
    void reverse();

    // by reference methods
    void insertAfterNode(Node *reference, string val);
    void deleteByReference(Node *reference);
    // delete by reference
    // insert start

};

#endif // DOUBLELINKEDLIST_H
