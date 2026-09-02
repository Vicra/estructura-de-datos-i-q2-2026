#include "QueueController.h"
#include <qstatusbar.h>
#include <QThread>
#include <QApplication>

QueueController::QueueController(QGraphicsScene* s, QMainWindow* w)
    : scene(s), mainWindow(w) {}

QueueController::~QueueController() {
    clear();
}

void QueueController::enqueue(int value) {
    queue.enqueue(value);
    drawQueue();
    showStatusMessage("Enqueued: " + QString::number(value));
}

void QueueController::dequeue() {
    if (queue.dequeue()) {
        drawQueue();
        showStatusMessage("Dequeued correctamente");
    } else {
        showStatusMessage("Queue vacío");
    }
}

void QueueController::search(int index) {
    if (queue.isEmpty()) {
        showStatusMessage("Queue vacío");
        return;
    }

    NodeQueue* current = queue.getFront();
    int currentIndex = 0;

    while (current && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    if (!current) {
        showStatusMessage("Posición fuera de rango");
        return;
    }

    for (int k = 0; k < 3; k++) {
        nodeItems[currentIndex]->setBrush(QBrush(Qt::yellow));
        QThread::msleep(300);
        QApplication::processEvents();

        if (current == queue.getFront())
            nodeItems[currentIndex]->setBrush(QBrush(Qt::green));
        else if (current == queue.getRear())
            nodeItems[currentIndex]->setBrush(QBrush(Qt::blue));
        else
            nodeItems[currentIndex]->setBrush(QBrush(Qt::black));

        QThread::msleep(300);
        QApplication::processEvents();
    }

    showStatusMessage("Encontrado en posición " + QString::number(index) +
                      ": " + QString::number(current->value));
}

void QueueController::peek() {
    if (queue.isEmpty()) {
        showStatusMessage("Queue vacío");
        return;
    }

    NodeQueue* front = queue.getFront();
    int index = 0;

    for (int k = 0; k < 3; k++) {
        nodeItems[index]->setBrush(QBrush(Qt::yellow));
        QThread::msleep(300);
        QApplication::processEvents();

        if (front == queue.getFront())
            nodeItems[index]->setBrush(QBrush(Qt::green));
        else if (front == queue.getRear())
            nodeItems[index]->setBrush(QBrush(Qt::blue));
        else
            nodeItems[index]->setBrush(QBrush(Qt::black));

        QThread::msleep(300);
        QApplication::processEvents();
    }

    showStatusMessage("Peek (HEAD): " + QString::number(front->value));
}

void QueueController::traverse() {
    if (queue.isEmpty()) {
        showStatusMessage("Queue vacío");
        return;
    }

    NodeQueue* current = queue.getFront();
    int index = 0;

    while (current) {

        nodeItems[index]->setBrush(QBrush(Qt::yellow));
        QThread::msleep(300);
        QApplication::processEvents();

        if (current == queue.getFront())
            nodeItems[index]->setBrush(QBrush(Qt::green));
        else if (current == queue.getRear())
            nodeItems[index]->setBrush(QBrush(Qt::blue));
        else
            nodeItems[index]->setBrush(QBrush(Qt::black));

        current = current->next;
        index++;
    }

    showStatusMessage("Recorrido completado");
}


void QueueController::clear() {
    queue.clear();
    scene->clear();
    nodeItems.clear();
    textItems.clear();
    showStatusMessage("Queue limpiado");
}

void QueueController::saveToFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    out << "TYPE:LIST\n";

    NodeQueue* current = queue.getFront();
    while (current) {
        out << current->value << " ";
        current = current->next;
    }
    file.close();
    showStatusMessage("Queue guardado en archivo");
}

void QueueController::loadFromFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    queue.clear();
    QTextStream in(&file);

    QString header = in.readLine();
    if (header.trimmed() != "TYPE:LIST") {
        QMessageBox::warning(nullptr, "Error de carga",
                             "No se pueden cargar estructuras de tipo TREE en Queue (TYPE:LIST requerido).");
        return;
    }

    while (!in.atEnd()) {
        QString token;
        in >> token;
        if (!token.isEmpty()) {
            bool ok;
            int value = token.toInt(&ok);
            if (ok) enqueue(value);
        }
    }
    file.close();
    showStatusMessage("Queue cargado desde archivo");
}


void QueueController::drawQueue() {
    scene->clear();
    nodeItems.clear();
    textItems.clear();

    NodeQueue* current = queue.getFront();
    int x = 50, y = 100;
    int radius = 60;
    int spacing = 100;

    while (current) {

        QBrush brush = QBrush(Qt::black);
        if (current == queue.getFront())
            brush = QBrush(Qt::green);
        else if (current == queue.getRear())
            brush = QBrush(Qt::blue);

        QGraphicsEllipseItem* circle = scene->addEllipse(x, y, radius, radius,
                                                         QPen(Qt::black), brush);

        QGraphicsTextItem* text = scene->addText(QString::number(current->value));
        QRectF textRect = text->boundingRect();
        text->setPos(x + radius/2 - textRect.width()/2,
                     y + radius/2 - textRect.height()/2);

        nodeItems.push_back(circle);
        textItems.push_back(text);

        if (current == queue.getFront()) {
            QGraphicsTextItem* label = scene->addText("HEAD");
            label->setPos(x + radius/2 - label->boundingRect().width()/2,
                          y + radius + 10);
        }
        else if (current == queue.getRear()) {
            QGraphicsTextItem* label = scene->addText("TAIL");
            label->setPos(x + radius/2 - label->boundingRect().width()/2,
                          y + radius + 10);
        }

        if (current->next) {
            int startX = x + radius;
            int startY = y + radius / 2;
            int endX = x + spacing;
            int endY = y + radius / 2;

            scene->addLine(startX, startY, endX, endY, QPen(Qt::black));
            scene->addLine(endX - 10, endY - 5, endX, endY, QPen(Qt::black));
            scene->addLine(endX - 10, endY + 5, endX, endY, QPen(Qt::black));
        }

        x += spacing;
        current = current->next;
    }
}



void QueueController::showStatusMessage(const QString& msg) {
    if (mainWindow && mainWindow->statusBar())
        mainWindow->statusBar()->showMessage(msg, 2000);
}
