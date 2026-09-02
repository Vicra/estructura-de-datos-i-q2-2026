#include "Stack.h"
#include <stdexcept>

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    clear();
}

void Stack::push(int value) {
    NodeStack* newNode = new NodeStack(value);
    newNode->next = top;
    top = newNode;
}

void Stack::pop() {
    if (top) {
        NodeStack* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::clear() {
    while (top) {
        NodeStack* temp = top;
        top = top->next;
        delete temp;
    }
}

int Stack::peek() {
    if (isEmpty()) {
        throw std::runtime_error("Stack vacío, no se puede hacer peek");
    }
    return top->value;
}


bool Stack::isEmpty() const {
    return top == nullptr;
}

NodeStack* Stack::getTop() const {
    return top;
}
