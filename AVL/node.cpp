#include "node.h"

Node::Node(int value) {
    this->left = nullptr;
    this->right = nullptr;
    this->value = value;
    this->height = 1;
}
