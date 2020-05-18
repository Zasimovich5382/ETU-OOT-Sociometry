

#include "relation.h"
#include <string>
#include <iostream>
#include <list>

#ifndef ENTITY_H
#define ENTITY_H
using namespace std;

class Relation;

class Entity
{
private:
    list<Relation*> relations;
    string name;

public:
    Entity();
    Entity(string name);
    void setName(string name);
    string getName();
    void addRelation(Relation *relation);
    void removeRelation(Relation *relations);
    void removeAllRelations();
    bool isRelatedTo(Entity *entity);
    list<Relation*> getRelations();
    void deleteEntity();


};

#endif // ENTITY_H
