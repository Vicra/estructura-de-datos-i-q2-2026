#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"

class Queue
{
public:
    Queue();

    // properties
    Node* head;
    Node* tail;

    // operations or functions
    void enqueue(int x);// insert
    int dequeue(); // delete
    void print();
    int peek(); // head
    int rear();// tail
};

#endif // QUEUE_H
