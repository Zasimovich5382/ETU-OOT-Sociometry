#pragma once
#include "container.h"
#include "entity.h"
#include "relation.h"

template<typename ValueType>
class ErContainer : Container
{
	typedef Iterator<ValueType> iterator;
	typedef Iterator<ValueType> const_iterator;

	ErContainer(initializer_list<ValueType> values);

	virtual iterator begin();
	virtual iterator end();

	virtual const_iterator begin() const;
	virtual const_iterator end() const;

	const size_t size;

	unique_ptr<ValueType[]> data;

	virtual void clear();
};

