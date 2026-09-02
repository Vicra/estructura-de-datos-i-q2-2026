#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "LinkedListController.h"
#include "DoubleLinkedListController.h"
#include "StackController.h"
#include "QueueController.h"
#include "BSTController.h"
#include "AVLController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLinkedList_clicked();
    void on_btnDoubleLinkedList_clicked();
    void on_btnStack_clicked();
    void on_btnQueue_clicked();
    void on_btnBST_clicked();
    void on_btnAVL_clicked();

    void on_insertButton_clicked();
    void on_removeButton_clicked();
    void on_searchButton_clicked();
    void on_traverseButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    enum EstructuraActiva { NONE, SLL, DLL, STACK, QUEUE, BST, AVL };
    EstructuraActiva estructuraActiva;

    LinkedListController* controllerSLL;
    DoubleLinkedListController* controllerDLL;
    StackController* controllerStack;
    QueueController* controllerQueue;
    class BSTController* controllerBST;
    class AVLController* controllerAVL;

    int mode = 0;
    void limpiarEscena();
    void resetControllers();
};

#endif // MAINWINDOW_H

