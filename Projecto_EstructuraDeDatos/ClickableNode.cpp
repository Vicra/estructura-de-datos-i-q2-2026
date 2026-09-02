#include "ClickableNode.h"
#include <qpen.h>

ClickableNode::ClickableNode(NodeAVL* node, const QRectF& rect, const QBrush& brush)
    : QGraphicsEllipseItem(rect), avlNode(node)
{
    setBrush(brush);
    setPen(QPen(Qt::black, 2));
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void ClickableNode::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    emit nodeClicked(avlNode);
    QGraphicsEllipseItem::mousePressEvent(event);
}
