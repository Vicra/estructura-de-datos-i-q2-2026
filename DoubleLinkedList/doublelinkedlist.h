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
    // TODO: insert by index
    void print();
    void pushFront(string x);
    bool searchBackwards(string x);
    void reverse();

    // by reference methods
    void insertAfterNode(Node *reference, string val);
    // insertBeforeNode(ref, val)
    void deleteByReference(Node *reference);
    // delete by reference
    // insert start

};

#endif // DOUBLELINKEDLIST_H
