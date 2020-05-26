#ifndef ITERATOR_H
#define ITERATOR_H

#include <string>
#include <list>

#include "socialentity.h"


template<class T>
class ERContainer;

template<class T>
class EntityIterator{
    typedef SocialEntity<T>  valueType;
    typedef SocialEntity<T>& reference;
    typedef SocialEntity<T>* pointer;

    friend class ERContainer<T>;

public:
    EntityIterator();
    EntityIterator(const EntityIterator& it);

    bool operator!=(EntityIterator const& other) const;
    bool operator==(EntityIterator const& other) const;

    reference operator*() const;

    EntityIterator& operator++();
    EntityIterator& operator++(int);

private:
    EntityIterator(SocialEntity<T>* ptr);
    SocialEntity<T>* ptr;
};

template<class T>
EntityIterator<T>::EntityIterator():
    ptr(nullptr)
{}

template<class T>
EntityIterator<T>::EntityIterator(SocialEntity<T>* ptr):
    ptr(ptr)
{}

template<class T>
EntityIterator<T>::EntityIterator(const EntityIterator& other):
    ptr(other.ptr)
{}

template<class T>
bool EntityIterator<T>::operator!=(EntityIterator const& other) const
{
    return ptr != other.ptr;
}

template<class T>
bool EntityIterator<T>::operator==(EntityIterator const& other) const
{
    return ptr == other.ptr;
}

template<class T>
typename EntityIterator<T>::reference EntityIterator<T>::operator*() const
{
    return *ptr;
}

template<class T>
EntityIterator<T>& EntityIterator<T>::operator++()
{
    ptr++;
    return *this;
}

template<class T>
EntityIterator<T>& EntityIterator<T>::operator++(int)
{
    auto it = this;
    ptr++;
    return *it;
}

#endif // ITERATOR_H
