#ifndef AVLCONTROLLER_H
#define AVLCONTROLLER_H

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
#include <QHash>
#include "ClickableNode.h"
#include "AVL.h"

class AVLController : public QObject {
    Q_OBJECT

public:
    AVLController(QGraphicsScene* scene, QMainWindow* window);
    ~AVLController();

    void insert(int value);
    void remove(int value);
    void search(int value);
    void clear();

    void traverseInOrder();
    void traversePreOrder();
    void traversePostOrder();

    void traverseInOrderText();
    void traversePreOrderText();
    void traversePostOrderText();

    void saveToFile(const QString& filename);
    void loadFromFile(const QString& filename);

private:
    QGraphicsScene* scene;
    AVL tree;


    QVector<ClickableNode*> nodeItems;
    QVector<QGraphicsTextItem*> labels;
    QVector<QGraphicsLineItem*> edges;
    QMap<NodeAVL*, ClickableNode*> nodeMap;
    QHash<NodeAVL*, QColor> nodeColors;

    QMainWindow* mainWindow;

    void clearScene();
    void drawTree();
    void drawNode(NodeAVL* node, int x, int y, int dx);

    void blinkNode(QGraphicsEllipseItem* node,
                   const QColor& highlight,
                   int times = 3,
                   int delayMs = 200,
                   const QColor& normal = Qt::white);

    void traverseInOrderHelper(NodeAVL* node, QString& result);
    void traversePreOrderHelper(NodeAVL* node, QString& result);
    void traversePostOrderHelper(NodeAVL* node, QString& result);

    void traverseInOrderHelper(NodeAVL* node, QVector<NodeAVL*>& order);
    void traversePreOrderHelper(NodeAVL* node, QVector<NodeAVL*>& order);
    void traversePostOrderHelper(NodeAVL* node, QVector<NodeAVL*>& order);

    void showStatusMessage(const QString& msg);

    void drawEdge(int x1, int y1, int x2, int y2, int radius);
};

#endif // AVLCONTROLLER_H

