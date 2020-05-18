#include "own_iterator.h"

template<typename ValueType>
OwnIterator<ValueType>::OwnIterator(ValueType *p) :
    p(p)
{

}

template<typename ValueType>
OwnIterator<ValueType>::OwnIterator(const OwnIterator& it) :
    p(it.p)
{

}

template<typename ValueType>
bool OwnIterator<ValueType>::operator!=(OwnIterator const& other) const
{
    return p != other.p;
}

template<typename ValueType>
bool OwnIterator<ValueType>::operator==(OwnIterator const& other) const
{
    return p == other.p;
}

template<typename ValueType>
typename OwnIterator<ValueType>::reference OwnIterator<ValueType>::operator*() const
{
    return *p;
}

template<typename ValueType>
OwnIterator<ValueType> &OwnIterator<ValueType>::operator++()
{
    ++p;
    return *this;
}
