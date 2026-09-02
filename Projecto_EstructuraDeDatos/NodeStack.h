#ifndef NODESTACK_H
#define NODESTACK_H

struct NodeStack {
    int value;
    NodeStack* next;

    NodeStack(int v) : value(v), next(nullptr) {}
};

#endif // NODESTACK_H
