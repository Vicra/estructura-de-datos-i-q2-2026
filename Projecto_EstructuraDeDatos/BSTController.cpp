#include "BSTController.h"
#include <QGraphicsTextItem>
#include <QFile>
#include <QTextStream>
#include <QPen>
#include <QBrush>
#include <QCoreApplication>
#include <QThread>
#include <qstatusbar.h>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QGraphicsColorizeEffect>

BSTController::BSTController(QGraphicsScene* scene, QMainWindow* window)
    : scene(scene), mainWindow(window) {}

BSTController::~BSTController() {
    clear();
}

void BSTController::blinkNode(QGraphicsEllipseItem* node,
                              const QColor& highlight,
                              int times,
                              int delayMs,
                              const QColor& baseColor,
                              std::function<void()> onFinished)
{
    if (!node || !node->scene()) {
        if (onFinished) onFinished();
        return;
    }

    for (int i = 0; i < times; ++i) {
        if (!node->scene()) break;
        node->setBrush(QBrush(highlight));
        QCoreApplication::processEvents();
        QThread::msleep(delayMs);

        if (!node->scene()) break;
        node->setBrush(QBrush(baseColor));
        QCoreApplication::processEvents();
        QThread::msleep(delayMs);
    }

    if (node->scene()) node->setBrush(QBrush(baseColor));
    QCoreApplication::processEvents();

    if (onFinished) onFinished();
}

void BSTController::insert(int value) {
    tree.insert(value);

    NodeBST* newNode = tree.getLastInserted();
    if (!newNode) {
        showStatusMessage("Error al insertar nodo");
        return;
    }

    drawTree();

    QGraphicsEllipseItem* item = nodeMap.value(newNode, nullptr);
    if (item && item->scene()) {
        QColor base = nodeColors.value(newNode, Qt::white);
        blinkNode(item, Qt::green, 2, 180, base);
    }

    showStatusMessage(QString("Insertado: %1").arg(value));
}

void BSTController::remove(int value) {
    NodeBST* node = tree.search(value);
    if (!node) {
        showStatusMessage(QString("No encontrado: %1").arg(value));
        return;
    }

    QGraphicsEllipseItem* item = nodeMap.value(node, nullptr);
    if (!item) {
        tree.remove(value);
        drawTree();
        showStatusMessage(QString("Eliminado: %1").arg(value));
        return;
    }

    QColor base = nodeColors.value(node, Qt::white);
    blinkNode(item, Qt::red, 3, 160, base);

    tree.remove(value);
    drawTree();
    showStatusMessage(QString("Eliminado: %1").arg(value));
}

void BSTController::search(int value) {
    NodeBST* node = tree.search(value);
    if (!node) {
        showStatusMessage(QString("No encontrado: %1").arg(value));
        return;
    }

    QGraphicsEllipseItem* item = nodeMap.value(node, nullptr);
    if (!item) {
        showStatusMessage(QString("Encontrado (no visible): %1").arg(value));
        return;
    }

    QColor base = nodeColors.value(node, Qt::white);
    blinkNode(item, Qt::yellow, 3, 180, base);
    showStatusMessage(QString("Encontrado: %1").arg(value));
}

void BSTController::clear() {
    if (scene) scene->clear();
    nodeItems.clear();
    labels.clear();
    edges.clear();
    nodeMap.clear();
    nodeColors.clear();

    tree.clear();
    showStatusMessage("Árbol limpiado");
}

void BSTController::saveToFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    tree.save(out);
    file.close();
    showStatusMessage("Árbol guardado en archivo");
}

void BSTController::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    tree.clear();
    QTextStream in(&file);
    tree.load(in);
    file.close();

    drawTree();
    showStatusMessage("Árbol cargado desde archivo");
}

void BSTController::drawTree() {
    if (!scene) return;

    scene->clear();
    nodeItems.clear();
    labels.clear();
    edges.clear();
    nodeMap.clear();
    nodeColors.clear();

    NodeBST* root = tree.getRoot();
    if (!root) return;

    int startX = int(scene->width() / 2);
    int startY = 50;
    int dx = int(scene->width() / 4);
    if (dx < 60) dx = 120;

    drawNode(root, startX, startY, dx);
}

int BSTController::getDepth(NodeBST* root, NodeBST* target, int depth) {
    if (!root) return -1;
    if (root == target) return depth;
    if (target->value < root->value)
        return getDepth(root->left, target, depth + 1);
    else
        return getDepth(root->right, target, depth + 1);
}

