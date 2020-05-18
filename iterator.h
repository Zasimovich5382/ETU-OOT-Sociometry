#include <string>
#include <iostream>
#include <list>
#include "er_container.h"

#ifndef ITERATOR_H
#define ITERATOR_H


template<typename ValueType>
class Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
//    friend class ErContainer<ValueType>;
private:
    Iterator(ValueType* p);
public:
    Iterator(const Iterator& it);

    bool operator!=(Iterator const& other) const;
    bool operator==(Iterator const& other) const; //need for BOOST_FOREACH
    typename Iterator::reference operator*() const;
    Iterator& operator++();
private:
    ValueType* p;
};

#endif // ITERATOR_H
