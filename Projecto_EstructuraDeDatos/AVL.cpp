#include "AVL.h"
#include <QString>
#include <QTextStream>
#include <algorithm>
#include <QVector>


AVL::AVL() : root(nullptr), lastInserted(nullptr) {}

AVL::~AVL() {
    clear();
}

int AVL::getHeight(NodeAVL* node) {
    return node ? node->height : 0;
}

int AVL::getBalance(NodeAVL* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

int AVL::getDepth(NodeAVL* node) {
    if (!root || !node) return -1;

    NodeAVL* current = root;
    int depth = 0;

    while (current) {
        if (node->value == current->value) {
            return depth;
        } else if (node->value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
        depth++;
    }

    return -1;
}

NodeAVL* AVL::rotateRight(NodeAVL* y) {
    NodeAVL* x = y->left;
    NodeAVL* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

    return x;
}

NodeAVL* AVL::rotateLeft(NodeAVL* x) {
    NodeAVL* y = x->right;
    NodeAVL* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}

void AVL::insert(int value) {
    root = insertRec(root, value);
}

NodeAVL* AVL::insertRec(NodeAVL* node, int value) {
    if (!node) {
        lastInserted = new NodeAVL(value);
        return lastInserted;
    }

    if (value < node->value) {
        node->left = insertRec(node->left, value);
    } else if (value > node->value) {
        node->right = insertRec(node->right, value);
    } else {
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && value < node->left->value)
        return rotateRight(node);

    if (balance < -1 && value > node->right->value)
        return rotateLeft(node);

    if (balance > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVL::remove(int value) {
    root = removeRec(root, value);
}

NodeAVL* AVL::removeRec(NodeAVL* node, int value) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = removeRec(node->left, value);
    } else if (value > node->value) {
        node->right = removeRec(node->right, value);
    } else {
        if (!node->left || !node->right) {
            NodeAVL* temp = node->left ? node->left : node->right;
            if (!temp) {
                delete node;
                return nullptr;
            } else {
                *node = *temp;
                delete temp;
            }
        } else {
            NodeAVL* succ = findMin(node->right);
            node->value = succ->value;
            node->right = removeRec(node->right, succ->value);
        }
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

NodeAVL* AVL::findMin(NodeAVL* node) {
    while (node && node->left) node = node->left;
    return node;
}

NodeAVL* AVL::search(int value) {
    NodeAVL* current = root;
    while (current) {
        if (value == current->value) return current;
        else if (value < current->value) current = current->left;
        else current = current->right;
    }
    return nullptr;
}

NodeAVL* AVL::getRoot() {
    return root;
}

void AVL::clear() {
    clearRec(root);
    root = nullptr;
    lastInserted = nullptr;
}

void AVL::clearRec(NodeAVL* node) {
    if (!node) return;
    clearRec(node->left);
    clearRec(node->right);
    delete node;
}

void AVL::save(QTextStream& out) {
    out << "TYPE:TREE\n";
    saveRec(root, out);
}


void AVL::saveRec(NodeAVL* node, QTextStream& out) {
    if (!node) {
        out << "# ";
        return;
    }
    out << node->value << " ";
    saveRec(node->left, out);
    saveRec(node->right, out);
}

#include <QMessageBox>

void AVL::load(QTextStream& in) {
    clear();

    QString header = in.readLine();
    if (header.trimmed() != "TYPE:TREE") {
        QMessageBox::warning(nullptr, "Error de carga",
                             "No se pueden cargar estructuras lineales (TYPE:LIST) en árboles.");
        return;
    }

    QVector<int> values;
    QString token;
    while (!in.atEnd()) {
        in >> token;
        if (token == "#" || token.isEmpty()) continue;
        values.append(token.toInt());
    }

    for (int v : values) {
        insert(v);
    }
}




NodeAVL* AVL::loadRec(QTextStream& in) {
    QString token;
    in >> token;
    if (token == "#" || token.isEmpty())
        return nullptr;

    NodeAVL* node = new NodeAVL(token.toInt());
    node->left = loadRec(in);
    node->right = loadRec(in);

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    return node;
}
