#include "DoubleLinkedList.h"
#include <stdexcept>

DoubleLinkedList::DoubleLinkedList() : head(nullptr), tail(nullptr) {}

DoubleLinkedList::~DoubleLinkedList() {
    clear();
}

void DoubleLinkedList::insert(int value) {
    NodeDLL* newNode = new NodeDLL(value);

    if (!head) {
        head = tail = newNode;
        return;
    }

    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
}

void DoubleLinkedList::insertAt(int value, int position) {
    if (position < 0) throw std::out_of_range("Posición inválida");

    NodeDLL* newNode = new NodeDLL(value);

    if (!head) {
        head = tail = newNode;
        return;
    }

    if (position == 0) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    NodeDLL* current = head;
    int index = 0;

    while (current->next && index < position) {
        current = current->next;
        index++;
    }

    if (!current->next && index < position) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        NodeDLL* prevNode = current->prev;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = current;
        current->prev = newNode;
    }
}

void DoubleLinkedList::removeAt(int position) {
    if (position < 0 || !head) throw std::out_of_range("Posición inválida");

    NodeDLL* current = head;
    int index = 0;

    while (current && index < position) {
        current = current->next;
        index++;
    }

    if (!current) throw std::out_of_range("Posición inválida");

    if (current == head && current == tail) {
        delete current;
        head = tail = nullptr;
        return;
    }

    if (current == head) {
        head = head->next;
        head->prev = nullptr;
        delete current;
        return;
    }

    if (current == tail) {
        tail = tail->prev;
        tail->next = nullptr;
        delete current;
        return;
    }

    NodeDLL* prevNode = current->prev;
    NodeDLL* nextNode = current->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    delete current;
}

void DoubleLinkedList::clear() {
    NodeDLL* current = head;
    while (current) {
        NodeDLL* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
}

NodeDLL* DoubleLinkedList::getHead() const {
    return head;
}

NodeDLL* DoubleLinkedList::getTail() const {
    return tail;
}

int DoubleLinkedList::size() const {
    int count = 0;
    NodeDLL* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

bool DoubleLinkedList::isEmpty() const {
    return head == nullptr;
}
