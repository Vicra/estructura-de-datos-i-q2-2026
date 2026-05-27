#ifndef AVLTREE_H
#define AVLTREE_H
#include "node.h"

#include <string>
using std::string;

class AVLTree
{
private:
    Node* insertRecursive(Node* currentRoot, Node* newNode);
    Node* searchRecursive(Node* currentRoot, int val);
    Node* mostLeftChild(Node * currentRoot);
    Node* successor(Node* currentRoot);
    Node* removeRecursive(Node* currentRoot, int val);
    void printHelper(string prefix, Node *currentRoot, bool isLeft);
    void inorderHelper(Node* currentRoot);
    void preorderHelper(Node* currentRoot);
    void postorderHelper(Node* currentRoot);

    // rotations
    Node* leftRotate(Node* x);
    Node* rightRotate(Node* y);

    int getHeight(Node* node);
    int getBalance(Node* node);
    int max(int a, int b);
public:
    AVLTree();
    Node* root;
    void insert(int val);
    bool search(int val);
    void remove(int val);
    void print();
    void inorder();
    void preorder();
    void postorder();
};

#endif // AVLTREE_H
