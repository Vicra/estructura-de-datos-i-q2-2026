#include "BST.h"
#include <QString>
#include <QTextStream>
#include <QMessageBox>

BST::BST() : root(nullptr), lastInserted(nullptr) {}

BST::~BST() {
    clear();
}

void BST::insert(int value) {
    root = insertRec(root, value);
}

NodeBST* BST::insertRec(NodeBST* node, int value) {
    if (!node) {
        node = new NodeBST(value);
        lastInserted = node;
        return node;
    }

    if (value < node->value) {
        node->left = insertRec(node->left, value);
    } else if (value > node->value) {
        node->right = insertRec(node->right, value);
    }
    return node;
}

void BST::remove(int value) {
    root = removeRec(root, value);
}

NodeBST* BST::removeRec(NodeBST* node, int value) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = removeRec(node->left, value);
    } else if (value > node->value) {
        node->right = removeRec(node->right, value);
    } else {

        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }

        else if (!node->left) {
            NodeBST* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            NodeBST* temp = node->left;
            delete node;
            return temp;
        }

        else {
            NodeBST* successor = findMin(node->right);
            node->value = successor->value;
            node->right = removeRec(node->right, successor->value);
        }
    }
    return node;
}

NodeBST* BST::findMin(NodeBST* node) {
    while (node && node->left) node = node->left;
    return node;
}

NodeBST* BST::search(int value) {
    NodeBST* current = root;
    while (current) {
        if (current->value == value) return current;
        else if (value < current->value) current = current->left;
        else current = current->right;
    }
    return nullptr;
}

NodeBST* BST::getRoot() {
    return root;
}

void BST::clear() {
    clearRec(root);
    root = nullptr;
    lastInserted = nullptr;
}

void BST::clearRec(NodeBST* node) {
    if (!node) return;
    clearRec(node->left);
    clearRec(node->right);
    delete node;
}

void BST::save(QTextStream& out) {
    out << "TYPE:TREE\n";
    saveRec(root, out);
}


void BST::saveRec(NodeBST* node, QTextStream& out) {
    if (!node) {
        out << "# ";
        return;
    }
    out << node->value << " ";
    saveRec(node->left, out);
    saveRec(node->right, out);
}

void BST::load(QTextStream& in) {
    clear();

    QString header;
    header = in.readLine();
    if (header.trimmed() != "TYPE:TREE") {
        QMessageBox::warning(nullptr, "Error de carga",
                             "No se pueden cargar estructuras lineales (TYPE:LIST) en árboles (BST).");
        return;
    }

    root = loadRec(in);
}


NodeBST* BST::loadRec(QTextStream& in) {
    QString token;
    in >> token;
    if (token == "#" || token.isEmpty())
        return nullptr;

    NodeBST* node = new NodeBST(token.toInt());
    node->left = loadRec(in);
    node->right = loadRec(in);
    return node;
}

