#include "relation.h"

Relation::Relation(Type type, Entity *f, Entity *s) {
    this->type = type;
    firstEntity = f;
    secondEntity = s;

    firstEntity->addRelation(this);
    secondEntity->addRelation(this);
}

bool Relation::equals(Relation r) {
    return this->name == r.name && this->firstEntity->getName() == r.getFirstEntity().getName() && this->secondEntity->getName() == r.getSecondEntity().getName();
}

Entity Relation::getFirstEntity() {

    return *firstEntity;
}

Entity Relation::getSecondEntity() {

    return *secondEntity;
}

void Relation::setFirstEntity(Entity *e) {

    firstEntity = e;
}

void Relation::setSecondEntity(Entity *e) {

    secondEntity = e;
}

void Relation::setType(Type type) {

    this->type = type;
}

void Relation::deleteRelation(){

    this->firstEntity->removeRelation(this);
    this->secondEntity->removeRelation(this);
    //add destructor

}
