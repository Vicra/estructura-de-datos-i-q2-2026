#ifndef CLICKABLENODEBST_H
#define CLICKABLENODEBST_H

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include "BST.h"

class ClickableNodeBST : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    ClickableNodeBST(NodeBST* node, const QRectF& rect, const QBrush& brush);

signals:
    void nodeClicked(NodeBST* node);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    NodeBST* bstNode;
};

#endif // CLICKABLENODEBST_H
