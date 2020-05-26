#ifndef ER_CONTAINER_H
#define ER_CONTAINER_H

#include <list>

#include "iterator.h"
#include "socialentity.h"
#include "relation.h"
#include "allocator.h"

template <class T>
class ERContainer
{
    using entitiesType = std::list<SocialEntity<T>>;

public:
    using iterator = typename entitiesType::iterator;
    using entity = SocialEntity<T>;
    using relation = Relation<T> ;

    ERContainer();
    ERContainer(std::initializer_list<SocialEntity<T>> values);
    ~ERContainer();

    iterator begin() { return entities.begin(); }
    iterator end() { return entities.end(); }

    SocialEntity<T>* find(const T& name);

    size_t size() const;

    bool addEntity(SocialEntity<T> entity);
    bool addEntity(const T& name, Gender gender);
    bool addRelation(const T& first, const T& second, Type type);

    void removeEntity(const T& name);
    void removeRelation(const T& first, const T& second);

    void editRelation(const T& first, const T& second, Type newType);

    void clear();

private:
    std::list<SocialEntity<T>, Alloc::Allocator<SocialEntity<T>>> entities;
};

template<class T>
ERContainer<T>::ERContainer(){}

template<class T>
ERContainer<T>::ERContainer(std::initializer_list<SocialEntity<T>> values):
    entities(values)
{}

template<class T>
ERContainer<T>::~ERContainer()
{}

template<class T>
SocialEntity<T>* ERContainer<T>::find(const T& name)
{
    for(auto it = entities.begin(); it !=  entities.end(); it++){
        if ((*it).getName() == name) return &(*it);
    }
    return nullptr;
}

template<class T>
size_t ERContainer<T>::size() const
{
    return entities.size();
}

template<class T>
bool ERContainer<T>::addEntity(SocialEntity<T> entity)
{
    SocialEntity<T>* entry = find(entity.getName());
    if (!entry){
        entities.push_back(entity);
        return true;
    }
    return false;
}

template<class T>
bool ERContainer<T>::addEntity(const T &name, Gender gender)
{
    SocialEntity<T> e = SocialEntity<T>(name, gender);
    return addEntity(e);
}

template<class T>
bool ERContainer<T>::addRelation(const T &first, const T &second, Type type)
{

    SocialEntity<T>* firstEntity = find(first);
    SocialEntity<T>* secondEntity = find(second);

    if (!firstEntity || !secondEntity || firstEntity == secondEntity){
        return false;
    }

    firstEntity->addRelation(Relation<T>(firstEntity, secondEntity, type));
    return true;
}

template<class T>
void ERContainer<T>::removeEntity(const T& name)
{
    //remove relations with vertex
    for(auto it = entities.begin(); it != entities.end(); it++){
        (*it).removeRelation(name);
    }

    //remove vertex itself
    for(auto it = entities.begin(); it != entities.end(); it++){
        if ((*it).getName() == name){
            entities.erase(it);
            break;
        }
    }
}

template<class T>
void ERContainer<T>::removeRelation(const T& first, const T& second)
{
    SocialEntity<T>* firstEntity = find(first);

    if (!firstEntity)
        return;

    firstEntity->removeRelation(second);
}

template<class T>
void ERContainer<T>::editRelation(const T &first, const T &second, Type newType)
{
    SocialEntity<T>* firstEntity = find(first);
    if (!firstEntity) return;

    Relation<T>* r = firstEntity->getRelationWith(second);
    if (r) r->setType(newType);
}

template<class T>
void ERContainer<T>::clear()
{
    entities.clear();
}

#endif // ER_CONTAINER_H
