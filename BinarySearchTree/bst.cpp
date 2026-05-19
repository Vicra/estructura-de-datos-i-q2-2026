#include "bst.h"

BST::BST() {
    this->root = nullptr;
}

// public
// insert(10)
// insert(5)
// insert(15)
// insert(10)
void BST::insert(int val){
    // instancia del nuevo nodo
    Node* newNode = new Node(val);

    // 1er caso: arbol vacio
    if(this->root == nullptr){
        this->root = newNode;
        return;
    }

    // 2 caso: arbol no vacio
    this->root = insertRecursive(this->root, newNode);
    return;
}

Node* BST::insertRecursive(Node*currentRoot, Node* newNode){
    // 1er iteracion currentNode: 10, newNode: 5
    // 2da iteracion currentNode: nullptr, newNode 5

    // ----- segundo llamado del main

    // 1er iteracion currentNode: 10, newNode: 15

    if(currentRoot == nullptr) return newNode;

    if(newNode->value < currentRoot->value){
        currentRoot->left = insertRecursive(currentRoot->left, newNode);
    } else if(newNode->value > currentRoot->value){
        currentRoot->right = insertRecursive(currentRoot->right, newNode);
    }
    return currentRoot;
}

bool BST::search(int val){
    Node* returnedNode = searchRecursive(this->root, val);
    if(returnedNode == nullptr) return false;
    return true;
}

Node* BST::searchRecursive(Node* currentRoot, int val){
    // caso si no lo encontre currentRoot: null, val: 17
    if(currentRoot == nullptr) return nullptr;

    // currentRoot: 10, val: 17
    if(currentRoot->value == val) return currentRoot;
    else if(val > currentRoot->value){
        return this->searchRecursive(currentRoot->right, val);
    } else {
        return this->searchRecursive(currentRoot->left, val);
    }
}

Node* BST::mostLeftChild(Node * currentRoot){
    while(currentRoot->left != nullptr){
        currentRoot = currentRoot->left;
    }
    return currentRoot;
}

Node* BST::successor(Node* currentRoot){
    return this->mostLeftChild(currentRoot->right);
}

void BST::remove(int val){
    // case 1, val: 25
    this->root = this->removeRecursive(this->root, val);
}

Node* BST::removeRecursive(Node* currentRoot, int val){
    if(val < currentRoot->value){
        currentRoot->left = this->removeRecursive(currentRoot->left, val);
    }
    else if(val > currentRoot->value){
        // TODO: falta algo
        currentRoot->right = this->removeRecursive(currentRoot->right, val);
    }
    else {
        // borrar
        // 1er caso: no tiene hijos
        if(currentRoot->left == nullptr
            && currentRoot->right == nullptr ){
            delete currentRoot;
            return nullptr;
        }

        // 2do caso: tengo un hijo por la izquierda
        else if(currentRoot->right == nullptr){
            Node* nodeToAscend = currentRoot->left;
            delete currentRoot;
            return nodeToAscend;
        }

        // 3er caso: tengo un hijo por la derecha
        else if(currentRoot->left == nullptr){
            Node* nodeToAscend = currentRoot->right;
            delete currentRoot;
            return nodeToAscend;
        }
    }
}














