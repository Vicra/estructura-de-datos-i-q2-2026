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

void LinkedList::remove(int x){
    // 1er caso: vacio
    if(this->head == nullptr) return;

    // 2do caso: tengo un elemento y es el que quiero borrar
    if(this->head == this->tail){
        if(this->head->value == x){
            Node* tmp = this->head;

            this->head = this->head->next;
            this->tail = this->tail->next;

            // this.head = nullptr;
            // this.tail = nullptr;
            // estos son lo mismo que arriba

            delete tmp;

        } else {
            return;
        }
    }

    // 3er caso: contiene mas de un elemento, borrar la cabeza
    if(this->head->value == x){
        Node* tmp = this->head;
        this->head = this->head->next;
        delete tmp;
    }

    // 4to caso: es la cola el que se quiere borrar
    if(this->tail->value == x){
        Node* it = this->head;
        // iterar hasta llegar al penultimo
        while(it->next != this->tail){
            it = it->next;
        }

        // it ya esta en el penultimo
        Node* tmp = this->tail;
        this->tail = it;
        this->tail->next = nullptr;
        delete tmp;
    }

    else {
        // el que quiero borrar no esta en la cabeza, ni en la cola
        // o no existe
        // 1->2->2->6->8  borrar(7)

        Node* it = this->head;
        while(it->next != nullptr) {
            if(it->next->value == x){
                // borrar
                Node* tmp = it->next;
                it->next = it->next->next;

                // it.next = tmp.next
                // es lo mismo de arriba

                delete tmp;
                return;
            } else {
                it = it->next;
            }
        }
        // fin de iteracion no lo encontro
    }
}

