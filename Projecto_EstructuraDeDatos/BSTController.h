#ifndef BSTCONTROLLER_H
#define BSTCONTROLLER_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QObject>
#include <QVector>
#include <QMap>
#include <QMainWindow>
#include <QTimer>
#include <QColor>
#include <functional>
#include "ClickableNodeBST.h"
#include "BST.h"

class BSTController : public QObject {
    Q_OBJECT

public:
    BSTController(QGraphicsScene* scene, QMainWindow* window);
    ~BSTController();

    void insert(int value);
    void remove(int value);
    void search(int value);
    void clear();

    void traverseInOrder();
    void traversePreOrder();
    void traversePostOrder();

    void saveToFile(const QString& filename);
    void loadFromFile(const QString& filename);

private:
    QGraphicsScene* scene;
    BST tree;

    QVector<QGraphicsEllipseItem*> nodeItems;
    QVector<QGraphicsTextItem*> labels;
    QVector<QGraphicsLineItem*> edges;
    QMap<NodeBST*, QGraphicsEllipseItem*> nodeMap;
    QMap<NodeBST*, QColor> nodeColors;

    QMainWindow* mainWindow;

    QColor rootColor   = QColor("#87CEFA");
    QColor leafColor   = QColor("#FFA07A");
    QColor innerColor  = QColor("#90EE90");
    QColor normalColor = Qt::white;

    int getDepth(NodeBST* root, NodeBST* target, int depth = 0);
    int getHeight(NodeBST* node);
    int getBalance(NodeBST* node);

    void drawTree();
    void drawNode(NodeBST* node, int x, int y, int dx);

    void blinkNode(QGraphicsEllipseItem* node,
                   const QColor& highlight,
                   int times,
                   int delayMs,
                   const QColor& baseColor,
                   std::function<void()> onFinished = nullptr);

    void traverseInOrderHelper(NodeBST* node, QString& result);
    void traversePreOrderHelper(NodeBST* node, QString& result);
    void traversePostOrderHelper(NodeBST* node, QString& result);

    void showStatusMessage(const QString& msg);
};

#endif // BSTCONTROLLER_H
