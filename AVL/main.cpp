#include "avltree.h"

int main(){
    AVLTree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(35);
    tree.insert(100);
    tree.print();
    tree.remove(40);
    tree.remove(20);
    tree.print();
    return 0;
}
