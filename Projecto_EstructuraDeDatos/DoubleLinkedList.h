#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

struct NodeDLL {
    int value;
    NodeDLL* prev;
    NodeDLL* next;

    NodeDLL(int v) : value(v), prev(nullptr), next(nullptr) {}
};

class DoubleLinkedList {
public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    void insert(int value);
    void insertAt(int value, int position);
    void removeAt(int position);
    void clear();

    NodeDLL* getHead() const;
    NodeDLL* getTail() const;
    int size() const;
    bool isEmpty() const;

private:
    NodeDLL* head;
    NodeDLL* tail;
};

#endif // DOUBLELINKEDLIST_H