int BSTController::getHeight(NodeBST* node) {
    if (!node) return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

int BSTController::getBalance(NodeBST* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}


void BSTController::drawNode(NodeBST* node, int x, int y, int dx) {
    if (!node) return;

    QColor fillColor = Qt::white;
    if (node == tree.getRoot()) {
        fillColor = rootColor;
    } else if (!node->left && !node->right) {
        fillColor = leafColor;
    } else {
        fillColor = innerColor;
    }

    QRectF rect(x - 20, y - 20, 40, 40);
    ClickableNodeBST* circle = new ClickableNodeBST(node, rect, QBrush(fillColor));
    scene->addItem(circle);

    QGraphicsTextItem* text = scene->addText(QString::number(node->value));
    text->setDefaultTextColor(Qt::black);
    text->setFont(QFont("Arial", 10, QFont::Bold));
    text->setPos(x - text->boundingRect().width() / 2,
                 y - text->boundingRect().height() / 2);

    nodeItems.append(circle);
    labels.append(text);
    nodeMap[node] = circle;
    nodeColors[node] = fillColor;

    QObject::connect(circle, &ClickableNodeBST::nodeClicked, [=](NodeBST* n) {
        if (mainWindow && mainWindow->statusBar()) {
            int depth = getDepth(this->tree.getRoot(), n);
            int height = getHeight(n);
            int balance = getBalance(n);

            mainWindow->statusBar()->showMessage(
                QString("Nodo %1 | Profundidad: %2 | Altura: %3 | Balance: %4")
                    .arg(n->value)
                    .arg(depth)
                    .arg(height)
                    .arg(balance)
                );
        }
    });

    if (node->left) {
        int childX = x - dx;
        int childY = y + 80;

        QLineF line(QPointF(x, y), QPointF(childX, childY));
        line.setLength(line.length() - 20);

        QLineF startLine(line);
        startLine.setLength(20);

        QGraphicsLineItem* l = scene->addLine(
            startLine.p2().x(), startLine.p2().y(),
            line.p2().x(), line.p2().y(),
            QPen(Qt::black, 2)
            );
        edges.append(l);

        drawNode(node->left, childX, childY, dx / 2);
    }

    if (node->right) {
        int childX = x + dx;
        int childY = y + 80;

        QLineF line(QPointF(x, y), QPointF(childX, childY));
        line.setLength(line.length() - 20);

        QLineF startLine(line);
        startLine.setLength(20);

        QGraphicsLineItem* r = scene->addLine(
            startLine.p2().x(), startLine.p2().y(),
            line.p2().x(), line.p2().y(),
            QPen(Qt::black, 2)
            );
        edges.append(r);

        drawNode(node->right, childX, childY, dx / 2);
    }
}

void BSTController::traverseInOrder() {
    QString result;
    traverseInOrderHelper(tree.getRoot(), result);
    if (!result.isEmpty()) result.chop(2);
    showStatusMessage("InOrder: " + result);
}

void BSTController::traverseInOrderHelper(NodeBST* node, QString& result) {
    if (!node) return;
    traverseInOrderHelper(node->left, result);

    QGraphicsEllipseItem* c = nodeMap.value(node, nullptr);
    if (c && c->scene()) {
        QColor base = nodeColors.value(node, Qt::white);
        blinkNode(c, Qt::cyan, 2, 220, base);
    }
    result += QString::number(node->value) + ", ";

    traverseInOrderHelper(node->right, result);
}

void BSTController::traversePreOrder() {
    QString result;
    traversePreOrderHelper(tree.getRoot(), result);
    if (!result.isEmpty()) result.chop(2);
    showStatusMessage("PreOrder: " + result);
}

void BSTController::traversePreOrderHelper(NodeBST* node, QString& result) {
    if (!node) return;
    QGraphicsEllipseItem* c = nodeMap.value(node, nullptr);
    if (c && c->scene()) {
        QColor base = nodeColors.value(node, Qt::white);
        blinkNode(c, Qt::cyan, 2, 220, base);
    }
    result += QString::number(node->value) + ", ";
    traversePreOrderHelper(node->left, result);
    traversePreOrderHelper(node->right, result);
}

void BSTController::traversePostOrder() {
    QString result;
    traversePostOrderHelper(tree.getRoot(), result);
    if (!result.isEmpty()) result.chop(2);
    showStatusMessage("PostOrder: " + result);
}

void BSTController::traversePostOrderHelper(NodeBST* node, QString& result) {
    if (!node) return;
    traversePostOrderHelper(node->left, result);
    traversePostOrderHelper(node->right, result);
    QGraphicsEllipseItem* c = nodeMap.value(node, nullptr);
    if (c && c->scene()) {
        QColor base = nodeColors.value(node, Qt::white);
        blinkNode(c, Qt::cyan, 2, 220, base);
    }
    result += QString::number(node->value) + ", ";
}

void BSTController::showStatusMessage(const QString& msg) {
    if (mainWindow && mainWindow->statusBar())
        mainWindow->statusBar()->showMessage(msg, 3000);
}
