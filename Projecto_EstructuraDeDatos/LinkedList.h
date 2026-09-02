#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <QTextStream>

struct Node {
    int value;
    Node* next;
    Node(int v) : value(v), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    void insert(int value);
    bool remove(int value);
    void print();
    void clear();
    void insertAt(int value, int position);
    bool removeAt(int position);
    void save(QTextStream& out);
    void load(QTextStream& in);
    int size();



    Node* getHead();

private:
    Node* head;
};

#endif // LINKEDLIST_H
