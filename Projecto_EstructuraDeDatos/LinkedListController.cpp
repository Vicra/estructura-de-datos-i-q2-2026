#include "LinkedListController.h"
#include <QGraphicsTextItem>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QCoreApplication>
#include <QPen>
#include <QBrush>
#include <QVariantAnimation>
#include <QStatusBar>
#include <QInputDialog>
#include <QPolygonF>
#include <QDebug>

LinkedListController::LinkedListController(QGraphicsScene* scene, QMainWindow* window)
    : scene(scene), mainWindow(window) {}

LinkedListController::~LinkedListController() {
    clear();
}

static void blinkNode(QGraphicsEllipseItem* node, QColor highlight, QColor normal, int times = 3, int delayMs = 200) {
    for (int i = 0; i < times; i++) {
        node->setBrush(QBrush(highlight));
        QCoreApplication::processEvents();
        QThread::msleep(delayMs);

        node->setBrush(QBrush(normal));
        QCoreApplication::processEvents();
        QThread::msleep(delayMs);
    }
    node->setBrush(QBrush(normal));
}

void LinkedListController::insert(int value) {
    bool ok;
    int position = QInputDialog::getInt(mainWindow, "Insertar nodo",
                                        "Posición:", 0, 0, 999, 1, &ok);
    if (ok) {
        list.insertAt(value, position);
        showStatusMessage("Nodo insertado en posición " + QString::number(position));
        redrawFromList();
    }
}

void LinkedListController::insertAt(int value, int position) {
    list.insertAt(value, position);
    showStatusMessage("Nodo insertado en posición " + QString::number(position));
    redrawFromList();
}

void LinkedListController::remove(int) {
    bool okPos, okVal;
    int position = QInputDialog::getInt(mainWindow, "Eliminar nodo",
                                        "Posición:", 0, 0, 999, 1, &okPos);
    if (!okPos) return;

    int value = QInputDialog::getInt(mainWindow, "Eliminar nodo",
                                     "Valor esperado:", 0, -999999, 999999, 1, &okVal);
    if (!okVal) return;

    Node* current = list.getHead();
    int index = 0;
    while (current) {
        if (index == position) {
            if (current->value == value) {
                if (list.removeAt(position)) {
                    showStatusMessage("Nodo eliminado en posición " + QString::number(position) +
                                      " con valor " + QString::number(value));
                    redrawFromList();
                }
                return;
            } else {
                showStatusMessage("Error: en la posición " + QString::number(position) +
                                  " está el valor " + QString::number(current->value) +
                                  ", no " + QString::number(value));
                return;
            }
        }
        index++;
        current = current->next;
    }

    showStatusMessage("Posición inválida: " + QString::number(position));
}


void LinkedListController::removeAt(int position) {
    if (list.removeAt(position)) {
        if (position >= 0 && position < nodeItems.size()) {
            if (nodeItems[position]->scene()) scene->removeItem(nodeItems[position]);
            delete nodeItems[position];
            nodeItems.removeAt(position);
            if (position < labels.size()) {
                if (labels[position]->scene()) scene->removeItem(labels[position]);
                delete labels[position];
                labels.removeAt(position);
            }
            if (position < arrows.size()) {
                if (arrows[position]->scene()) scene->removeItem(arrows[position]);
                delete arrows[position];
                arrows.removeAt(position);
            }
        }
        showStatusMessage("Nodo eliminado en posición " + QString::number(position));
        redrawFromList();
    } else {
        showStatusMessage("Posición inválida: " + QString::number(position));
    }
}



void LinkedListController::clear() {
    for (auto arrow : arrows) {
        if (arrow->scene()) scene->removeItem(arrow);
        delete arrow;
    }
    arrows.clear();

    for (auto node : nodeItems) {
        if (node->scene()) scene->removeItem(node);
        delete node;
    }
    nodeItems.clear();

    for (auto l : labels) {
        if (l->scene()) scene->removeItem(l);
        delete l;
    }
    labels.clear();

    list.clear();
}



void LinkedListController::search(int) {
    bool okPos, okVal;
    int position = QInputDialog::getInt(mainWindow, "Buscar nodo",
                                        "Posición:", 0, 0, 999, 1, &okPos);
    if (!okPos) return;

    int value = QInputDialog::getInt(mainWindow, "Buscar nodo",
                                     "Valor esperado:", 0, -999999, 999999, 1, &okVal);
    if (!okVal) return;

    Node* current = list.getHead();
    int index = 0;
    while (current) {
        if (index == position) {
            if (current->value == value) {
                if (index >= 0 && index < nodeItems.size()) {
                    blinkNode(nodeItems[index], Qt::yellow, Qt::cyan);
                    showStatusMessage("Nodo encontrado en posición " + QString::number(position) +
                                      " con valor " + QString::number(value));
                }
                return;
            } else {
                showStatusMessage("Error: en la posición " + QString::number(position) +
                                  " está el valor " + QString::number(current->value));
                return;
            }
        }
        current = current->next;
        index++;
    }

    showStatusMessage("Posición inválida: " + QString::number(position));
}


