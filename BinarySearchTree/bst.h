#ifndef BST_H
#define BST_H
#include "node.h"
class BST
{
private:
    // recursive/private functions
    Node* insertRecursive(Node* currentRoot, Node* newNode);
    Node* searchRecursive(Node* currentRoot, int val);
    Node* mostLeftChild(Node * currentRoot);
    Node* successor(Node* currentRoot);
    Node* removeRecursive(Node* currentRoot, int val);

public:
    BST();

    Node* root;

    // operations
    void insert(int val);
    bool search(int val);
    void remove(int val);
    // remove
};

#endif // BST_H
