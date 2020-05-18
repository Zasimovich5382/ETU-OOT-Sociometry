#include "own_container.h"
#include <memory> // для std::unique_ptr
#include <iostream>


OwnContainer::OwnContainer(std::initializer_list<Entity> values) :
    size(values.size()),
    data(new Entity[size])
{
    std::copy(values.begin(), values.end(), data.get());
}

void OwnContainer::addEntity(Entity *entity){


    Entity newEntity[size+1];
    for(int i = 0; i < (int)size; i++){
        newEntity[i] = data[i];
    }
    newEntity[size] = *entity;

    std::unique_ptr<Entity[]> copy(newEntity);

    this->data = std::move(copy);
}

void OwnContainer::addRelation(Type type, Entity* first, Entity* second){

    new Relation(type, first, second);
}

void OwnContainer::removeEntity(Entity *entity){
    Entity newEntity[size-1];
    for(int i = 0; i < (int)size-1; i++){
        if(data[i].getName() != entity->getName())newEntity[i] = data[i];
    }


    std::unique_ptr<Entity[]> copy(newEntity);

    this->data = std::move(copy);
}

void OwnContainer::removeRelation(Relation *relation){
    relation->deleteRelation();
}
