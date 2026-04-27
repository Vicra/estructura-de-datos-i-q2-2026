#ifndef STACKLL_H
#define STACKLL_H
#include "node.h"

class StackLL
{
public:
    StackLL();

    // properties
    Node* head;

    // operations
    // fn: insert - push
    void push(int x);

    // fn: remove - pop
    int pop();

    void print();

    void peek();

    void clear();
};

#endif // STACKLL_H
