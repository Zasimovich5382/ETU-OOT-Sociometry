#include "drawing_entity.h"

#include "drawing_entity.h"
#include <string>

DrawingEntity::DrawingEntity() :
    QGraphicsItem()
{

}

DrawingEntity::~DrawingEntity()
{

}

QRectF DrawingEntity::boundingRect() const
{
    return QRectF(-150,-150,500,800);
}

void DrawingEntity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);

    polygon << QPoint(centre.rx(),centre.ry()-40) << QPoint(centre.rx()+ 40,centre.ry() + 40) << QPoint(centre.rx() - 40,centre.ry() + 40);

    if(gender == MALE){

        painter->drawEllipse(centre, 40, 40);
        polygon << QPoint(centre.rx() +40,centre.ry()-40) << QPoint(centre.rx()+ 40,centre.ry() + 40) << QPoint(centre.rx() - 40,centre.ry() + 40)<< QPoint(centre.rx() +40,centre.ry()+40);
    }
    else{

        painter->drawPolygon(polygon);
    }

    painter->setFont(QFont("Arial", 8, QFont::Normal));

    char buf[40];
    sprintf(buf,"%d",id);

    painter->drawText(centre + QPointF(-4,4), buf);


    Q_UNUSED(option);
    Q_UNUSED(widget);
}

