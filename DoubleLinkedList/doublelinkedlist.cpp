#include "doublelinkedlist.h"
#include <iostream>
using std::cout;
using std::endl;
DoubleLinkedList::DoubleLinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

void DoubleLinkedList::insert(string val){
    Node* newNode = new Node(val);

    this->size++;

    // 1er caso: lista vacia
    if(this->head == nullptr){
        this->head = newNode;
        this->tail = newNode;
        return;
    }

    // 2do caso: lista no esta vacia
    // paso 1
    this->tail->next = newNode;

    // paso 2
    newNode->prev = this->tail;

    // paso 3 : actualizar la cola
    this->tail = newNode;

}
void DoubleLinkedList::deleteByIndex(int pos){
    // 1er caso: lista vacia
    if(this->head == nullptr){
        return;
    }

    // 2do caso: pos out of bounds
    if(pos < 0 || pos >= this->size){
        return;
    }

    // 3er caso: borrar la cabeza, pos=0
    if(pos == 0){
        Node* tmp = this->head;

        this->head = this->head->next;

        if(this->head != nullptr) { // A, B
            this->head->prev = nullptr;
        } else {
            // solo tiene/tenia un elemento
            // hay algo mas que hacer?
            this->tail = this->head;
        }
        delete tmp;
        this->size--;
        return;
    }

    // 4to caso: borrar la cola
    if(pos == this->size-1){
        Node*tmp = this->tail;
        this->tail = tmp->prev;
        this->tail->next = nullptr;
        delete tmp;
        this->size--;
        return;
    }
}

void DoubleLinkedList::print(){
    Node* it = this->head;
    if(it == nullptr) {
        cout << "Empty DLL" << endl;
        return;
    }
    cout << "nullptr <- " ;
    while(it!=nullptr){
        cout << it->value;

        // validando si no es el ultimo
        if(it->next != nullptr){
            cout << "<=>";
        }
        it = it->next;
    }
    cout << "-> nullptr" << endl;
    if(this->head != nullptr) {
        cout << "Head: " << this->head->value << endl;
    } else {
        cout << "Head: nullptr" << endl;
    }
    if(this->tail != nullptr) {
        cout << "Tail: " << this->tail->value << endl;
    } else {
        cout << "Tail: nullptr" << endl;
    }
    cout << "Size: " << this->size ;
    cout << endl << endl;
}
