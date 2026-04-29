#ifndef NODE_H
#define NODE_H
#include <string>

using std::string;

class Node
{
public:
    Node(string val);

    //props
    Node* prev;
    Node* next;
    string value;

};

#endif // NODE_H