void LinkedListController::animateAppearance(QGraphicsItem* item) {
    QVariantAnimation* anim = new QVariantAnimation();
    anim->setDuration(300);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);

    QObject::connect(anim, &QVariantAnimation::valueChanged, [item](const QVariant &v){
        item->setOpacity(v.toDouble());
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void LinkedListController::animateRemoval(QGraphicsItem* item) {
    QVariantAnimation* anim = new QVariantAnimation();
    anim->setDuration(300);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);

    QObject::connect(anim, &QVariantAnimation::valueChanged, [item](const QVariant &v){
        item->setOpacity(v.toDouble());
    });

    QObject::connect(anim, &QVariantAnimation::finished, [this, item]() {
        if (item->scene()) scene->removeItem(item);
        delete item;
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void LinkedListController::showStatusMessage(const QString& msg) {
    if (mainWindow && mainWindow->statusBar()) {
        mainWindow->statusBar()->showMessage(msg, 2000);
    }
}

void LinkedListController::redrawFromList() {
    for (auto arrow : arrows) {
        if (arrow->scene()) scene->removeItem(arrow);
        delete arrow;
    }
    arrows.clear();

    for (auto node : nodeItems) {
        if (node->scene()) scene->removeItem(node);
        delete node;
    }
    nodeItems.clear();

    for (auto label : labels) {
        if (label->scene()) scene->removeItem(label);
        delete label;
    }
    labels.clear();

    Node* current = list.getHead();
    int index = 0;

    if (!current) {
        auto* nullLabel = scene->addText("nullptr");
        nullLabel->setDefaultTextColor(Qt::red);
        nullLabel->setPos(0, 65);
        labels.push_back(nullLabel);
        return;
    }

    while (current) {
        qreal x = index * 120;

        auto* node = scene->addEllipse(x, 50, 60, 60, QPen(Qt::black), QBrush(Qt::cyan));
        nodeItems.push_back(node);

        auto* label = new QGraphicsTextItem(QString::number(current->value), node);
        label->setDefaultTextColor(Qt::black);

        QRectF rect = node->rect();
        QRectF textRect = label->boundingRect();
        label->setPos(rect.x() + (rect.width() - textRect.width()) / 2,
                      rect.y() + (rect.height() - textRect.height()) / 2);

        if (current->next) {
            QPen pen(Qt::black);
            pen.setWidth(2);

            qreal startX = x + 60;
            qreal startY = 80;
            qreal endX = (index + 1) * 120;
            qreal endY = 80;

            auto* arrowLine = scene->addLine(startX, startY, endX, endY, pen);

            QPolygonF arrowHead;
            arrowHead << QPointF(endX, endY)
                      << QPointF(endX - 10, endY - 5)
                      << QPointF(endX - 10, endY + 5);

            auto* arrowPolygon = scene->addPolygon(arrowHead, pen, QBrush(Qt::black));

            arrows.push_back(arrowLine);
            arrows.push_back(arrowPolygon);

        }

        current = current->next;
        index++;
    }

    qreal lastX = (index) * 120;
    auto* nullLabel = scene->addText("nullptr");
    nullLabel->setDefaultTextColor(Qt::red);
    nullLabel->setPos(lastX, 65);
    labels.push_back(nullLabel);
}

void LinkedListController::traverse() {
    for (auto n : nodeItems)
        n->setBrush(QBrush(Qt::cyan));

    Node* current = list.getHead();
    int index = 0;

    while (current) {
        if (index >= 0 && index < nodeItems.size()) {
            nodeItems[index]->setBrush(QBrush(Qt::darkBlue));
            QCoreApplication::processEvents();
            QThread::msleep(400);

            nodeItems[index]->setBrush(QBrush(Qt::cyan));
        }

        current = current->next;
        index++;
    }

    showStatusMessage("Recorrido completado");
}

void LinkedListController::saveToFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    list.save(out);
    file.close();
}

void LinkedListController::loadFromFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    list.load(in);
    file.close();

    redrawFromList();
}





