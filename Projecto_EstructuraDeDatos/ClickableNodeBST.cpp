#include "ClickableNodeBST.h"
#include <QPen>

ClickableNodeBST::ClickableNodeBST(NodeBST* node, const QRectF& rect, const QBrush& brush)
    : QGraphicsEllipseItem(rect), bstNode(node)
{
    setBrush(brush);
    setPen(QPen(Qt::black, 2));
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void ClickableNodeBST::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    emit nodeClicked(bstNode);
    QGraphicsEllipseItem::mousePressEvent(event);
}
