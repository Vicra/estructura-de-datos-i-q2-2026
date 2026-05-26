#ifndef NODE_H
#define NODE_H

class Node
{
public:
    Node(int val);
    Node* left;
    Node* right;
    int value;
    int height;
};

#endif // NODE_H
