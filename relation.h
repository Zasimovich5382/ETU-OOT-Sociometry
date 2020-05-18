#ifndef RELATION_H
#define RELATION_H


#include "entity.h"
#include <list>
#include <string>

using namespace std;

class Entity;

    enum Type
{
    TYPE_VAN,
    TYPE_TWO,
};


class Relation
{
private:
    string name; //ыозможно не нужно
    Type type;
    Entity *firstEntity;
    Entity *secondEntity;
public:
    Relation(Type tipe, Entity *f, Entity *t);
    bool equals(Relation r);
    Entity getFirstEntity();
    Entity getSecondEntity();
    void setFirstEntity(Entity *entity);
    void setSecondEntity(Entity *entity);
    void setType(Type type);
    void deleteRelation();

};


#endif // RELATION_H
