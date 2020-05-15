#include "ErContainer.h"

template<typename ValueType>
ErContainer<ValueType>::ErContainer(initializer_list<ValueType> values) :
	size(values.size()),
	data(new ValueType[size])
{
	std::copy(values.begin(), values.end(), data.get());
}

template<typename ValueType>
ErContainer<ValueType>::iterator ErContainer<ValueType>::begin()
{
	return iterator(data.get());
}

template<typename ValueType>
ErContainer<ValueType>::iterator ErContainer<ValueType>::end()
{
	return iterator(data.get() + size);
}

template<typename ValueType>
ErContainer<ValueType>::const_iterator ErContainer<ValueType>::begin() const
{
	return const_iterator(data.get());
}

template<typename ValueType>
ErContainer<ValueType>::const_iterator ErContainer<ValueType>::end() const
{
	return const_iterator(data.get() + size);
}