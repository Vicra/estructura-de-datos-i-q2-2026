#include "queue.h"
#include <iostream>
using std::cout;
using std::endl;

Queue::Queue() {
    this->head = nullptr;
    this->tail = nullptr;
}

void Queue::enqueue(int x){
    // crear la instancia
    Node* newNode = new Node(x);

    // 1er caso: lista vacia
    if(this->head == nullptr){
        this->head = newNode;
        this->tail = newNode;
        return;
    }

    // 2do caso: lista no esta vacia
    this->tail->next = newNode;
    this->tail = newNode;
}

void Queue::print() {
    Node*it = this->head;
    if(it == nullptr) {
        cout << "Empty queue " << endl;
        return;
    }
    while(it!= nullptr){
        cout << it->value << " -> ";
        it = it->next;
    }
    cout << "nullptr" << endl;
    cout << "Head :" << this->peek() << endl;
    cout << "Tail: " << this->rear() << endl << endl;
}

int Queue::dequeue(){
    // 1er caso: lista vacia
    if(this->head == nullptr) return -1;

    // 2do caso: lista no esta vacia
    Node* tmp = this->head;
    int valueToReturn = tmp->value;

    this->head = tmp->next;
    delete tmp;
    return valueToReturn;
}

int Queue::peek(){
    if(this->head != nullptr)
        return this->head->value;
    return -1;
}

int Queue::rear(){
    if(this->tail != nullptr)
        return this->tail->value;
    return -1;
}
