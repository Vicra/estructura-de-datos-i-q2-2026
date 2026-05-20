#include "bst.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(3);
    tree.insert(7);
    tree.insert(15);
    tree.insert(25);
    tree.print();
    cout << "Searching 17 ..." << tree.search(17) <<endl;
    cout << "Searching 67 ..." << tree.search(67) <<endl;
    cout << "Searching 101 ..." << tree.search(101) <<endl;
    cout << "Searching 88 ..." << tree.search(88) <<endl;
    cout << "Tree" << endl;
    // tree.remove(10);
    tree.print();
    // tree.remove(20);
    tree.print();
    // tree.remove(7);
    // tree.remove(5);
    tree.print();
    cout << "Inorder :";
    tree.inorder();
    cout << endl << "Preorder :";
    tree.preorder();
    cout << endl << "Postorder :";
    tree.postorder();
    return 0;
}
