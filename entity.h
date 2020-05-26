#ifndef ENTITY_H
#define ENTITY_H

#include <list>

#include "allocator.h"

template<class T>
class Relation;

//interface
template<class T>
class Entity{
public:
    virtual void removeRelation(const T& name) = 0;
    virtual Relation<T>* getRelationWith(const T& name) = 0;
    virtual bool isRelatedTo(const T& name) = 0;
    virtual void setName(const T& name) = 0;
    virtual const T& getName() = 0;
    virtual std::list<Relation<T>, Alloc::Allocator <Relation<T>>>& getRelations() = 0;
protected:
     static int id_counter;
};

template<class T>
int Entity<T>::id_counter = 0;
#endif // ENTITY_H
