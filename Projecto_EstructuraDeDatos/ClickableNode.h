#ifndef CLICKABLENODE_H
#define CLICKABLENODE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include "AVL.h"

class ClickableNode : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    ClickableNode(NodeAVL* node, const QRectF& rect, const QBrush& brush);

signals:
    void nodeClicked(NodeAVL* node);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    NodeAVL* avlNode;
};

#endif // CLICKABLENODE_H
