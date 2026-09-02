#ifndef AVL_H
#define AVL_H

#include <QTextStream>

struct NodeAVL {
    int value;
    int height;
    NodeAVL* left;
    NodeAVL* right;

    NodeAVL(int v)
        : value(v), height(1), left(nullptr), right(nullptr) {}
};

class AVL {
public:
    AVL();
    ~AVL();

    void insert(int value);
    void remove(int value);
    NodeAVL* search(int value);

    NodeAVL* getRoot();
    NodeAVL* getLastInserted() { return lastInserted; }

    void clear();

    void save(QTextStream& out);
    void load(QTextStream& in);

    int getBalance(NodeAVL* node);
    int getDepth(NodeAVL* node);

private:
    NodeAVL* root;
    NodeAVL* lastInserted;

    int getHeight(NodeAVL* node);
    NodeAVL* rotateLeft(NodeAVL* y);
    NodeAVL* rotateRight(NodeAVL* x);

    NodeAVL* insertRec(NodeAVL* node, int value);
    NodeAVL* removeRec(NodeAVL* node, int value);
    NodeAVL* findMin(NodeAVL* node);
    void clearRec(NodeAVL* node);

    void saveRec(NodeAVL* node, QTextStream& out);
    NodeAVL* loadRec(QTextStream& in);
};

#endif // AVL_H
