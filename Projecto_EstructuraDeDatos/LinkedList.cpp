#include "LinkedList.h"
#include <iostream>
#include <QMessageBox>

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::insert(int value) {
    insertAt(value, 0);
}

bool LinkedList::remove(int value) {
    Node* current = head;
    Node* prev = nullptr;
    int pos = 0;

    while (current) {
        if (current->value == value) {
            return removeAt(pos);
        }
        prev = current;
        current = current->next;
        pos++;
    }
    return false;
}

void LinkedList::insertAt(int value, int position) {
    Node* newNode = new Node(value);

    if (position <= 0 || !head) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;
    int index = 0;
    while (current->next && index < position - 1) {
        current = current->next;
        index++;
    }

    newNode->next = current->next;
    current->next = newNode;
}

bool LinkedList::removeAt(int position) {
    if (!head) return false;

    if (position <= 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* current = head;
    int index = 0;
    while (current->next && index < position - 1) {
        current = current->next;
        index++;
    }

    if (!current->next) return false;

    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

void LinkedList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

Node* LinkedList::getHead() {
    return head;
}

void LinkedList::print() {
    Node* current = head;
    while (current) {
        std::cout << current->value << " -> ";
        current = current->next;
    }
    std::cout << "nullptr\n";
}

int LinkedList::size() {
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}


void LinkedList::save(QTextStream& out) {
    out << "TYPE:LIST\n";
    Node* current = head;
    while (current) {
        out << current->value << " ";
        current = current->next;
    }
}

void LinkedList::load(QTextStream& in) {
    clear();

    QString header = in.readLine();
    if (header.trimmed() != "TYPE:LIST") {
        QMessageBox::warning(nullptr, "Error de carga",
                             "No se pueden cargar estructuras de tipo TREE en listas (TYPE:LIST requerido).");
        return;
    }

    int value;
    while (!in.atEnd()) {
        in >> value;
        if (in.status() != QTextStream::Ok) break;
        insertAt(value, size());
    }
}
