#include "edge.h"
#include "node.h"

#include <QtMath>
#include <QDebug>
#include <QPainter>

Edge::Edge(Node *sourceNode, Node *destNode, int relType)
    : arrowSize(10)
{
    color = Qt::black;
    hasOpposite = false;
    this->relType = relType;
    setAcceptedMouseButtons(0);

    source = sourceNode;
    dest = destNode;

    source->addEdge(this);
    dest->addEdge(this);

    adjust();
}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }

    if(hasOpposite){
        float angle = atan2f((destPoint - sourcePoint).x(), (destPoint - sourcePoint).y());
        QPointF angle_off(5 * cosf(angle), 5 * sinf(-angle));

        sourcePoint += angle_off;
        destPoint += angle_off;
    }
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);

    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    if(relType == 0){
        painter->setPen(QPen(color, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else {
        painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    painter->drawLine(line);

    // Draw the arrows
    double angle = std::atan2(-line.dy(), line.dx());

//    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
//                                                  cos(angle + M_PI / 3) * arrowSize);
//    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
//                                                  cos(angle + M_PI - M_PI / 3) * arrowSize);
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(color);
//    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);

    if(color != Qt::black)
        painter->setPen(QPen(color, 1));
    else
        painter->setPen(QPen(Qt::red, 1));

//    QString data_repr = QString::number(id);
//    QPointF sPos = source->pos(), dPos = dest->pos();
//    painter->drawText((sPos.x()+dPos.x())/2 + 5, (sPos.y()+dPos.y())/2 + 5, data_repr);
}

