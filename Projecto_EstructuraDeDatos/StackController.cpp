#include "StackController.h"
#include <QGraphicsTextItem>
#include <QFile>
#include <QTextStream>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QThread>
#include <QCoreApplication>
#include <QPen>
#include <QBrush>
#include <qstatusbar.h>
#include <QMessageBox>

StackController::StackController(QGraphicsScene* scene, QMainWindow* window)
    : scene(scene), mainWindow(window) {}

StackController::~StackController() {
    clear();
}

void StackController::push(int value) {
    stack.push(value);
    redrawFromStack();
    if (!nodeItems.empty()) animateAppearance(nodeItems.back());
    showStatusMessage("Push: " + QString::number(value));
}

void StackController::pop() {
    if (stack.isEmpty()) {
        showStatusMessage("Pila vacía, no se puede hacer pop");
        return;
    }
    animateRemoval(nodeItems.back());
    stack.pop();
    redrawFromStack();
    showStatusMessage("Pop realizado");
}

void StackController::clear() {
    for (auto n : nodeItems) {
        if (n->scene()) scene->removeItem(n);
        delete n;
    }
    nodeItems.clear();

    for (auto a : arrows) {
        if (a->scene()) scene->removeItem(a);
        delete a;
    }
    arrows.clear();

    stack.clear();
    scene->clear();
}

void StackController::saveToFile(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "TYPE:LIST\n";

        NodeStack* current = stack.getTop();
        while (current) {
            out << current->value << " ";
            current = current->next;
        }
        file.close();
        showStatusMessage("Stack guardado en: " + filename);
    }
}

void StackController::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        stack.clear();
        QTextStream in(&file);

        QString header = in.readLine();
        if (header.trimmed() != "TYPE:LIST") {
            QMessageBox::warning(nullptr, "Error de carga",
                                 "No se pueden cargar estructuras de tipo TREE en Stack (TYPE:LIST requerido).");
            return;
        }

        QList<int> valores;
        QString token;
        while (!in.atEnd()) {
            in >> token;
            if (!token.isEmpty()) {
                bool ok;
                int value = token.toInt(&ok);
                if (ok) valores.append(value);
            }
        }
        file.close();

        for (int i = valores.size() - 1; i >= 0; --i) {
            stack.push(valores[i]);
        }

        redrawFromStack();
        showStatusMessage("Stack cargado desde: " + filename);
    } else {
        showStatusMessage("Error al cargar archivo");
    }
}

void StackController::redrawFromStack() {
    scene->clear();
    nodeItems.clear();
    arrows.clear();

    NodeStack* current = stack.getTop();
    int index = 0;

    while (current) {
        qreal y = index * 80;

        auto* node = scene->addEllipse(50, y, 60, 60, QPen(Qt::black), QBrush(Qt::red));
        auto* label = new QGraphicsTextItem(QString::number(current->value), node);

        QRectF rect = node->rect();
        label->setPos(rect.x() + (rect.width() - label->boundingRect().width()) / 2,
                      rect.y() + (rect.height() - label->boundingRect().height()) / 2);

        nodeItems.push_back(node);

        if (index == 0) {
            auto* topLabel = scene->addText("TOP");
            topLabel->setDefaultTextColor(Qt::white);
            topLabel->setPos(rect.x() + (rect.width() - topLabel->boundingRect().width()) / 2,
                             rect.y() - topLabel->boundingRect().height() - 5);
        }

        if (current->next) {
            qreal x1 = 80;
            qreal y1 = y + 60;
            qreal x2 = 80;
            qreal y2 = y + 80;

            auto* line = scene->addLine(x1, y1, x2, y2, QPen(Qt::black, 2));
            arrows.push_back(line);

            QPolygonF triangle;
            triangle << QPointF(x2 - 7, y2 - 7) << QPointF(x2 + 7, y2 - 7) << QPointF(x2, y2);
            auto* arrowHead = scene->addPolygon(triangle, QPen(Qt::black), QBrush(Qt::black));
            arrows.push_back(arrowHead);
        }

        current = current->next;
        index++;
    }

    qreal y = index * 80;
    auto* nullLabel = scene->addText("nullptr");
    nullLabel->setDefaultTextColor(Qt::white);
    nullLabel->setPos(70, y + 20);
}

void StackController::peek() {
    if (stack.isEmpty()) {
        showStatusMessage("Stack vacío (no hay TOP)");
        return;
    }

    if (!nodeItems.empty()) {
        nodeItems[0]->setBrush(QBrush(Qt::yellow));
        showStatusMessage("Peek: " + QString::number(stack.peek()));
        QTimer::singleShot(1000, [this]() {
            if (!nodeItems.empty())
                nodeItems[0]->setBrush(QBrush(Qt::red));
        });
    }
}

void StackController::search(int index) {
    if (stack.isEmpty()) {
        showStatusMessage("Stack vacío");
        return;
    }

    if (index < 0 || index >= nodeItems.size()) {
        showStatusMessage("Posición inválida en el stack");
        return;
    }

    for (int k = 0; k < 3; k++) {
        nodeItems[index]->setBrush(QBrush(Qt::yellow));
        QCoreApplication::processEvents();
        QThread::msleep(300);
        nodeItems[index]->setBrush(QBrush(Qt::red));
        QCoreApplication::processEvents();
        QThread::msleep(300);
    }

    showStatusMessage("Valor en posición " + QString::number(index) +
                      " = " + QString::number(stack.getTop()->value));
}


void StackController::traverse(bool topToBottom) {
    if (stack.isEmpty()) {
        showStatusMessage("Stack vacío, no se puede recorrer");
        return;
    }

    if (topToBottom) {
        for (int i = 0; i < nodeItems.size(); i++) {
            nodeItems[i]->setBrush(QBrush(Qt::magenta));
            QCoreApplication::processEvents();
            QThread::msleep(400);
            nodeItems[i]->setBrush(QBrush(Qt::red));
        }
        showStatusMessage("Recorrido: TOP → Bottom");
    } else {
        for (int i = nodeItems.size() - 1; i >= 0; i--) {
            nodeItems[i]->setBrush(QBrush(Qt::green));
            QCoreApplication::processEvents();
            QThread::msleep(400);
            nodeItems[i]->setBrush(QBrush(Qt::red));
        }
        showStatusMessage("Recorrido: Bottom → TOP");
    }
}

void StackController::animateAppearance(QGraphicsItem* item) {
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
    item->setGraphicsEffect(effect);

    QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(500);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void StackController::animateRemoval(QGraphicsItem* item) {
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
    item->setGraphicsEffect(effect);

    QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(500);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void StackController::showStatusMessage(const QString& msg) {
    if (mainWindow && mainWindow->statusBar())
        mainWindow->statusBar()->showMessage(msg, 2000);
}
