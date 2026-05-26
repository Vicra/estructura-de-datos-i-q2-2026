#include "node.h"

Node::Node(int val) {
    this->value = val;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
}
