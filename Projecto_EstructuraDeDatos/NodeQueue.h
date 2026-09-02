#ifndef NODEQUEUE_H
#define NODEQUEUE_H

struct NodeQueue {
    int value;
    NodeQueue* next;

    NodeQueue(int v) : value(v), next(nullptr) {}
};

#endif // NODEQUEUE_H
