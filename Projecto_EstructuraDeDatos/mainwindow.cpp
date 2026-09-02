#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <qstatusbar.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , estructuraActiva(NONE)
    , controllerSLL(nullptr)
    , controllerDLL(nullptr)
    , controllerStack(nullptr)
    , controllerQueue(nullptr)
    , controllerBST(nullptr)
    , controllerAVL(nullptr)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() {
    delete controllerSLL;
    delete controllerDLL;
    delete controllerStack;
    delete controllerQueue;
    delete controllerBST;
    delete controllerAVL;
    delete ui;
}

void MainWindow::limpiarEscena() {
    scene->clear();
}

void MainWindow::on_btnLinkedList_clicked() {
    resetControllers();
    controllerSLL = new LinkedListController(scene, this);
    estructuraActiva = SLL;
    statusBar()->showMessage("Estructura activa: Lista Simple", 2000);
}

void MainWindow::on_btnDoubleLinkedList_clicked() {
    resetControllers();
    controllerDLL = new DoubleLinkedListController(scene, this);
    estructuraActiva = DLL;
    statusBar()->showMessage("Estructura activa: Lista Doble", 2000);
}

void MainWindow::on_btnStack_clicked() {
    resetControllers();
    controllerStack = new StackController(scene, this);
    estructuraActiva = STACK;
    statusBar()->showMessage("Estructura activa: Pila (Stack)", 2000);
}

void MainWindow::on_btnQueue_clicked() {
    resetControllers();

    if (!controllerQueue)
        controllerQueue = new QueueController(scene, this);
    controllerQueue->clear();
    estructuraActiva = QUEUE;
    statusBar()->showMessage("Estructura activa: Cola (Queue)", 2000);
}

void MainWindow::on_btnBST_clicked() {
    resetControllers();
    controllerBST = new BSTController(scene, this);
    estructuraActiva = BST;
    statusBar()->showMessage("Estructura activa: Árbol Binario de Búsqueda (BST)", 2000);
}

void MainWindow::on_btnAVL_clicked() {
    resetControllers();
    controllerAVL = new AVLController(scene, this);
    estructuraActiva = AVL;
    statusBar()->showMessage("Estructura activa: Árbol AVL", 2000);
}

void MainWindow::on_insertButton_clicked() {
    if (estructuraActiva == NONE) return;

    bool ok;
    int value = QInputDialog::getInt(this, "Insertar", "Valor:", 0, -9999, 9999, 1, &ok);
    if (!ok) return;

    if (estructuraActiva == SLL && controllerSLL) {
        controllerSLL->insert(value);
    } else if (estructuraActiva == DLL && controllerDLL) {
        int pos = QInputDialog::getInt(this, "Insertar", "Posición:", 0, 0, 999, 1, &ok);
        if (ok) controllerDLL->insertAt(value, pos);
    } else if (estructuraActiva == STACK && controllerStack) {
        controllerStack->push(value);
    } else if (estructuraActiva == QUEUE && controllerQueue) {
        controllerQueue->enqueue(value);
    }else if (estructuraActiva == BST && controllerBST) {
        controllerBST->insert(value);
    }else if (estructuraActiva == AVL && controllerAVL) {
        controllerAVL->insert(value);
    }
}

void MainWindow::on_removeButton_clicked() {
    if (estructuraActiva == NONE) return;

    if (estructuraActiva == SLL && controllerSLL) {
        bool ok;
        int value = QInputDialog::getInt(this, "Eliminar", "Valor:", 0, -9999, 9999, 1, &ok);
        if (ok) controllerSLL->remove(value);
    } else if (estructuraActiva == DLL && controllerDLL) {
        bool ok;
        int pos = QInputDialog::getInt(this, "Eliminar", "Posición:", 0, 0, 999, 1, &ok);
        if (ok) controllerDLL->removeAt(pos);
    } else if (estructuraActiva == STACK && controllerStack) {
        controllerStack->pop();
    } else if (estructuraActiva == QUEUE && controllerQueue) {
        controllerQueue->dequeue();
    } else if (estructuraActiva == BST && controllerBST) {
        bool ok;
        int value = QInputDialog::getInt(this, "Eliminar", "Valor:", 0, -9999, 9999, 1, &ok);
        if (ok) controllerBST->remove(value);
    } else if (estructuraActiva == AVL && controllerAVL) {
        bool ok;
        int value = QInputDialog::getInt(this, "Eliminar", "Valor:", 0, -9999, 9999, 1, &ok);
        if (ok) controllerAVL->remove(value);
    }
}

