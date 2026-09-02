#include "AVLController.h"
#include <QMessageBox>
#include <QGraphicsSimpleTextItem>
#include <QDebug>
#include <QThread>
#include <QApplication>
#include <QStatusBar>
#include <QFile>
#include <QTextStream>
#include <QtMath>


AVLController::AVLController(QGraphicsScene* scene, QMainWindow* window)
    : scene(scene), mainWindow(window) {
}

AVLController::~AVLController() {
    clear();
}

void AVLController::insert(int value) {
    tree.insert(value);
    drawTree();

    NodeAVL* found = tree.search(value);
    if (found && nodeMap.contains(found)) {
        QColor base = nodeColors.value(found, Qt::white);
        blinkNode(nodeMap[found], Qt::green, 3, 200, base);
    }

    showStatusMessage("Insertado: " + QString::number(value));
}

void AVLController::remove(int value) {
    NodeAVL* node = tree.search(value);
    if (!node) {
        showStatusMessage("No encontrado: " + QString::number(value));
        return;
    }

    QGraphicsEllipseItem* item = nodeMap.value(node, nullptr);
    if (!item) {
        tree.remove(value);
        drawTree();
        showStatusMessage("Eliminado: " + QString::number(value));
        return;
    }

    QColor base = nodeColors.value(node, Qt::white);

    blinkNode(item, Qt::red, 3, 160, base);

    tree.remove(value);
    drawTree();
    showStatusMessage("Eliminado: " + QString::number(value));
}


void AVLController::search(int value) {
    NodeAVL* found = tree.search(value);
    if (!found) {
        showStatusMessage("No encontrado: " + QString::number(value));
        return;
    }

    auto it = nodeMap.find(found);
    if (it != nodeMap.end()) {
        QColor base = nodeColors.value(found, Qt::white);
        blinkNode(it.value(), Qt::yellow, 3, 250, base);
    }
    showStatusMessage("Encontrado: " + QString::number(value));
}


void AVLController::clearScene() {
    for (auto* item : nodeItems) scene->removeItem(item);
    for (auto* label : labels) scene->removeItem(label);
    for (auto* edge : edges) scene->removeItem(edge);

    nodeItems.clear();
    labels.clear();
    edges.clear();
    nodeMap.clear();
    nodeColors.clear();
}

void AVLController::clear() {
    tree.clear();
    clearScene();
}

void AVLController::drawTree() {
    clearScene();
    if (!tree.getRoot()) return;
    drawNode(tree.getRoot(), 400, 50, 200);
}

void AVLController::drawNode(NodeAVL* node, int x, int y, int offset) {
    if (!node) return;

    int radius = 20;

    QColor fillColor = Qt::white;
    if (node == tree.getRoot()) {
        fillColor = QColor("#87CEFA");
    } else if (!node->left && !node->right) {
        fillColor = QColor("#FFA07A");
    } else {
        fillColor = QColor("#90EE90");
    }

    QRectF rect(x - radius, y - radius, 2 * radius, 2 * radius);
    ClickableNode* circle = new ClickableNode(node, rect, QBrush(fillColor));
    scene->addItem(circle);
    nodeItems.push_back(circle);

    QGraphicsTextItem* text = scene->addText(QString::number(node->value));
    text->setDefaultTextColor(Qt::black);
    text->setFont(QFont("Arial", 10, QFont::Bold));
    text->setPos(x - text->boundingRect().width() / 2,
                 y - text->boundingRect().height() /2);
    labels.push_back(text);

    nodeMap[node] = circle;
    nodeColors[node] = fillColor;

    int profundidad = tree.getDepth(node);
    int altura = node->height;
    int balance = tree.getBalance(node);

    circle->setToolTip(
        QString("Valor: %1\nProfundidad: %2\nAltura: %3\nBalance: %4")
            .arg(node->value)
            .arg(profundidad)
            .arg(altura)
            .arg(balance));

    QObject::connect(circle, &ClickableNode::nodeClicked, [=](NodeAVL* n) {
        if (mainWindow && mainWindow->statusBar()) {
            mainWindow->statusBar()->showMessage(
                QString("Nodo %1 | Profundidad: %2 | Altura: %3 | Balance: %4")
                    .arg(n->value)
                    .arg(profundidad)
                    .arg(altura)
                    .arg(balance));
        }
    });

    if (node->left) {
        int childX = x - offset;
        int childY = y + 80;
        drawEdge(x, y, childX, childY, radius);
        drawNode(node->left, childX, childY, offset / 2);
    }

    if (node->right) {
        int childX = x + offset;
        int childY = y + 80;
        drawEdge(x, y, childX, childY, radius);
        drawNode(node->right, childX, childY, offset / 2);
    }
}


void AVLController::blinkNode(QGraphicsEllipseItem* node,
                              const QColor& highlight,
                              int times,
                              int delayMs,
                              const QColor& normal) {
    if (!node) return;

    for (int i = 0; i < times; i++) {
        node->setBrush(QBrush(highlight));
        QApplication::processEvents();
        QThread::msleep(delayMs);

        node->setBrush(QBrush(normal));
        QApplication::processEvents();
        QThread::msleep(delayMs);
    }

    node->setBrush(QBrush(normal));
    QApplication::processEvents();
}

