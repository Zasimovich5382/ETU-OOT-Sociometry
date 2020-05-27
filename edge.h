#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode, int relType);

    Node *sourceNode() const;
    Node *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    bool hasOpposite;
    QColor color;
    Node *source, *dest;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
    int relType; // 0 - negative, 1 - positive
};

#endif // EDGE_H
