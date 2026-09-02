    #include "DoubleLinkedListController.h"
    #include <QGraphicsEllipseItem>
    #include <QGraphicsOpacityEffect>
    #include <QGraphicsTextItem>
    #include <QGraphicsLineItem>
    #include <QPropertyAnimation>
    #include <QBrush>
    #include <QPen>
    #include <QCoreApplication>
    #include <QThread>
    #include <QTimer>
    #include <QStatusBar>
    #include <QFile>
    #include <QTextStream>
    #include <QMessageBox>

    DoubleLinkedListController::DoubleLinkedListController(QGraphicsScene* scene, QMainWindow* window)
        : scene(scene), mainWindow(window) {}

    DoubleLinkedListController::~DoubleLinkedListController() {
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


    void DoubleLinkedListController::insertAt(int value, int position) {
        list.insertAt(value, position);
        redrawFromList();
        if (position >= 0 && position < nodeItems.size())
            animateAppearance(nodeItems[position]);
        showStatusMessage("Nodo insertado en pos " + QString::number(position));
    }

    void DoubleLinkedListController::removeAt(int position) {
        if (position < 0 || position >= nodeItems.size()) {
            showStatusMessage("Posición inválida");
            return;
        }
        animateRemoval(nodeItems[position]);

        QTimer::singleShot(600, [=]() {
            list.removeAt(position);
            redrawFromList();
            showStatusMessage("Nodo eliminado en pos " + QString::number(position));
        });
    }


    void DoubleLinkedListController::search(int position) {
        if (position < 0 || position >= nodeItems.size()) {
            showStatusMessage("Posición inválida");
            return;
        }

        for (auto n : nodeItems)
            n->setBrush(QBrush(Qt::blue));

        blinkNode(nodeItems[position], Qt::yellow, Qt::blue);

        showStatusMessage("Encontrado en posición " + QString::number(position));
    }

    void DoubleLinkedListController::traverseForward() {
        NodeDLL* current = list.getHead();
        int index = 0;
        while (current) {
            nodeItems[index]->setBrush(QBrush(Qt::cyan));
            QCoreApplication::processEvents();
            QThread::msleep(400);
            nodeItems[index]->setBrush(QBrush(Qt::blue));
            current = current->next;
            index++;
        }
        showStatusMessage("Recorrido hacia adelante");
    }

    void DoubleLinkedListController::traverseBackward() {
        NodeDLL* tail = list.getHead();
        if (!tail) return;
        while (tail->next) tail = tail->next;

        int index = nodeItems.size() - 1;
        while (tail) {
            nodeItems[index]->setBrush(QBrush(Qt::magenta));
            QCoreApplication::processEvents();
            QThread::msleep(400);
            nodeItems[index]->setBrush(QBrush(Qt::blue));
            tail = tail->prev;
            index--;
        }
        showStatusMessage("Recorrido hacia atrás");
    }

    void DoubleLinkedListController::clear() {
        scene->clear();
        nodeItems.clear();
        arrows.clear();
        list.clear();
    }


    void DoubleLinkedListController::animateAppearance(QGraphicsItem* item) {
        if (auto ellipse = dynamic_cast<QGraphicsEllipseItem*>(item))
            ellipse->setBrush(QBrush(Qt::green));

        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
        item->setGraphicsEffect(effect);

        QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
        anim->setDuration(600);
        anim->setStartValue(0.0);
        anim->setEndValue(1.0);
        anim->start(QAbstractAnimation::DeleteWhenStopped);

        QTimer::singleShot(800, [item]() {
            if (auto ellipse = dynamic_cast<QGraphicsEllipseItem*>(item))
                ellipse->setBrush(QBrush(Qt::blue));
        });
    }

    void DoubleLinkedListController::animateRemoval(QGraphicsItem* item) {
        if (auto ellipse = dynamic_cast<QGraphicsEllipseItem*>(item))
            ellipse->setBrush(QBrush(Qt::red));

        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
        item->setGraphicsEffect(effect);

        QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
        anim->setDuration(600);
        anim->setStartValue(1.0);
        anim->setEndValue(0.0);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }

    void DoubleLinkedListController::showStatusMessage(const QString& msg) {
        if (mainWindow) mainWindow->statusBar()->showMessage(msg, 2000);
    }

    void DoubleLinkedListController::redrawFromList() {
        scene->clear();
        nodeItems.clear();
        arrows.clear();

        NodeDLL* current = list.getHead();

        if (!current) {
            showStatusMessage("Lista vacía");
            return;
        }

        int index = 0;
        auto* nullLabelStart = scene->addText("nullptr");
        nullLabelStart->setPos(-60, 70);

        while (current) {
            qreal x = index * 120;

            auto* node = scene->addEllipse(x, 50, 50, 50, QPen(Qt::black), QBrush(Qt::blue));
            auto* label = new QGraphicsTextItem(QString::number(current->value), node);
            QRectF rect = node->rect();
            label->setPos(rect.x() + (rect.width() - label->boundingRect().width()) / 2,
                          rect.y() + (rect.height() - label->boundingRect().height()) / 2);
            nodeItems.push_back(node);

            if (current->next) {
                QPen pen(Qt::black);
                pen.setWidth(2);
                arrows.push_back(scene->addLine(x + 50, 75, (index + 1) * 120, 75, pen));
                arrows.push_back(scene->addLine((index + 1) * 120, 70, x + 50, 70, pen));
            }

            if (index == 0) {
                auto* headLabel = scene->addText("HEAD");
                headLabel->setDefaultTextColor(Qt::darkGreen);
                headLabel->setPos(x, 20);
            }

            if (!current->next) {
                auto* tailLabel = scene->addText("TAIL");
                tailLabel->setDefaultTextColor(Qt::darkRed);
                tailLabel->setPos(x, 110);
            }

            current = current->next;
            index++;
        }

        qreal x = index * 120;
        auto* nullLabelEnd = scene->addText("nullptr");
        nullLabelEnd->setPos(x, 70);
    }

    void DoubleLinkedListController::saveToFile(const QString& filename) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "TYPE:LIST\n";

            NodeDLL* current = list.getHead();
            while (current) {
                out << current->value << " ";
                current = current->next;
            }
            file.close();
            showStatusMessage("Lista doble guardada en: " + filename);
        } else {
            showStatusMessage("Error al guardar archivo");
        }
    }

    void DoubleLinkedListController::loadFromFile(const QString& filename) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            list.clear();
            QTextStream in(&file);

            QString header = in.readLine();
            if (header.trimmed() != "TYPE:LIST") {
                QMessageBox::warning(nullptr, "Error de carga",
                                     "No se pueden cargar estructuras de tipo TREE en listas (TYPE:LIST requerido).");
                return;
            }

            while (!in.atEnd()) {
                QString token;
                in >> token;
                if (!token.isEmpty()) {
                    bool ok;
                    int value = token.toInt(&ok);
                    if (ok) list.insert(value);
                }
            }

            file.close();
            redrawFromList();
            showStatusMessage("Lista doble cargada desde: " + filename);
        } else {
            showStatusMessage("Error al cargar archivo");
        }
    }



