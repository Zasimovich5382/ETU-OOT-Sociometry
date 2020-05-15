#include "entity.h"

Entity::Entity() {

}

Entity::Entity(string name){

    this->name = name;
}

void Entity::setName(string name){

    this->name = name;
}
string Entity::getName() {

    return this->name;
}
void Entity::addRelation(Relation relation) {

    relations.push_back(relation);
}
void Entity::removeRelation(Relation relation) {

    list<Relation> copy = relations;

    for (auto iter = copy.begin(); iter != copy.end(); iter++)
    {
        Relation r = *iter;
        if (r.equals(relation)) relations.erase(iter);
    }

}
void Entity::removeAllRelations() {

    relations.clear();
}

bool Entity::isRelatedTo(Entity entity) {
    for (Relation r : relations) {
        if (r.getFirstEntity.equals(entity) || r.getSecondEntity.equals(entity))
            return true;
        return false;

    }
}

bool Entity::equals(Entity e) {

    return this->name == e.name;
}

