#pragma once
#include "entity.h"
#include <list>
#include <string>

using namespace std;

enum Type
{
    TYPE_VAN,
    TYPE_TWO,
};


class Relation
{
private:
    string name;
    Type type;
    Entity firstEntity;
    Entity secondEntity;
public:
    Relation(Type tipe, Entity f, Entity t);
    bool equals(Relation r);
    Entity getFirstEntity();
    Entity getSecondEntity();
    void setFirstEntity(Entity entity);
    void setSecondEntity(Entity entity);
    void setType(Type type);

};
