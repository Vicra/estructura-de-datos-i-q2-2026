#include "node.h"
#include <iostream>

using std::cout;
using std::endl;

void printList(Node* root){
    while(root!=nullptr){
        cout << root->value << ", ";
        root = root->next;
    }
}

int main() {
    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);

    // prints
    cout << n1->value << endl;
    cout << n2->value << endl;
    cout << n3->value << endl;

    // unir elementos
    n1->next = n2;
    n2->next = n3;

    // imprimir elementos en un ciclo
    printList(n1);
    cout << endl;
    cout << "n1: " << n1->value << endl;

    // deletes
    delete n1;
    delete n2;
    delete n3;
    return 0;
}
