#ifndef DRAWING_ENTITY_H
#define DRAWING_ENTITY_H

#include <QGraphicsItem>
#include <QPainter>
#include "socialentity.h"

// Наследуемся от QGraphicsItem

class DrawingEntity : public QGraphicsItem
{
public:
    DrawingEntity();

    //add template
    DrawingEntity(SocialEntity<std::string> *entity){
        this->gender = entity->getGender();
        this->id = entity->getID();
    }

    ~DrawingEntity();

    void setGender(Gender gender) {
        this->gender = gender;
    }

    Gender getGender() {
        return this->gender;
    }

    void setCentre(QPoint centre) {
        this->centre = centre;
    }

    QPoint getCentre() {
        return this->centre;
    }

    DrawingEntity(Gender gender, QPoint centre, int id){
        this->gender = gender;
        this->centre = centre;
        this->id = id;
    }

    void setID(int id) {
        this->id = id;
    }

    int getID() {
        return this->id;
    }


    QPolygon getPolygon(){
        return this->polygon;
    }

protected:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPolygon polygon;
    int id;
    Gender gender;
    QPoint centre = QPoint(0,0);
};


#endif // DRAWING_ENTITY_H
