#include "bst.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(21);
    tree.insert(3);
    tree.insert(101);
    tree.insert(67);

    cout << "Searching 17 ..." << tree.search(17) <<endl;
    cout << "Searching 67 ..." << tree.search(67) <<endl;
    cout << "Searching 101 ..." << tree.search(101) <<endl;
    cout << "Searching 88 ..." << tree.search(88) <<endl;

    cout << "Tree" << endl;
    return 0;
}
