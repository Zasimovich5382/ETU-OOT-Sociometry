#ifndef OWN_ITERATOR_H
#define OWN_ITERATOR_H
#include <list>
//#include "own_container.h"
using namespace std;

template<typename ValueType>
class OwnIterator: public std::iterator<std::input_iterator_tag, ValueType>
{
    friend class OwnContainer;//<ValueType>;
private:
    OwnIterator(ValueType* p);
public:
    OwnIterator(const OwnIterator &it);

    bool operator!=(OwnIterator const& other) const;
    bool operator==(OwnIterator const& other) const; //need for BOOST_FOREACH
    typename OwnIterator::reference operator*() const;
    OwnIterator& operator++();
private:
    ValueType* p;
};


#endif // OWN_ITERATOR_H
