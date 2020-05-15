#pragma once
#include "Iterator.h"
#include <list>
#include <iostream>
#include <memory>

using namespace std;

template<typename ValueType>
class Container{

public:
	typedef Iterator<ValueType> iterator;
	typedef Iterator<ValueType> const_iterator;

	//Container(initializer_list<int> values);

	virtual iterator begin()=0;
	virtual iterator end()=0;

	virtual const_iterator begin() const = 0;
	virtual const_iterator end() const = 0;

	const size_t size;

	unique_ptr<ValueType[]> data;

	virtual void clear() = 0;

};

