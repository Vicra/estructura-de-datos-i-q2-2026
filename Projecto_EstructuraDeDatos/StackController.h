#ifndef STACKCONTROLLER_H
#define STACKCONTROLLER_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMainWindow>
#include <vector>
#include "Stack.h"

class StackController {
public:
    StackController(QGraphicsScene* scene, QMainWindow* window);
    ~StackController();

    void push(int value);
    void pop();
    void clear();

    void search(int index);
    void peek();
    void saveToFile(const QString& filename);
    void loadFromFile(const QString& filename);
    void traverse(bool topToBottom = true);
    void redrawFromStack();

private:
    QGraphicsScene* scene;
    QMainWindow* mainWindow;
    Stack stack;

    std::vector<QGraphicsItem*> arrows;
    std::vector<QGraphicsEllipseItem*> nodeItems;

    void animateAppearance(QGraphicsItem* item);
    void animateRemoval(QGraphicsItem* item);
    void showStatusMessage(const QString& msg);
};

#endif // STACKCONTROLLER_H