void MainWindow::on_searchButton_clicked() {
    if (estructuraActiva == NONE) return;

    if (estructuraActiva == STACK && controllerStack) {
        // 🔹 Stack
        QStringList options;
        options << "Peek (TOP)" << "Buscar por posición";

        bool ok;
        QString choice = QInputDialog::getItem(this,
                                               "Buscar en Stack",
                                               "Selecciona el tipo de búsqueda:",
                                               options, 0, false, &ok);
        if (!ok || choice.isEmpty()) return;

        if (choice == "Peek (TOP)") {
            controllerStack->peek();
        } else {
            int index = QInputDialog::getInt(this,
                                             "Buscar en Stack",
                                             "Posición (0 = TOP):",
                                             0, 0, 9999, 1, &ok);
            if (ok) controllerStack->search(index);
        }
    }
    else if (estructuraActiva == QUEUE && controllerQueue) {
        // 🔹 Queue
        QStringList options;
        options << "Peek (HEAD)" << "Buscar por posición";

        bool ok;
        QString choice = QInputDialog::getItem(this,
                                               "Buscar en Queue",
                                               "Selecciona el tipo de búsqueda:",
                                               options, 0, false, &ok);
        if (!ok || choice.isEmpty()) return;

        if (choice == "Peek (HEAD)") {
            controllerQueue->peek();
        } else {
            int index = QInputDialog::getInt(this,
                                             "Buscar en Queue",
                                             "Posición (0 = HEAD):",
                                             0, 0, 9999, 1, &ok);
            if (ok) controllerQueue->search(index);
        }
    }
    else {
        // 🔹 Todas las demás estructuras que buscan por valor
        bool ok;
        int value = QInputDialog::getInt(this, "Buscar", "Valor:",
                                         0, -9999, 9999, 1, &ok);
        if (!ok) return;

        if (estructuraActiva == SLL && controllerSLL) {
            controllerSLL->search(value);
        } else if (estructuraActiva == DLL && controllerDLL) {
            controllerDLL->search(value);
        } else if (estructuraActiva == BST && controllerBST) {
            controllerBST->search(value);
        } else if (estructuraActiva == AVL && controllerAVL) {
            controllerAVL->search(value);
        }
    }
}

void MainWindow::on_traverseButton_clicked() {
    static bool forward = true;

    if (estructuraActiva == SLL && controllerSLL) {
        controllerSLL->traverse();
    } else if (estructuraActiva == DLL && controllerDLL) {
        if (forward) controllerDLL->traverseForward();
        else controllerDLL->traverseBackward();
    } else if (estructuraActiva == STACK && controllerStack) {
        controllerStack->traverse(forward);
    } else if (estructuraActiva == QUEUE && controllerQueue) {
        controllerQueue->traverse();
    } else if (estructuraActiva == BST && controllerBST) {
        QStringList options;
        options << "InOrder" << "PreOrder" << "PostOrder";

        bool ok;
        QString choice = QInputDialog::getItem(this,
                                               "Seleccionar recorrido",
                                               "Tipo de recorrido:",
                                               options, 0, false, &ok);

        if (ok && !choice.isEmpty()) {
            if (choice == "InOrder") {
                controllerBST->traverseInOrder();
            } else if (choice == "PreOrder") {
                controllerBST->traversePreOrder();
            } else if (choice == "PostOrder") {
                controllerBST->traversePostOrder();
            }
        }
    }else if (estructuraActiva == AVL && controllerAVL) {
        QStringList options;
        options << "InOrder" << "PreOrder" << "PostOrder";

        bool ok;
        QString choice = QInputDialog::getItem(this,
                                               "Seleccionar recorrido",
                                               "Tipo de recorrido:",
                                               options, 0, false, &ok);

        if (ok && !choice.isEmpty()) {
            if (choice == "InOrder") {
                controllerAVL->traverseInOrder();
            } else if (choice == "PreOrder") {
                controllerAVL->traversePreOrder();
            } else if (choice == "PostOrder") {
                controllerAVL->traversePostOrder();
            }
        }
    }
}

