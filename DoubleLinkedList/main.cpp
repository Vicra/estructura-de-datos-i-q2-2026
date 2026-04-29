#include "doublelinkedlist.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {
    DoubleLinkedList dll;
    dll.insert("A");
    dll.deleteByIndex(-1);
    dll.print();
    dll.deleteByIndex(2);
    dll.print();
    dll.deleteByIndex(0);
    dll.print();
    dll.insert("B");
    dll.insert("C");
    dll.print();
    cout << "Borrando B" << endl;
    dll.deleteByIndex(0);
    cout << "B borrado" << endl;
    dll.print();

    dll.insert("D");
    dll.insert("E");
    dll.print();
    dll.deleteByIndex(2);
    dll.print();
    return 0;
}
