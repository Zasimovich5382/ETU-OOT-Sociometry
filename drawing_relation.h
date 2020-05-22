#ifndef DRAWING_RELATION_H
#define DRAWING_RELATION_H

#include <QPainter>
#include "drawing_entity.h"
#include <qmath.h>
#include <QPen>
#include "relation.h"

class DrawingRelation : public  QGraphicsLineItem
{
public:
    DrawingRelation();

//    DrawingRelation(Relation<QString> *relation){
//        this->type = relation->getType();

//        this->entityFirst = DrawingEntity(relation->getFirstEntity());

//        this->entitySecond = DrawingEntity(relation->getSecondEntity());

//    }

    ~DrawingRelation();


    DrawingRelation(TypeRelation type, DrawingEntity *f, DrawingEntity *s){

        setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        this->type = type;
        this->entityFirst = f;
        this->entitySecond = s;
    }


protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    TypeRelation type;
    DrawingEntity *entityFirst;
    DrawingEntity *entitySecond;
    QPolygonF arrowHeadFirst;
    QPolygonF arrowHeadLast;

public slots:
    void updatePosition();

};
#endif // DRAWING_RELATION_H
