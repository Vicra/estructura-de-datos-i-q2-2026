#include "node.h"

Node::Node(string val) {
    this->next = nullptr;
    this->prev = nullptr;
    this->value = val;
}
