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
    dll.pushFront("B");
    dll.print();
    dll.pushFront("A");
    dll.print();
    cout << "Search Z: "
         << (dll.searchBackwards("Z") == true ? "true": "false")
         << endl;

    cout << "Search D: "
         << (dll.searchBackwards("D") == true ? "true": "false")
         << endl;

    cout << "Search B: "
         << (dll.searchBackwards("B") == true ? "true": "false")
         << endl;

    cout << "Search A: "
         << (dll.searchBackwards("A") == true ? "true": "false")
         << endl;
    return 0;
}
