#include "node.h"
#include "linkedlist.h"
#include <iostream>

using std::cout;
using std::endl;

void printList(Node* root){
    Node* it = root;
    while(it!=nullptr){
        cout << it->value << ", ";
        it = it->next;
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

    cout << "Linked list" << endl;
    LinkedList l;
    // l.insert(10);
    // l.insert(20);
    // l.insert(30);
    // l.insert(40);
    // l.insert(50);
    l.pushFront(10);
    l.pushFront(20);
    l.pushFront(30);
    l.pushFront(40);
    l.pushFront(50);
    l.pushFront(60);
    l.print();
    l.remove(10);
    l.print();
    l.remove(60);
    l.print();
    l.remove(40);
    l.print();


    return 0;
}
