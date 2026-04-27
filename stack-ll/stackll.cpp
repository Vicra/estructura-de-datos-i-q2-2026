#include "stackll.h"
#include <iostream>
using std::cout;
using std::endl;

StackLL::StackLL() {
    this->head = nullptr;
}

void StackLL::push(int x){
    // create new node instace
    Node* newNode = new Node(x);

    // 1er caso: lista vacia
    if(this->head == nullptr){
        this->head = newNode;
        return;
    }

    // 2do caso: lista no vacia
    // el siguiente del nuevo nodo es la cabeza
    newNode->next = this->head;
    this->head = newNode;
}

void StackLL::print(){
    Node*it = this->head;
    if(it == nullptr) {
        cout << "Stack vacio" << endl;
    }
    while(it!= nullptr){
        cout << it->value << "->";
        it = it->next;
    }
    cout << "nullptr" << endl;
    this->peek();
}

int StackLL::pop(){
    // a borrar
    Node* tmp = this->head;
    int valueToReturn = tmp->value;

    // apuntar la cabeza al siguiente
    this->head = tmp->next;

    delete tmp;
    return valueToReturn;

}

void StackLL::peek(){
    if(this->head == nullptr){
        cout << "Empty head" << endl;
        return;
    }
    cout << "Peek: " << this->head->value << endl;
}

void StackLL::clear(){
    while(this->head != nullptr){
        this->pop();
    }
    return;
}
