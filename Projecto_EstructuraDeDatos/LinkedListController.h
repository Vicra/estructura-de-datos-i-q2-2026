#ifndef LINKEDLISTCONTROLLER_H
#define LINKEDLISTCONTROLLER_H

#include <QGraphicsScene>
#include <QVector>
#include <QPointer>
#include <QString>
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include "LinkedList.h"

class LinkedListController {
public:
    LinkedListController(QGraphicsScene* scene, QMainWindow* window);
    ~LinkedListController();

    void insert(int value);
    void remove(int value);
    void insertAt(int value, int position);
    void removeAt(int position);
    void search(int value);
    void traverse();
    void clear();
    void saveToFile(const QString& filename);
    void loadFromFile(const QString& filename);

private:
    QGraphicsScene* scene;
    LinkedList list;
    QVector<QGraphicsEllipseItem*> nodeItems;
    QVector<QGraphicsItem*> arrows;
    QList<QGraphicsTextItem*> labels;

    QMainWindow* mainWindow;

    void redrawFromList();
    void animateAppearance(QGraphicsItem* item);
    void animateRemoval(QGraphicsItem* item);
    void showStatusMessage(const QString& msg);
};

#endif
