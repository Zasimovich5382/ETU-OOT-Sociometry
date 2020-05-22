#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QList>

class Edge;
class GraphWidget;

class Node : public QGraphicsItem
{
public:
    Node(int id, int gender, GraphWidget *graphWidget, int size=30);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void calculateForces();
    bool advance();

    void setColor(QColor color);
    void setGravity(bool flag);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    bool forces;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int nodeSize;
    int gender; // 0 - male, 1 - female
    int id;

    QColor color;
    QList<Edge *> edgeList;

    QPointF newPos;
    GraphWidget *graph;
};

#endif // NODE_H
