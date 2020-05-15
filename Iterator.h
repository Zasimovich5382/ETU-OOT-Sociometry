#pragma once
#include "ErContainer.h"
template<typename ValueType>
class Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	friend class ErContainer;
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

