#ifndef DOUBLELINKEDLISTCONTROLLER_H
#define DOUBLELINKEDLISTCONTROLLER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QStatusBar>
#include "DoubleLinkedList.h"

class DoubleLinkedListController {
public:
    DoubleLinkedListController(QGraphicsScene* scene, QMainWindow* window);
    ~DoubleLinkedListController();

    void insertAt(int value, int position);
    void removeAt(int position);
    void search(int value);
    void traverseForward();
    void traverseBackward();
    void clear();
    void saveToFile(const QString& filename);
    void loadFromFile(const QString& filename);


private:
    QGraphicsScene* scene;
    QMainWindow* mainWindow;
    DoubleLinkedList list;

    QVector<QGraphicsEllipseItem*> nodeItems;
    QVector<QGraphicsLineItem*> arrows;

    void animateAppearance(QGraphicsItem* item);
    void animateRemoval(QGraphicsItem* item);
    void showStatusMessage(const QString& msg);
    void redrawFromList();
};

#endif // DOUBLELINKEDLISTCONTROLLER_H
