#ifndef BST_H
#define BST_H

#include <QTextStream>

struct NodeBST {
    int value;
    NodeBST* left;
    NodeBST* right;

    NodeBST(int v) : value(v), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST();
    ~BST();

    void insert(int value);
    void remove(int value);
    NodeBST* search(int value);

    NodeBST* getRoot();
    NodeBST* getLastInserted() { return lastInserted; }

    void clear();

    void save(QTextStream& out);
    void load(QTextStream& in);

private:
    NodeBST* root;
    NodeBST* lastInserted;

    NodeBST* insertRec(NodeBST* node, int value);
    NodeBST* removeRec(NodeBST* node, int value);
    NodeBST* findMin(NodeBST* node);
    void clearRec(NodeBST* node);

    void saveRec(NodeBST* node, QTextStream& out);
    NodeBST* loadRec(QTextStream& in);
};

#endif // BST_H