void AVLController::drawEdge(int x1, int y1, int x2, int y2, int radius) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double length = qSqrt(dx*dx + dy*dy);

    if (length == 0) return;

    double ux = dx / length;
    double uy = dy / length;

    int startX = x1 + ux * radius;
    int startY = y1 + uy * radius;
    int endX   = x2 - ux * radius;
    int endY   = y2 - uy * radius;

    QGraphicsLineItem* line = scene->addLine(startX, startY, endX, endY, QPen(Qt::black, 2));
    edges.push_back(line);
}

void AVLController::traverseInOrder() {
    QString result;
    QVector<NodeAVL*> order;
    traverseInOrderHelper(tree.getRoot(), order);

    int delay = 0;
    for (NodeAVL* node : order) {
        if (nodeMap.contains(node)) {
            QGraphicsEllipseItem* item = nodeMap[node];
            QColor normal = nodeColors.value(node, Qt::white);

            QTimer::singleShot(delay, [=]() {
                blinkNode(item, Qt::yellow, 2, 200, normal);
            });

            result += QString::number(node->value) + ", ";
            delay += 600;
        }
    }

    if (!result.isEmpty()) result.chop(2);
    showStatusMessage("InOrder: " + result);
}

void AVLController::traversePreOrder() {
    QString result;
    QVector<NodeAVL*> order;
    traversePreOrderHelper(tree.getRoot(), order);

    int delay = 0;
    for (NodeAVL* node : order) {
        if (nodeMap.contains(node)) {
            QGraphicsEllipseItem* item = nodeMap[node];
            QColor normal = nodeColors.value(node, Qt::white);

            QTimer::singleShot(delay, [=]() {
                blinkNode(item, Qt::yellow, 2, 200, normal);
            });

            result += QString::number(node->value) + ", ";
            delay += 600;
        }
    }

    if (!result.isEmpty()) result.chop(2);
    showStatusMessage("PreOrder: " + result);
}

void AVLController::traversePostOrder() {
    QString result;
    QVector<NodeAVL*> order;
    traversePostOrderHelper(tree.getRoot(), order);

    int delay = 0;
    for (NodeAVL* node : order) {
        if (nodeMap.contains(node)) {
            QGraphicsEllipseItem* item = nodeMap[node];
            QColor normal = nodeColors.value(node, Qt::white);

            QTimer::singleShot(delay, [=]() {
                blinkNode(item, Qt::yellow, 2, 200, normal);
            });

            result += QString::number(node->value) + ", ";
            delay += 600;
        }
    }

    if (!result.isEmpty()) result.chop(2);
    showStatusMessage("PostOrder: " + result);
}


void AVLController::traverseInOrderText() {
    QString result;
    traverseInOrderHelper(tree.getRoot(), result);
    if (!result.isEmpty()) result.chop(2);
    showStatusMessage("InOrder: " + result);
}

void AVLController::traversePreOrderText() {
    QString result;
    traversePreOrderHelper(tree.getRoot(), result);
    if (!result.isEmpty()) result.chop(2);
    showStatusMessage("PreOrder: " + result);
}

void AVLController::traversePostOrderText() {
    QString result;
    traversePostOrderHelper(tree.getRoot(), result);
    if (!result.isEmpty()) result.chop(2);
    showStatusMessage("PostOrder: " + result);
}

void AVLController::traverseInOrderHelper(NodeAVL* node, QString& result) {
    if (!node) return;
    traverseInOrderHelper(node->left, result);
    result += QString::number(node->value) + ", ";
    traverseInOrderHelper(node->right, result);
}

void AVLController::traversePreOrderHelper(NodeAVL* node, QString& result) {
    if (!node) return;
    result += QString::number(node->value) + ", ";
    traversePreOrderHelper(node->left, result);
    traversePreOrderHelper(node->right, result);
}

void AVLController::traversePostOrderHelper(NodeAVL* node, QString& result) {
    if (!node) return;
    traversePostOrderHelper(node->left, result);
    traversePostOrderHelper(node->right, result);
    result += QString::number(node->value) + ", ";
}

void AVLController::traverseInOrderHelper(NodeAVL* node, QVector<NodeAVL*>& order) {
    if (!node) return;
    traverseInOrderHelper(node->left, order);
    order.append(node);
    traverseInOrderHelper(node->right, order);
}

void AVLController::traversePreOrderHelper(NodeAVL* node, QVector<NodeAVL*>& order) {
    if (!node) return;
    order.append(node);
    traversePreOrderHelper(node->left, order);
    traversePreOrderHelper(node->right, order);
}

void AVLController::traversePostOrderHelper(NodeAVL* node, QVector<NodeAVL*>& order) {
    if (!node) return;
    traversePostOrderHelper(node->left, order);
    traversePostOrderHelper(node->right, order);
    order.append(node);
}

void AVLController::saveToFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    tree.save(out);
    file.close();
}

void AVLController::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&file);
    tree.load(in);
    file.close();
    drawTree();
}

void AVLController::showStatusMessage(const QString& msg) {
    if (mainWindow && mainWindow->statusBar()) {
        mainWindow->statusBar()->showMessage(msg, 4000);
    } else {
        qDebug() << msg;
    }
}
