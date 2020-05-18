#ifndef OWN_CONTAINER_H
#define OWN_CONTAINER_H
#include "own_iterator.h"
#include <memory>
#include "entity.h"
#include "relation.h"

using namespace std;
//template <typename T>
class OwnContainer
{
public:
    typedef OwnIterator<Entity> iterator;
    typedef OwnIterator<const Entity> const_iterator;


    OwnContainer(std::initializer_list<Entity> values);

    iterator begin(){
        return iterator(data.get());
    }
    iterator end()
    {
        return iterator(data.get() + size);
    }

    const_iterator begin() const
    {
        return const_iterator(data.get());
    }

    const_iterator end() const{
        return const_iterator(data.get() + size);
    }


    void addEntity(Entity *entity);
    void addRelation(Type type, Entity* first, Entity* second);
    void removeEntity(Entity *entity);
    void removeRelation(Relation *relation);


//private:
    const size_t size;
    unique_ptr<Entity[]> data;
};

#endif // OWN_CONTAINER_H