void MainWindow::on_saveButton_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar estructura", "", "Archivos de texto (*.txt)");
    if (fileName.isEmpty()) return;

    if (estructuraActiva == SLL && controllerSLL) {
        controllerSLL->saveToFile(fileName);
    } else if (estructuraActiva == DLL && controllerDLL) {
        controllerDLL->saveToFile(fileName);
    } else if (estructuraActiva == STACK && controllerStack) {
        controllerStack->saveToFile(fileName);
    } else if (estructuraActiva == QUEUE && controllerQueue) {
        controllerQueue->saveToFile(fileName);
    }  else if (estructuraActiva == BST && controllerBST) {
        controllerBST->saveToFile(fileName);
    }else if (estructuraActiva == AVL && controllerAVL) {
        controllerAVL->saveToFile(fileName);
    }
}

void MainWindow::on_loadButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Cargar estructura", "", "Archivos de texto (*.txt)");
    if (fileName.isEmpty()) return;

    if (estructuraActiva == SLL && controllerSLL) {
        controllerSLL->loadFromFile(fileName);
    } else if (estructuraActiva == DLL && controllerDLL) {
        controllerDLL->loadFromFile(fileName);
    } else if (estructuraActiva == STACK && controllerStack) {
        controllerStack->loadFromFile(fileName);
    } else if (estructuraActiva == QUEUE && controllerQueue) {
        controllerQueue->loadFromFile(fileName);
    } else if (estructuraActiva == BST && controllerBST) {
        controllerBST->loadFromFile(fileName);
    }else if (estructuraActiva == AVL && controllerAVL) {
        controllerAVL->loadFromFile(fileName);
    }
}


void MainWindow::on_clearButton_clicked() {
    if (estructuraActiva == SLL && controllerSLL) {
        controllerSLL->clear();
    } else if (estructuraActiva == DLL && controllerDLL) {
        controllerDLL->clear();
    } else if (estructuraActiva == STACK && controllerStack) {
        controllerStack->clear();
    } else if (estructuraActiva == QUEUE && controllerQueue) {
        controllerQueue->clear();
    } else if (estructuraActiva == BST && controllerBST) {
        controllerBST->clear();
    }else if (estructuraActiva == AVL && controllerAVL) {
        controllerAVL->clear();
    }
}

void MainWindow::resetControllers() {
    if (controllerSLL) { controllerSLL->clear(); delete controllerSLL; controllerSLL = nullptr;  }
    if (controllerDLL) { controllerDLL->clear(); delete controllerDLL; controllerDLL = nullptr; }
    if (controllerStack) { controllerStack->clear(); delete controllerStack; controllerStack = nullptr; }
    if (controllerQueue) { controllerQueue->clear(); delete controllerQueue; controllerQueue = nullptr; }
    if (controllerBST) { controllerBST->clear(); delete controllerBST; controllerBST = nullptr; }
    if (controllerAVL) { controllerAVL->clear(); delete controllerAVL; controllerAVL = nullptr; }


    limpiarEscena();
    estructuraActiva = NONE;
    statusBar()->showMessage("Estructura reiniciada", 1500);
}
