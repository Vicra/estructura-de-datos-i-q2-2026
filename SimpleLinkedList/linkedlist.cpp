#include "linkedlist.h"
#include <iostream>

using std::cout;
using std::endl;

LinkedList::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
}

void LinkedList::insert(int newValue){
    // instancia
    Node* newNode = new Node(newValue);

    // encontrar el ultimo
    // advertencia: si actualizo el head, considerar
    // si es necesario actualizar el tail
    // CASOS
    // 1er caso: lista vacia
    if(this->head == nullptr){
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->tail->next = newNode;
        this->tail = newNode;
    }

    return;
}

void LinkedList::pushFront(int newValue){
    Node* newNode = new Node(newValue);
    // 1er caso : vacio
    if(this->head == nullptr){
        this->head = newNode;
        this->tail = newNode;
    }

    // 2do caso: contiene elementos
    else {
        newNode->next = this->head;
        this->head = newNode;
    }
}

void LinkedList::print(){
    Node* it = this->head;
    cout << "Head ->" ;
    while(it != nullptr){
        cout << it->value << " -> ";
        it = it->next;
    }
    cout << "nullptr" << endl;
    cout << "Tail:" << this->tail->value<< endl;
}
