#ifndef STACK_H
#define STACK_H

#include "NodeStack.h"

class Stack {
public:
    Stack();
    ~Stack();

    void push(int value);
    void pop();
    void clear();
    int peek();
    bool isEmpty() const;
    NodeStack* getTop() const;

private:
    NodeStack* top;
};

#endif // STACK_H
