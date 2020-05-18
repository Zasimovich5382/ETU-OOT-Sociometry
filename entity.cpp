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
void Entity::addRelation(Relation *relation) {

    relations.push_back(relation);
}

void Entity::removeRelation(Relation *relation) {

    for (auto iter = relations.begin(); iter != relations.end(); iter++)
    {
        Relation* r = *iter;
        if (r->equals(*relation)) {
            relations.erase(iter);
            break;
        }

    }


}
void Entity::removeAllRelations() {

    relations.clear();
}

bool Entity::isRelatedTo(Entity *entity) {
    for (auto iter = relations.begin(); iter != relations.end(); iter++)
    {
        Relation* r = *iter;
        if (r->getFirstEntity().getName() == entity->getName() || r->getSecondEntity().getName() == entity->getName()) return true;
    }

    return false;
}

list<Relation*> Entity::getRelations(){
    return this->relations;
}

void Entity::deleteEntity(){

    for (auto iter = relations.begin(); iter != relations.end(); iter++)
    {
        Relation* r = *iter;
        r->deleteRelation();
    }
    //add destructor
}
