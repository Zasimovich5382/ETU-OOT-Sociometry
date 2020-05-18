#ifndef CONTAINER_H
#define CONTAINER_H
#include "own_iterator.h"
#include <memory>
#include "entity.h"

class Container
{
public:
    typedef OwnIterator<Entity> iterator;
    typedef OwnIterator<const Entity> const_iterator;

    Container(std::initializer_list<Entity> values);

    virtual iterator begin();
    virtual iterator end();

    virtual const_iterator begin() const;
    virtual const_iterator end() const;

};

#endif // CONTAINER_H
