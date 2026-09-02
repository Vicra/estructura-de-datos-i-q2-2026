#ifndef QUEUECONTROLLER_H
#define QUEUECONTROLLER_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "Queue.h"

class QueueController {
private:
    QGraphicsScene* scene;
    QMainWindow* mainWindow;
    Queue queue;
    QList<QGraphicsEllipseItem*> nodeItems;

    QVector<QGraphicsTextItem*> textItems;

public:
    QueueController(QGraphicsScene* scene, QMainWindow* window);
    ~QueueController();

    void enqueue(int value);
    void dequeue();
    void search(int index);
    void peek();
    void traverse();
    void clear();

    void saveToFile(const QString& fileName);
    void loadFromFile(const QString& fileName);

private:
    void drawQueue();
    void showStatusMessage(const QString& msg);
};

#endif // QUEUECONTROLLER_H
