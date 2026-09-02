#ifndef QUEUE_H
#define QUEUE_H

#include "NodeQueue.h"

class Queue {
private:
    NodeQueue* front;
    NodeQueue* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    bool isEmpty() const { return front == nullptr; }
    int getSize() const { return size; }

    NodeQueue* getRear() const {
        NodeQueue* current = front;
        if (!current) return nullptr;

        while (current->next) {
            current = current->next;
        }
        return current;
    }



    void enqueue(int value) {
        NodeQueue* newNode = new NodeQueue(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    bool dequeue() {
        if (isEmpty()) return false;
        NodeQueue* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        size--;
        return true;
    }

    NodeQueue* getFront() const { return front; }

    void clear() {
        while (!isEmpty()) dequeue();
    }
};

#endif // QUEUE_H
