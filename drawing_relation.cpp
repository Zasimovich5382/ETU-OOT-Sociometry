#include "drawing_relation.h"

const qreal Pi = 3.14;

DrawingRelation::DrawingRelation()
{

}

DrawingRelation::~DrawingRelation()
{

}



void DrawingRelation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen myPen = pen();
    myPen.setColor(Qt::black);
    myPen.setStyle(Qt::SolidLine);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(Qt::black);

    QLineF centerLine(entityFirst->getCentre(), entitySecond->getCentre());



    QPolygonF endPolygon = entitySecond->getPolygon();
    QPointF p1 = endPolygon.first() + entitySecond->getCentre();
    QPointF intersectPoint2;
    for (int i = 1; i < endPolygon.count(); ++i) {
        QPointF p2 = endPolygon.at(i) ;
        QLineF polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType2 =
            polyLine.intersect(centerLine, &intersectPoint2);
        if (intersectType2 == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    QPolygonF firstPolygon = entityFirst->getPolygon();
    p1 = firstPolygon.first() + entityFirst->getCentre();
    QPointF intersectPoint1;
    QLineF polyLine;
    for (int i = 1; i < firstPolygon.count(); ++i) {
        QPointF p2 = firstPolygon.at(i) ;
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType1 =
            polyLine.intersect(centerLine, &intersectPoint1);
        if (intersectType1 == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }


    setLine(QLineF(intersectPoint2, intersectPoint1));//intersectPoint1



    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                            cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                            cos(angle + Pi - Pi / 3) * arrowSize);

    QPointF arrowP3 = line().p2() - QPointF(sin(angle + Pi / 3) * arrowSize,
                                            cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP4 = line().p2() - QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                            cos(angle + Pi - Pi / 3) * arrowSize);

    arrowHeadFirst.clear();
    arrowHeadLast.clear();
    arrowHeadFirst << line().p1() << arrowP1 << arrowP2;
    arrowHeadLast << line().p2() << arrowP3 << arrowP4;


//    if(type == CHOICE || type == REJECTION){
        painter->drawPolygon(arrowHeadFirst);
//    }
//    else if (type == MUTUALCHOICE || type == MUTUALREJECTION){
//        painter->drawPolygon(arrowHeadFirst);
//        painter->drawPolygon(arrowHeadLast);
//    }

    if(type == NEGATIVE){
        myPen.setStyle(Qt::DashLine);
        painter->setPen(myPen);
    }

    painter->drawLine(line());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void DrawingRelation::updatePosition()
{
    QLineF line(mapFromItem(entityFirst, 0, 0), mapFromItem(entitySecond, 0, 0));
    setLine(line);
}

